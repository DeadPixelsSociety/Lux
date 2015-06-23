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
#ifndef LOCAL_SHOOT_H
#define LOCAL_SHOOT_H

#include "Game.h"

enum class ShootType {
  PERIODIC,
};

class Shoot {
public:
  Shoot(Origin origin, sf::Color color)
  : m_origin(origin)
  , m_color(color)
  {

  }

  virtual void shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir) = 0;

  Origin getOrigin() const {
    return m_origin;
  }

  const sf::Color& getColor() const {
    return m_color;
  }

private:
  Origin m_origin;
  sf::Color m_color;
};

class PeriodicShoot : public Shoot {
public:
  PeriodicShoot(Origin origin, sf::Color color)
  : Shoot(origin, color)
  {

  }

  virtual void shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir) override;


private:
  float m_elapsedTime;
  float m_period;
};

#endif // LOCAL_SHOOT_H
