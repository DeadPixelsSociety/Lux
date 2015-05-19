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
#include "Hero.h"

#include "Game.h"

void Hero::update(float dt) {
  m_pos = m_sensor.getCenter();

  HeroPositionEvent event;
  event.pos = m_pos;
  m_events.triggerEvent(&event);

  m_elapsedTime += dt;

  if (m_elapsedTime >= 500.0f) {
    sf::Vector2f velocity(1.0f, 1.0f);
    m_elapsedTime = 0.0f;
  }
}

void Hero::render(sf::RenderWindow& window) {
  sf::CircleShape circle(RADIUS);
  circle.setOrigin(RADIUS, RADIUS);
  circle.setPosition(m_pos);
  circle.setFillColor(sf::Color::Red);
  window.draw(circle);
}
