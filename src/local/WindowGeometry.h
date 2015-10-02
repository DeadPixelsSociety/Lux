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


#ifndef GAME_WINDOW_GEOMETRY_H
#define GAME_WINDOW_GEOMETRY_H

#include <SFML/Graphics.hpp>


class WindowGeometry {
public:
  WindowGeometry(float width, float height)
  : m_width(width)
  , m_height(height)
  {

  }

  void update(sf::Event& event);

  float getXCentered(float w);
  float getXFromRight(float x);

  float getYCentered(float h);
  float getYFromBottom(float y);

  sf::Vector2f getCornerPosition(const sf::Vector2f& pos);

private:
  float m_width;
  float m_height;
};


#endif // GAME_WINDOW_GEOMETRY_H
