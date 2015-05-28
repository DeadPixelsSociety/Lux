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

static constexpr float SHOOT_PERIOD = 0.5f;
static constexpr float SHOOT_VELOCITY = 400.0f;

void Hero::update(float dt) {
  m_pos = m_sensor.getCenter();

  HeroPositionEvent event;
  event.pos = m_pos;
  m_events.triggerEvent(&event);

  m_elapsedTime += dt;

  if (m_elapsedTime >= SHOOT_PERIOD) {
    ShootEvent shoot;
    shoot.origin = Origin::HERO;
    shoot.pos = m_pos;
    shoot.velocity = sf::Vector2f(0.0f, -SHOOT_VELOCITY);
    shoot.color = sf::Color::Yellow;

    m_events.triggerEvent(&shoot);
    m_elapsedTime = 0.0f;
  }
}

void Hero::render(sf::RenderWindow& window) {
  sf::Sprite sprite;
  sprite.setTexture(*m_texture);
  sprite.setOrigin(128.0f, 128.0f); // Half size of texture
  sprite.setScale(HERO_SCALE_X, HERO_SCALE_Y);
  sprite.setPosition(m_pos);
  sprite.setRotation(90.0f);
  window.draw(sprite);
}
