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
#ifndef LOCAL_SHIP_H
#define LOCAL_SHIP_H

#include <game/Entity.h>

class Ship : public game::Entity {
public:
  Ship(float maxStructurePoint);

  float getMaxStructurePoint() const {
    return m_maxStructurePoint;
  }

  float getStructurePoint() const {
    return m_structurePoint;
  }

  float getStructureHealthPercentage() const {
    return m_structurePoint / m_maxStructurePoint;
  }

  bool isDamaged() const {
    return m_structurePoint <= 0.0f;
  }

  void restore() {
    m_structurePoint = m_maxStructurePoint;
  }

  void restore(const float health) {
    if (health + m_structurePoint > m_maxStructurePoint) {
      restore();
      return;
    }
    m_structurePoint += health;
  }

  void impact(float damage);

private:
  float m_maxStructurePoint;
  float m_structurePoint;
};


#endif // LOCAL_SHIP_H
