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
#ifndef LOCAL_ENEMY_H
#define LOCAL_ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
public:
  Enemy(const sf::Vector2f& pos, const sf::Vector2f& vel)
  : m_pos(pos), m_vel(vel) {
  }

  virtual void update(float dt) override;

  virtual void render(sf::RenderWindow& window) override;

private:
  static constexpr float RADIUS = 20.0f;

  sf::Vector2f m_pos;
  sf::Vector2f m_vel;
};

#endif // LOCAL_ENEMY_H
