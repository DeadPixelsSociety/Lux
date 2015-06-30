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
#include "Shoot.h"

#include "Game.h"

Shoot::~Shoot() {

}

void SingleShoot::shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) {
  ShootEvent shoot;
  shoot.origin = getOrigin();
  shoot.pos = pos;
  shoot.velocity = dir;
  shoot.color = getColor();

  events.triggerEvent(&shoot);
}


static constexpr float CONE_ANGLE = 15; // in degrees

void ConeShoot::shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) {
  ShootEvent shoot;
  shoot.origin = getOrigin();
  shoot.pos = pos;
  shoot.color = getColor();

  shoot.velocity = dir;
  events.triggerEvent(&shoot);

  sf::Transform tr1;
  tr1.rotate(CONE_ANGLE);
  shoot.velocity = tr1.transformPoint(dir);
  events.triggerEvent(&shoot);

  sf::Transform tr2;
  tr2.rotate(-CONE_ANGLE);
  shoot.velocity = tr2.transformPoint(dir);
  events.triggerEvent(&shoot);
}


void PeriodicShoot::shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) {
  m_elapsedTime += dt;

  if (m_elapsedTime >= m_period) {
    getDecorated().shoot(dt, pos, dir, events);
    m_elapsedTime -= m_period;
  }
}


void DelayedShoot::shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) {
  m_elapsedTime += dt;

  if (m_elapsedTime >= m_delay) {
    getDecorated().shoot(dt, pos, dir, events);
  }
}


void CountedShoot::shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) {
  if (m_count > 0) {
    getDecorated().shoot(dt, pos, dir, events);
    m_count--;
  }
}

