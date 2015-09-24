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

#include <cassert>
#include <iostream>

#include "Bonus.h"
#include "Config.h"
#include "Game.h"

BonusManager::BonusManager(EventManager& events, ResourceManager &resources) 
: m_lifeTexture(nullptr) {
  events.registerHandler<DropBonusEvent>(&BonusManager::onDropBonusEvent, this);
  events.registerHandler<LocationEvent>(&BonusManager::onLocationEvent, this);

  m_lifeTexture = resources.getTexture("red_cross.png");
  assert(m_lifeTexture != nullptr);
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

void BonusManager::update(float dt) {
  sf::FloatRect screen(-EXTRA, -EXTRA, WINDOW_W + 2 * EXTRA, WINDOW_H + 2 * EXTRA);

  for (Bonus& bonus : m_bonus) {
    bonus.pos += bonus.velocity * dt;

    if (!screen.contains(bonus.pos)) {
      bonus.active = false;
    }
  }

  m_bonus.erase(std::remove_if(m_bonus.begin(), m_bonus.end(), [](const Bonus& b) { return !b.active; }), m_bonus.end());
}

static constexpr float BONUS_SIZE = 32.0f;
static constexpr float RATIO_LIFE_BONUS = BONUS_SIZE / 148.0f;

void BonusManager::render(sf::RenderWindow& window) {
  sf::Sprite sprite;
  
  for (Bonus& bonus : m_bonus) {
    // Check the type of bonus
    switch(bonus.type) {
      case BonusType::LIFE:
        sprite.setTexture(*m_lifeTexture);
        sprite.setOrigin(BONUS_SIZE / 2.0f, BONUS_SIZE / 2.0f); // Half size of texture
        sprite.setScale(RATIO_LIFE_BONUS, RATIO_LIFE_BONUS);
        sprite.setPosition(bonus.pos);
        break;
    }

    window.draw(sprite);
  }
}

static bool isTargetReached(const sf::Vector2f& shipPos, const sf::Vector2f& bonusPos) {
  return shipPos.x - 30.0f <= bonusPos.x && bonusPos.x <= shipPos.x + 30.0f
      && shipPos.y - 30.0f <= bonusPos.y && bonusPos.y <= shipPos.y + 30.0f;
}

static constexpr float BONUS_LINEAR_VELOCTY = WINDOW_H / 5.0f;

EventStatus BonusManager::onDropBonusEvent(EventType type, Event *event) {
  auto shoot = static_cast<DropBonusEvent *>(event);

  addBonus(shoot->pos, {0.0f, BONUS_LINEAR_VELOCTY}, BonusType::LIFE);

  return EventStatus::KEEP;
}

EventStatus BonusManager::onLocationEvent(EventType type, Event *event) {
  assert(type == LocationEvent::type);

  auto loc = static_cast<LocationEvent*>(event);

  // Check if is player location
  if (loc->origin != Origin::HERO) {
    return EventStatus::KEEP;
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
      }
    }
  }

  return EventStatus::KEEP;
}
