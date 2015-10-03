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
    LifeEvent lifeEvent;
    lifeEvent.life = 0.0f;
    m_events.triggerEvent(&lifeEvent);

    DeadEvent dead;
    dead.origin = Origin::HERO;
    dead.ship = ShipClass::ANTLIA;
    dead.pos = m_pos;
    m_events.triggerEvent(&dead);
    m_inGame = false;
    return;
  }

  LifeEvent lifeEvent;
  lifeEvent.life = getStructureHealthPercentage();
  m_events.triggerEvent(&lifeEvent);

  m_elapsedTime += dt;

  sf::Vector2f dir(0.0f, SHOOT_VELOCITY);
  m_shoot->shoot(dt, m_pos, dir, m_events);
}

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
