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

#include "Config.h"
#include "Game.h"

static constexpr float SHOOT_PERIOD = 0.3f;
static constexpr float SHOOT_VELOCITY = 400.0f;

void Enemy::update(float dt) {
  m_pos += m_vel * dt;

  if (m_pos.y > WINDOW_H + ENEMY_HEIGHT) {
    DeadEnemyEvent dead;
    dead.dead = this;

    m_events.triggerEvent(&dead);
    return;
  }

  EnemyPositionEvent event;
  event.pos = m_pos;
  m_events.triggerEvent(&event);

  m_elapsedTime += dt;

  if (m_elapsedTime >= SHOOT_PERIOD) {
    ShootEvent shoot;
    shoot.origin = Origin::ENEMY;
    shoot.pos = m_pos;

    sf::Vector2f d = m_hero_pos - m_pos;
    float norm = std::hypot(d.x, d.y);
    d = (d / norm) * SHOOT_VELOCITY;

    shoot.velocity = d;
    shoot.color = sf::Color::Green;

    m_events.triggerEvent(&shoot);
    m_elapsedTime = 0.0f;
  }
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

EventStatus Enemy::onPositionEvent(EventType type, Event *event) {
  assert(type == HeroPositionEvent::type);
  auto heroPosition = static_cast<HeroPositionEvent*>(event);
  m_hero_pos = heroPosition->pos;
  return EventStatus::KEEP;
}

static constexpr float GENERATION_PERIOD = 1.0f;

EventStatus EnemyManager::onDeadEnemyEvent(EventType type, Event *event) {
  assert(type == DeadEnemyEvent::type);
  auto dead = static_cast<DeadEnemyEvent*>(event);
  
  m_enemies.removeEntity(dead->dead);
  delete m_enemies.removeEntity(dead->dead);;
  return EventStatus::KEEP;
}

void EnemyManager::update(float dt) {

  m_elapsedTime += dt;

  std::uniform_real_distribution<float> dist(Enemy::ENEMY_WIDTH, WINDOW_W - Enemy::ENEMY_WIDTH);

  if (m_elapsedTime >= GENERATION_PERIOD) {
    sf::Vector2f pos(dist(m_engine), -Enemy::ENEMY_HEIGHT);
    sf::Vector2f velocity(0.0f, WINDOW_H / 3.0f);

    auto enemy = new Enemy(pos, velocity, m_events, m_resources);
    m_enemies.addEntity(*enemy);

    m_elapsedTime = 0.0f;
  }

  m_enemies.update(dt);
}

void EnemyManager::render(sf::RenderWindow& window) {
  m_enemies.render(window);
}


