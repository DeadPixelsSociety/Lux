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
#ifndef LOCAL_ENTITY_H
#define LOCAL_ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
  Entity()
  : m_alive(true)
  {
  }

  virtual ~Entity();

  bool isAlive() const {
    return m_alive;
  }

  void kill() {
    m_alive = false;
  }

  virtual int priority() const;

  virtual void update(float dt);
  virtual void render(sf::RenderWindow& window);

private:
  bool m_alive;
};

#endif // LOCAL_ENTITY_H
