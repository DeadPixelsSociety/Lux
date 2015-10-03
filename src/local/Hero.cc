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


static constexpr float SHOOT_PERIOD = 0.4f;
static constexpr float SHOOT_VELOCITY = -400.0f;

void Hero::update(float dt) {
  if (!m_inGame) {
    return;
  }

  m_pos = m_sensor.getCenter();

  LocationEvent loc;
  loc.origin = Origin::HERO;
  loc.pos = m_pos;
  loc.ship = this;
  m_events.triggerEvent(&loc);

  ScoreEvent scoreEvent;
  scoreEvent.score = m_score;
  m_events.triggerEvent(&scoreEvent);

  if (isDamaged()) {
    DeadEvent dead;
    dead.origin = Origin::HERO;
    dead.ship = ShipClass::ANTLIA;
    dead.pos = m_pos;
    m_events.triggerEvent(&dead);
    m_inGame = false;
    return;
  }

  m_elapsedTime += dt;

  sf::Vector2f dir(0.0f, SHOOT_VELOCITY);
  m_shoot->shoot(dt, m_pos, dir, m_events);
}

static constexpr float HEALTH_WIDTH = 200.0f;
static constexpr float HEALTH_HEIGHT = 5.0f;
static constexpr float HEALTH_THICKNESS = 1.0f;
static constexpr float HEALTH_PADDING = 40.0f;

static constexpr float AREA_WIDTH = 800;
static constexpr float AREA_HEIGHT = 600;

static constexpr float SCORE_PADDING_WIDTH = AREA_WIDTH - 150.0f;


void Hero::render(sf::RenderWindow& window) {
  if (isDamaged()) {
    return;
  }

  sf::Sprite sprite;
  sprite.setTexture(*m_texture);
  sprite.setOrigin(128.0f, 128.0f); // Half size of texture
  sprite.setScale(HERO_SCALE_X, HERO_SCALE_Y);
  sprite.setPosition(m_pos);
  sprite.setRotation(-90.0f);
  window.draw(sprite);

  sf::RectangleShape rectangleShape({ HEALTH_WIDTH, HEALTH_HEIGHT });
  rectangleShape.setOrigin(HEALTH_WIDTH / 2, HEALTH_HEIGHT / 2);
  rectangleShape.setPosition(AREA_WIDTH / 2, AREA_HEIGHT - HEALTH_PADDING);
  rectangleShape.setOutlineColor(sf::Color::White);
  rectangleShape.setOutlineThickness(HEALTH_THICKNESS);
  rectangleShape.setFillColor(sf::Color::Transparent);
  window.draw(rectangleShape);

  sf::RectangleShape healthRectangle({ HEALTH_WIDTH * getStructureHealthPercentage(), HEALTH_HEIGHT });
  healthRectangle.setOrigin(0.0f, HEALTH_HEIGHT / 2);
  healthRectangle.setPosition(AREA_WIDTH / 2 - HEALTH_WIDTH / 2, AREA_HEIGHT - HEALTH_PADDING);
  healthRectangle.setFillColor(sf::Color::Red);
  window.draw(healthRectangle);

  sf::Text text;
  text.setFont(*m_font);
  text.setString("Score : " + std::to_string(m_score));
  text.setCharacterSize(24);
  text.setColor(sf::Color::White);

  // FixMe: fix the vertical align
  text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
  text.setPosition(SCORE_PADDING_WIDTH, AREA_HEIGHT - HEALTH_PADDING - text.getLocalBounds().height - 5.0f);

  window.draw(text);
}

game::EventStatus Hero::onDeadEvent(game::EventType type, game::Event *event) {
  auto dead = static_cast<DeadEvent *>(event);

  if (dead->origin != Origin::ENEMY) {
    return game::EventStatus::KEEP;
  }

  switch (dead->ship) {
    case ShipClass::ANTLIA:
    break;

    case ShipClass::BOOTES:
      m_score += 15;
    break;

    case ShipClass::CYGNUS:
      m_score += 45;
    break;

    case ShipClass::DRACO:
      m_score += 110;
    break;

    case ShipClass::ERIDANUS:
      m_score += 250;
    break;

    default:
      assert(false);
  }

  return game::EventStatus::KEEP;
}

void Hero::upgradeWeapon() {
  if (m_weaponLevel > 5) {
    m_score += 100;
  }
  else {
    m_shoot = makeSimplePlayerShoot(Origin::HERO, ShipClass::ANTLIA, ++m_weaponLevel, 0.1f, 0.5f);
  }
}

game::EventStatus Hero::onRestartGameEvent(game::EventType type, game::Event *event) {
  m_inGame = true;
  m_score = 0;
  restore();
  m_weaponLevel = 1;
  m_shoot = makeSimplePlayerShoot(Origin::HERO, ShipClass::ANTLIA, m_weaponLevel, 0.1f, 0.5f);

  return game::EventStatus::KEEP;
}

game::EventStatus Hero::onWinGameEvent(game::EventType type, game::Event *event) {
  auto winEvent = static_cast<WinGameEvent *>(event);

  m_score += winEvent->bonusScore;

  return game::EventStatus::KEEP;
}
