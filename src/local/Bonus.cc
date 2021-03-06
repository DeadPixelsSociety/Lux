/*
 * Lux
 *
 * Copyright (c) 2015, Julien Bernard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Bonus.h"

#include <cassert>
#include <iostream>

#include "Game.h"
#include "Hero.h"

BonusManager::BonusManager(game::EventManager& events, game::ResourceManager &resources, Engine &engine)
: m_engine(engine)
, m_lifeTexture(nullptr)
, m_weaponTexture(nullptr) {
  events.registerHandler<DropBonusEvent>(&BonusManager::onDropBonusEvent, this);
  events.registerHandler<LocationEvent>(&BonusManager::onLocationEvent, this);

  m_lifeTexture = resources.getTexture("bonus_life.png");
  assert(m_lifeTexture != nullptr);

  m_weaponTexture = resources.getTexture("bonus_weapon.png");
  assert(m_weaponTexture != nullptr);
}

void BonusManager::addBonus(const sf::Vector2f& pos, const sf::Vector2f& velocity, const BonusType &type) {
  Bonus bonus;
  bonus.pos = pos;
  bonus.velocity = velocity;
  bonus.type = type;
  bonus.active = true;

  m_bonus.push_back(bonus);
}

static constexpr float EXTRA = 20.0f;

static constexpr float AREA_WIDTH = 800;
static constexpr float AREA_HEIGHT = 600;

void BonusManager::update(float dt) {
  sf::FloatRect screen(-EXTRA, -EXTRA, AREA_WIDTH + 2 * EXTRA, AREA_HEIGHT + 2 * EXTRA);

  for (Bonus& bonus : m_bonus) {
    bonus.pos += bonus.velocity * dt;

    if (!screen.contains(bonus.pos)) {
      bonus.active = false;
    }
  }

  m_bonus.erase(std::remove_if(m_bonus.begin(), m_bonus.end(), [](const Bonus& b) { return !b.active; }), m_bonus.end());
}

static constexpr float BONUS_SIZE = 60.0f;
static constexpr float RATIO_LIFE_BONUS = BONUS_SIZE / 256.0f;
static constexpr float RATIO_WEAPON_BONUS = BONUS_SIZE / 256.0f;

void BonusManager::render(sf::RenderWindow& window) {
  sf::Sprite sprite;
  
  for (Bonus& bonus : m_bonus) {
    // Check the type of bonus
    switch(bonus.type) {
      case BonusType::LIFE:
        sprite.setTexture(*m_lifeTexture);
        sprite.setOrigin(128.0f, 128.0f); // Half size of texture
        sprite.setScale(RATIO_LIFE_BONUS, RATIO_LIFE_BONUS);
        sprite.setPosition(bonus.pos);
        break;

      case BonusType::UPGRADE_WEAPON:
        sprite.setTexture(*m_weaponTexture);
        sprite.setOrigin(128.0f, 128.0f); // Half size of texture
        sprite.setScale(RATIO_WEAPON_BONUS, RATIO_WEAPON_BONUS);
        sprite.setPosition(bonus.pos);
        break;
    }

    window.draw(sprite);
  }
}

static bool isTargetReached(const sf::Vector2f& shipPos, const sf::Vector2f& bonusPos) {
  sf::Rect<float> rectShip(shipPos, {Hero::HERO_WIDTH, Hero::HERO_HEIGHT});
  sf::Rect<float> rectBonus(bonusPos, {BONUS_SIZE, BONUS_SIZE});
  return rectShip.intersects(rectBonus);
}

static constexpr float BONUS_LINEAR_VELOCTY = 120.0f;

game::EventStatus BonusManager::onDropBonusEvent(game::EventType type, game::Event *event) {
  auto shoot = static_cast<DropBonusEvent *>(event);

  // Select the random type
  std::uniform_int_distribution<int> dist(0, 1);
  BonusType bonusType = static_cast<BonusType>(dist(m_engine));

  addBonus(shoot->pos, {0.0f, BONUS_LINEAR_VELOCTY}, bonusType);

  return game::EventStatus::KEEP;
}

game::EventStatus BonusManager::onLocationEvent(game::EventType type, game::Event *event) {
  assert(type == LocationEvent::type);

  auto loc = static_cast<LocationEvent*>(event);

  // Check if is player location
  if (loc->origin != Origin::HERO) {
    return game::EventStatus::KEEP;
  }

  // Check if one bonus is hit
  for (Bonus& bonus : m_bonus) {
    if (isTargetReached(loc->pos, bonus.pos)) {
      // Remove the bonus
      bonus.active = false;

      // Check the type of bonus
      switch(bonus.type) {
        case BonusType::LIFE:
          loc->ship->restore(10.0f);
          break;

        case BonusType::UPGRADE_WEAPON:
          Hero *hero = static_cast<Hero*>(loc->ship);
          hero->upgradeWeapon();
          break;
      }
    }
  }

  return game::EventStatus::KEEP;
}
