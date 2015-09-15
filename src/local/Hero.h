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
#ifndef LOCAL_HERO_H
#define LOCAL_HERO_H

#include <cassert>

#include "Entity.h"
#include "Event.h"
#include "Game.h"
#include "Resources.h"
#include "Sensor.h"
#include "Ship.h"

class Hero : public Ship {
public:
  static constexpr float HERO_WIDTH = 60.0f;
  static constexpr float HERO_HEIGHT = 60.0f;
  static constexpr float HERO_SCALE_X = HERO_WIDTH / 256.0f;
  static constexpr float HERO_SCALE_Y = HERO_HEIGHT / 256.0f;

  static constexpr float HERO_HEALTH = 100.0f;

  Hero(Sensor& sensor, EventManager& events, ResourceManager &resources)
  : Ship(HERO_HEALTH)
  , m_sensor(sensor)
  , m_events(events)
  , m_elapsedTime(0.0f)
  , m_texture(nullptr)
  , m_score(0)
  , m_font(nullptr)
  {
    m_texture = resources.getTexture("ship_antlia.png");
    assert(m_texture != nullptr);

    m_font = resources.getFont("jupiter.ttf");
    assert(m_font != nullptr);
    
    m_events.registerHandler<DeadEvent>(&Hero::onDeadEvent, this);
  }

  virtual void update(float dt) override;

  virtual void render(sf::RenderWindow& window) override;

  EventStatus onDeadEvent(EventType type, Event *event);

private:
  sf::Vector2f m_pos;
  Sensor& m_sensor;
  EventManager& m_events;
  float m_elapsedTime;
  sf::Texture *m_texture;
  unsigned long long int m_score;
  sf::Font *m_font;
};


#endif // LOCAL_HERO_H
