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

#include "Config.h"
#include "Game.h"
#include "Memory.h"

static constexpr float SHOOT_PERIOD = 1.0f;
static constexpr float SHOOT_VELOCITY = 400.0f;

Enemy::Enemy(const sf::Vector2f& pos, const sf::Vector2f& vel, EventManager& events, ResourceManager &resources)
: m_pos(pos), m_vel(vel)
, m_events(events)
, m_elapsedTime(0.0f)
, m_texture(nullptr)
// , m_shoot(new ConeShoot(Origin::ENEMY, sf::Color::Yellow))
, m_shoot(makeUnique<DelayedShoot>(
    makeUnique<PeriodicShoot>(
      makeUnique<CountedShoot>(
        makeUnique<SingleShoot>(Origin::ENEMY, sf::Color::Green)
        , 3)
      , 0.1f)
    , 1.0f)
  )
{
  m_texture = resources.getTexture("ship_bootes.png");
  assert(m_texture != nullptr);
}


void Enemy::update(float dt) {
  assert(isAlive());

  m_pos += m_vel * dt;

  if (m_pos.y > WINDOW_H + ENEMY_HEIGHT) {
    kill();
    assert(!isAlive());
    return;
  }

  LocationEvent loc;
  loc.origin = Origin::ENEMY;
  loc.pos = m_pos;
  loc.entity = this;
  m_events.triggerEvent(&loc);

  if (!isAlive()) {
    DeadEvent dead;
    dead.origin = Origin::ENEMY;
    dead.ship = ShipClass::BOOTES;
    dead.pos = m_pos;
    m_events.triggerEvent(&dead);
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
  sprite.setOrigin(128.0f, 128.0f); // Half size of texture
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


static constexpr float GENERATION_PERIOD = 1.0f;

EventStatus EnemyManager::onLocationEvent(EventType type, Event *event) {
  assert(type == LocationEvent::type);
  auto loc = static_cast<LocationEvent*>(event);

  if (loc->origin == Origin::HERO) {
    m_hero_pos = loc->pos;
  }

  return EventStatus::KEEP;
}


void EnemyManager::update(float dt) {
  m_elapsedTime += dt;

  std::uniform_real_distribution<float> dist(Enemy::ENEMY_WIDTH, WINDOW_W - Enemy::ENEMY_WIDTH);

  if (m_elapsedTime >= GENERATION_PERIOD) {
    sf::Vector2f pos(dist(m_engine), -Enemy::ENEMY_HEIGHT);
    sf::Vector2f velocity(0.0f, WINDOW_H / 3.0f);

    auto enemy = new Enemy(pos, velocity, m_events, m_resources);
    m_enemies.push_back(enemy);

    m_elapsedTime = 0.0f;
  }

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


