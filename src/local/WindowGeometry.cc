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

#include "WindowGeometry.h"


void WindowGeometry::update(sf::Event& event) {
  if (event.type != sf::Event::Resized) {
    return;
  }

  m_width = static_cast<float>(event.size.width);
  m_height = static_cast<float>(event.size.height);
}

float WindowGeometry::getXCentered(float w) {
  return m_width / 2 - w / 2;
}

float WindowGeometry::getXFromRight(float x) {
  return m_width - x;
}


float WindowGeometry::getYCentered(float h) {
  return m_height / 2 - h / 2;
}

float WindowGeometry::getYFromBottom(float y) {
  return m_height - y;
}

sf::Vector2f WindowGeometry::getCornerPosition(const sf::Vector2f& pos) {
  float x = pos.x > 0 ? pos.x : m_width + pos.x;
  float y = pos.y > 0 ? pos.y : m_height + pos.y;
  return { x, y };
}

