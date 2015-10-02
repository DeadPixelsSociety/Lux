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

#include <game/Entity.h>

#include "Enemy.h"
#include "Game.h"
#include "Shoot.h"

class Scenario : public game::Entity {
public:
  Scenario(EnemyManager& manager, game::EventManager& events, game::ResourceManager &resources);

  virtual void update(float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  game::EventStatus onScoreEvent(game::EventType type, game::Event *event) {
    auto scoreEvent = static_cast<ScoreEvent *>(event);

    m_currentScore = scoreEvent->score;

    return game::EventStatus::KEEP;
  }

  game::EventStatus onDeadEvent(game::EventType type, game::Event *event);

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
  struct Score {
    Score(int idPlayer, int score) 
    : idPlayer(idPlayer)
    , score(score) {
      
    }

    unsigned int idPlayer;
    unsigned int score;
  };

private:
  static unsigned int m_currentPlayer;

  EnemyManager& m_manager;
  game::EventManager& m_events;

  std::vector<Wave> m_waves;

  float m_elapsedTime;
  std::size_t m_currentWave;
  std::size_t m_currentShip;
  sf::Font *m_font;

  unsigned int m_currentScore;
  bool m_win;
  std::vector<Score> m_highScore;
  bool m_updateScore;
};


#endif // LOCAL_SCENARIO_H
