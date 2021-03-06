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
#include "Memory.h"

Shoot::~Shoot() {

}

std::unique_ptr<Shoot> makeSimpleShoot(Origin origin, ShipClass shipClass, float delay) {
  return makeUnique<DelayedShoot>(
    makeUnique<CountedShoot>(
      makeUnique<SingleShoot>(origin, shipClass)
      , 1)
    , delay);
}

std::unique_ptr<Shoot> makeBurstShoot(Origin origin, ShipClass shipClass, float delay, float period, int count) {
  return makeUnique<DelayedShoot>(
    makeUnique<PeriodicShoot>(
      makeUnique<CountedShoot>(
        makeUnique<SingleShoot>(origin, shipClass)
        , count)
      , period)
    , delay);
}

std::unique_ptr<Shoot> makeConeShoot(Origin origin, ShipClass shipClass, float delay) {
  return makeUnique<DelayedShoot>(
    makeUnique<CountedShoot>(
      makeUnique<ConeShoot>(origin, shipClass)
      , 1)
    , delay);
}

std::unique_ptr<Shoot> makeContinuousSimpleShoot(Origin origin, ShipClass shipClass, float period) {
  return makeUnique<PeriodicShoot>(
    makeUnique<SingleShoot>(origin, shipClass)
    , period);
}

std::unique_ptr<Shoot> makeSimplePlayerShoot(Origin origin, ShipClass shipClass, int nbshoot, float shootInterval, float inactivePeriod) {
  return makeUnique<RegularShoot>(
    makeUnique<SingleShoot>(origin, shipClass)
    , nbshoot, shootInterval, inactivePeriod);
}


void SingleShoot::shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, game::EventManager& events) {
  ShootEvent shoot;
  shoot.origin = getOrigin();
  shoot.pos = pos;
  shoot.velocity = dir;
  shoot.shipClass = getShipClass();

  events.triggerEvent(&shoot);
}


static constexpr float CONE_ANGLE = 15; // in degrees

void ConeShoot::shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, game::EventManager& events) {
  ShootEvent shoot;
  shoot.origin = getOrigin();
  shoot.pos = pos;
  shoot.shipClass = getShipClass();

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


void PeriodicShoot::shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, game::EventManager& events) {
  m_elapsedTime -= dt;

  if (m_elapsedTime <= 0) {
    getDecorated().shoot(dt, pos, dir, events);
    m_elapsedTime += m_period;
  }
}


void DelayedShoot::shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, game::EventManager& events) {
  m_elapsedTime += dt;

  if (m_elapsedTime >= m_delay) {
    getDecorated().shoot(dt, pos, dir, events);
  }
}


void CountedShoot::shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, game::EventManager& events) {
  if (m_count > 0) {
    getDecorated().shoot(dt, pos, dir, events);
    m_count--;
  }
}


void RegularShoot::shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, game::EventManager& events) {
  m_elapsedTime += dt;

  // Update state of shoot
  if (m_topFront && m_elapsedTime >= m_shootPeriod) {
    m_elapsedTime -= m_shootPeriod;
    m_topFront = false;
  }
  else if (!m_topFront && m_elapsedTime >= m_inactivePeriod) {
    m_elapsedTime -= m_inactivePeriod;
    m_topFront = true;
    m_nbShoot = 0;
  }
  
  // Launch the shoot if neede
  if (m_topFront && m_elapsedTime >= (m_shootInterval * m_nbShoot)) {
    m_nbShoot++;
    getDecorated().shoot(dt, pos, dir, events);
  }
}

