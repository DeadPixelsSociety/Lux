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

#include "Config.h"

static constexpr float SHOOT_PERIOD = 0.4f;
static constexpr float SHOOT_VELOCITY = 400.0f;

void Hero::update(float dt) {
  m_pos = m_sensor.getCenter();

  LocationEvent loc;
  loc.origin = Origin::HERO;
  loc.pos = m_pos;
  loc.ship = this;
  m_events.triggerEvent(&loc);

  ScoreEvent scoreEvent;
  scoreEvent.score = m_score;
  m_events.triggerEvent(&scoreEvent);

  if (!isAlive()) {
    DeadEvent dead;
    dead.origin = Origin::HERO;
    dead.ship = ShipClass::ANTLIA;
    dead.pos = m_pos;
    m_events.triggerEvent(&dead);
    return;
  }

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

static constexpr float HEALTH_WIDTH = 200.0f;
static constexpr float HEALTH_HEIGHT = 5.0f;
static constexpr float HEALTH_THICKNESS = 1.0f;
static constexpr float HEALTH_PADDING = 40.0f;

static constexpr float SCORE_PADDING_WIDTH = WINDOW_W - 150.0f;

void Hero::render(sf::RenderWindow& window) {
  sf::Sprite sprite;
  sprite.setTexture(*m_texture);
  sprite.setOrigin(128.0f, 128.0f); // Half size of texture
  sprite.setScale(HERO_SCALE_X, HERO_SCALE_Y);
  sprite.setPosition(m_pos);
  sprite.setRotation(-90.0f);
  window.draw(sprite);

  sf::RectangleShape rectangleShape({ HEALTH_WIDTH, HEALTH_HEIGHT });
  rectangleShape.setOrigin(HEALTH_WIDTH / 2, HEALTH_HEIGHT / 2);
  rectangleShape.setPosition(WINDOW_W / 2, WINDOW_H - HEALTH_PADDING);
  rectangleShape.setOutlineColor(sf::Color::White);
  rectangleShape.setOutlineThickness(HEALTH_THICKNESS);
  rectangleShape.setFillColor(sf::Color::Transparent);
  window.draw(rectangleShape);

  sf::RectangleShape healthRectangle({ HEALTH_WIDTH * getStructureHealthPercentage(), HEALTH_HEIGHT });
  healthRectangle.setOrigin(0.0f, HEALTH_HEIGHT / 2);
  healthRectangle.setPosition(WINDOW_W / 2 - HEALTH_WIDTH / 2, WINDOW_H - HEALTH_PADDING);
  healthRectangle.setFillColor(sf::Color::Red);
  window.draw(healthRectangle);

  sf::Text text;
  text.setFont(*m_font);
  text.setString("Score : " + std::to_string(m_score));
  text.setCharacterSize(24);
  text.setColor(sf::Color::White);

  // FixMe: fix the vertical align
  text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
  text.setPosition(SCORE_PADDING_WIDTH, WINDOW_H - HEALTH_PADDING - text.getLocalBounds().height - 5.0f);

  window.draw(text);
}

EventStatus Hero::onDeadEvent(EventType type, Event *event) {
  auto dead = static_cast<DeadEvent *>(event);

  if (dead->origin != Origin::ENEMY) {
    return EventStatus::KEEP;
  }

  switch (dead->ship) {
    case ShipClass::ANTLIA:
    break;

    case ShipClass::BOOTES:
      m_score += 10;
    break;

    case ShipClass::CYGNUS:
      m_score += 50;
    break;

    case ShipClass::DRACO:
      m_score += 200;
    break;

    case ShipClass::ERIDANUS:
      m_score += 500;
    break;

    default:
      assert(false);
  }

  return EventStatus::KEEP;
}

EventStatus Hero::onRestartGameEvent(EventType type, Event *event) {
  m_score = 0;
  restore();
  return EventStatus::KEEP;
}
