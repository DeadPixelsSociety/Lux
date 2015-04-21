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
#ifndef LOCAL_HERO_H
#define LOCAL_HERO_H

#include "Entity.h"
#include "PhysicEngine.h"
#include "Sensor.h"

class Hero : public Entity {
public:
  static constexpr float RADIUS = 10.0f;

  Hero(Sensor& sensor, PhysicEngine &physicEngine)
  : m_sensor(sensor)
  , m_physicEngine(physicEngine)
  , m_elapsedTime(0.0f)
  {
  }

  virtual void update(float dt) override;

  virtual void render(sf::RenderWindow& window) override;

private:
  sf::Vector2f m_pos;
  Sensor& m_sensor;
  PhysicEngine &m_physicEngine;
  float m_elapsedTime;
};


#endif // LOCAL_HERO_H
