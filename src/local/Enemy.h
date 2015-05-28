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
#include "Event.h"
#include "Game.h"
#include "Group.h"
#include "Random.h"

class Enemy : public Entity {
public:
  Enemy(const sf::Vector2f& pos, const sf::Vector2f& vel, EventManager& events)
  : m_pos(pos), m_vel(vel)
  , m_events(events)
  , m_elapsedTime(0.0f)
  {
    m_events.registerHandler<HeroPositionEvent>(&Enemy::onPositionEvent, this);
  }

  virtual void update(float dt) override;

  virtual void render(sf::RenderWindow& window) override;

  static constexpr float RADIUS = 20.0f;

private:
  EventStatus onPositionEvent(EventType type, Event *event);


private:

  sf::Vector2f m_pos;
  sf::Vector2f m_vel;
  EventManager& m_events;

  float m_elapsedTime;
  sf::Vector2f m_hero_pos;
};


class EnemyManager : public Entity {
public:
  EnemyManager(Engine& engine, EventManager& events)
  : m_engine(engine)
  , m_events(events)
  , m_elapsedTime(0.0f)
  {
    m_events.registerHandler<DeadEnemyEvent>(&EnemyManager::onDeadEnemyEvent, this);
  }

  EventStatus onDeadEnemyEvent(EventType type, Event *event);

  virtual void update(float dt) override;

  virtual void render(sf::RenderWindow& window) override;

private:
  Engine& m_engine;
  EventManager& m_events;
  Group m_enemies;
  float m_elapsedTime;
};


#endif // LOCAL_ENEMY_H
