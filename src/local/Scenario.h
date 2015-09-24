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
#ifndef LOCAL_SCENARIO_H
#define LOCAL_SCENARIO_H

#include <vector>

#include "Enemy.h"
#include "Entity.h"
#include "Game.h"
#include "Shoot.h"

class Scenario : public Entity {
public:
  Scenario(EnemyManager& manager, EventManager& events, ResourceManager &resources);

  virtual void update(float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  EventStatus onScoreEvent(EventType type, Event *event) {
    auto scoreEvent = static_cast<ScoreEvent *>(event);

    m_currentScore = scoreEvent->score;

    return EventStatus::KEEP;
  }

  EventStatus onDeadEvent(EventType type, Event *event);

  struct WaveShip {
    ShipClass ship;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float start;
  };

  struct Wave {
    float duration;
    std::vector<WaveShip> ships;
  };


private:
  EnemyManager& m_manager;
  EventManager& m_events;

  std::vector<Wave> m_waves;

  float m_elapsedTime;
  std::size_t m_currentWave;
  std::size_t m_currentShip;
  sf::Font *m_font;

  unsigned int m_currentScore;
  bool m_win;
  std::vector<unsigned int> m_highScore;
};


#endif // LOCAL_SCENARIO_H
