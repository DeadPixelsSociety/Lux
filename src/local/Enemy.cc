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
#include "Enemy.h"

#include <cassert>
#include <iostream>

#include "Game.h"
#include "Memory.h"

static constexpr float SHOOT_PERIOD = 1.0f;
static constexpr float SHOOT_VELOCITY = 400.0f;
static constexpr float BONUS_FREQUENCY = 0.50f;

Enemy::Enemy(ShipClass ship, const sf::Vector2f& pos, const sf::Vector2f& vel, float health, Engine& engine, game::EventManager& events, game::ResourceManager &resources)
: Ship(health)
, m_shipClass(ship)
, m_pos(pos)
, m_vel(vel)
, m_engine(engine)
, m_events(events)
, m_elapsedTime(0.0f)
, m_texture(nullptr)
// , m_shoot(new ConeShoot(Origin::ENEMY, sf::Color::Yellow))
, m_shoot(nullptr)
{
  switch (ship) {
    case ShipClass::ANTLIA:
      assert(false);
      break;
    case ShipClass::BOOTES:
      m_texture = resources.getTexture("ship_bootes.png");
      m_shoot = makeSimpleShoot(Origin::ENEMY, ShipClass::BOOTES, 0.5f);
      break;
    case ShipClass::CYGNUS:
      m_texture = resources.getTexture("ship_cygnus.png");
      m_shoot = makeBurstShoot(Origin::ENEMY, ShipClass::CYGNUS, 0.75f, 0.1f, 3);
      break;
    case ShipClass::DRACO:
      m_texture = resources.getTexture("ship_draco.png");
      m_shoot = makeConeShoot(Origin::ENEMY, ShipClass::DRACO, 0.75f);
      break;
    case ShipClass::ERIDANUS:
      m_texture = resources.getTexture("ship_eridanus.png");
      m_shoot = makeContinuousSimpleShoot(Origin::ENEMY, ShipClass::ERIDANUS, 0.5f);
      break;
  }

  assert(m_texture != nullptr);
}

static constexpr float AREA_HEIGHT = 600;

void Enemy::update(float dt) {
  assert(isAlive());

  m_pos += m_vel * dt;

  if (m_pos.y > AREA_HEIGHT + ENEMY_HEIGHT) {
    kill();
    assert(!isAlive());
    return;
  }

  LocationEvent loc;
  loc.origin = Origin::ENEMY;
  loc.pos = m_pos;
  loc.ship = this;
  m_events.triggerEvent(&loc);

  if (isDamaged()) {
    DeadEvent dead;
    dead.origin = Origin::ENEMY;
    dead.ship = m_shipClass;
    dead.pos = m_pos;
    m_events.triggerEvent(&dead);
    kill();

    // Generate the bonus
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    if (dist(m_engine) < BONUS_FREQUENCY) {
      DropBonusEvent event;
      event.pos = m_pos;
      m_events.triggerEvent(&event);
    }

    return;
  }

  sf::Vector2f dir = m_hero_pos - m_pos;
  float norm = std::hypot(dir.x, dir.y);
  dir = (dir / norm) * SHOOT_VELOCITY;

  m_shoot->shoot(dt, m_pos, dir, m_events);
}

void Enemy::render(sf::RenderWindow& window) {
  sf::Sprite sprite;
  sprite.setTexture(*m_texture);
  sprite.setOrigin(32.0f, 32.0f); // Half size of texture
  sprite.setScale(ENEMY_SCALE_X, ENEMY_SCALE_Y);
  sprite.setPosition(m_pos);
  sprite.setRotation(-90.0f);
  window.draw(sprite);
}


EnemyManager::~EnemyManager() {
  for (auto enemy : m_enemies) {
    delete enemy;
  }
}

void EnemyManager::addEnemy(ShipClass ship, const sf::Vector2f& position, const sf::Vector2f& velocity) {
  auto enemy = new Enemy(ship, position, velocity, 15.0f, m_engine, m_events, m_resources);
  m_enemies.push_back(enemy);
}

static constexpr float GENERATION_PERIOD = 1.0f;

game::EventStatus EnemyManager::onLocationEvent(game::EventType type, game::Event *event) {
  assert(type == LocationEvent::type);
  auto loc = static_cast<LocationEvent*>(event);

  if (loc->origin == Origin::HERO) {
    m_hero_pos = loc->pos;
  }

  return game::EventStatus::KEEP;
}


void EnemyManager::update(float dt) {
  for (auto enemy : m_enemies) {
    enemy->setHeroPosition(m_hero_pos);
    enemy->update(dt);
  }

  const auto trash = std::partition(m_enemies.begin(), m_enemies.end(), [](const Enemy *e) {
    return e->isAlive();
  });

  for (auto it = trash; it != m_enemies.end(); ++it) {
    assert(!(*it)->isAlive());
    delete *it;
    *it = nullptr;
  }

  m_enemies.erase(trash, m_enemies.end());
}

void EnemyManager::render(sf::RenderWindow& window) {
  for (auto enemy : m_enemies) {
    enemy->render(window);
  }
}


