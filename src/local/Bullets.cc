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
#include "Bullets.h"

#include <cassert>
#include <iostream>

#include "Enemy.h"
#include "Hero.h"

static constexpr float RADIUS = 5.0f;

Bullets::Bullets(game::EventManager& events, game::ResourceManager &manager)
: m_bulletBlueTexture(nullptr)
, m_bulletGreenTexture(nullptr)
, m_bulletYellowTexture(nullptr)
, m_bulletPurpleTexture(nullptr) {
  events.registerHandler<LocationEvent>(&Bullets::onLocationEvent, this);
  events.registerHandler<ShootEvent>(&Bullets::onShootEvent, this);

  // Load the texture
  m_bulletBlueTexture = manager.getTexture("bullet_blue.png");
  assert(m_bulletBlueTexture != nullptr);

  m_bulletGreenTexture = manager.getTexture("bullet_green.png");
  assert(m_bulletGreenTexture != nullptr);

  m_bulletYellowTexture = manager.getTexture("bullet_yellow.png");
  assert(m_bulletYellowTexture != nullptr);

  m_bulletPurpleTexture = manager.getTexture("bullet_purple.png");
  assert(m_bulletPurpleTexture != nullptr);
}


void Bullets::addBullet(Origin origin, ShipClass shipClass, const sf::Vector2f& pos, const sf::Vector2f& velocity) {
  Bullet bullet;
  bullet.origin = origin;
  bullet.pos = pos;
  bullet.velocity = velocity;

  switch (shipClass) {
    case ShipClass::ANTLIA:
      bullet.texture = m_bulletBlueTexture;
      break;

    case ShipClass::BOOTES:
      bullet.texture = m_bulletGreenTexture;
      break;

    case ShipClass::CYGNUS:
    case ShipClass::DRACO:
      bullet.texture = m_bulletPurpleTexture;
      break;

    case ShipClass::ERIDANUS:
      bullet.texture = m_bulletYellowTexture;
      break;
  }
  bullet.active = true;

  m_bullets.push_back(bullet);
}

static constexpr float AREA_WIDTH = 800;
static constexpr float AREA_HEIGHT = 600;
static constexpr float EXTRA = 100.0f;

void Bullets::update(float dt) {
  sf::FloatRect screen(-EXTRA, -EXTRA, AREA_WIDTH + 2 * EXTRA, AREA_HEIGHT + 2 * EXTRA);

  for (Bullet& bullet : m_bullets) {
    bullet.pos += bullet.velocity * dt;

    if (!screen.contains(bullet.pos)) {
      bullet.active = false;
    }
  }

  m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [](const Bullet& b) { return !b.active; }), m_bullets.end());
}

void Bullets::render(sf::RenderWindow& window) {
  for (Bullet& bullet : m_bullets) {
    sf::CircleShape shape(RADIUS);
    shape.setOrigin(RADIUS, RADIUS);
    shape.setTexture(bullet.texture);
    shape.setPosition(bullet.pos);
    window.draw(shape);
  }
}

static bool isTargetReached(const sf::Vector2f& shipPos, const sf::Vector2f& bulletPos) {
  return shipPos.x - 30.0f <= bulletPos.x && bulletPos.x <= shipPos.x + 30.0f
      && shipPos.y - 30.0f <= bulletPos.y && bulletPos.y <= shipPos.y + 30.0f;
}

game::EventStatus Bullets::onLocationEvent(game::EventType type, game::Event *event) {
  assert(type == LocationEvent::type);

  auto loc = static_cast<LocationEvent*>(event);

  for (Bullet& bullet : m_bullets) {
    if (loc->origin == bullet.origin) {
      continue;
    }

    if (isTargetReached(loc->pos, bullet.pos)) {
      loc->ship->impact(10.0f);
      bullet.active = false;
    }
  }

  return game::EventStatus::KEEP;
}

game::EventStatus Bullets::onShootEvent(game::EventType type, game::Event *event) {
  auto shoot = static_cast<ShootEvent *>(event);

  addBullet(shoot->origin, shoot->shipClass, shoot->pos, shoot->velocity);

  return game::EventStatus::KEEP;
}
