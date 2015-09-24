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

#include <vector>

#include "Entity.h"
#include "Event.h"
#include "Game.h"
#include "Random.h"
#include "Resources.h"
#include "Ship.h"
#include "Shoot.h"

class Enemy : public Ship {
public:
  static constexpr float ENEMY_WIDTH = 60.0f;
  static constexpr float ENEMY_HEIGHT = 60.0f;
  static constexpr float ENEMY_SCALE_X = ENEMY_WIDTH / 64.0f;
  static constexpr float ENEMY_SCALE_Y = ENEMY_HEIGHT / 64.0f;

  Enemy(ShipClass ship, const sf::Vector2f& pos, const sf::Vector2f& vel, float health, Engine& engine, EventManager& events, ResourceManager &resources);

  virtual void update(float dt) override;

  virtual void render(sf::RenderWindow& window) override;

  void setHeroPosition(const sf::Vector2f& pos) {
    m_hero_pos = pos;
  }

private:
  sf::Vector2f m_pos;
  sf::Vector2f m_vel;
  Engine& m_engine;
  EventManager& m_events;

  float m_elapsedTime;
  sf::Vector2f m_hero_pos;
  sf::Texture *m_texture;

  std::unique_ptr<Shoot> m_shoot;
};


class EnemyManager : public Entity {
public:
  EnemyManager(Engine& engine, EventManager& events, ResourceManager &resources)
  : m_engine(engine)
  , m_events(events)
  , m_elapsedTime(0.0f)
  , m_resources(resources)
  {
    m_events.registerHandler<LocationEvent>(&EnemyManager::onLocationEvent, this);
  }

  EnemyManager(const EnemyManager&) = delete;
  EnemyManager& operator=(const EnemyManager&) = delete;

  EnemyManager(EnemyManager&&) = delete;
  EnemyManager& operator=(EnemyManager&&) = delete;

  ~EnemyManager();


  void addEnemy(ShipClass ship, const sf::Vector2f& position, const sf::Vector2f& velocity);

  EventStatus onLocationEvent(EventType type, Event *event);

  virtual void update(float dt) override;

  virtual void render(sf::RenderWindow& window) override;

private:
  Engine& m_engine;
  EventManager& m_events;
  std::vector<Enemy*> m_enemies;
  float m_elapsedTime;
  ResourceManager& m_resources;
  sf::Vector2f m_hero_pos;
};


#endif // LOCAL_ENEMY_H
