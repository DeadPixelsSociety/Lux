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
#include "Game.h"
#include "Shoot.h"

class Scenario {
public:
  Scenario(EnemyManager& manager);

  void update(float dt);

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

  std::vector<Wave> m_waves;

  float m_elapsedTime;
  std::size_t m_currentWave;
  std::size_t m_currentShip;

};


#endif // LOCAL_SCENARIO_H
