#include "Scenario.h"

#include <cstdio>

#include "Config.h"

//     sf::Vector2f pos(dist(m_engine), -Enemy::ENEMY_HEIGHT);
//     sf::Vector2f velocity(0.0f, WINDOW_H / 3.0f);

Scenario::Scenario(EnemyManager& manager)
: m_manager(manager)
, m_elapsedTime(0)
, m_currentWave(0)
, m_currentShip(0)
{
  Wave wave;
  wave.duration = 1.0f;
  wave.ships.push_back({ ShipClass::BOOTES, { WINDOW_W / 2.0f, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f });
  wave.ships.push_back({ ShipClass::BOOTES, { WINDOW_W / 2.0f, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.2f });

  m_waves.push_back(wave);
  m_waves.push_back(wave);
}

void Scenario::update(float dt) {
  m_elapsedTime += dt;

  if (m_currentWave == m_waves.size()) {
    return;
  }

  Wave& wave = m_waves[m_currentWave];

  if (m_elapsedTime > wave.duration) {
    m_elapsedTime -= wave.duration;
    m_currentWave++;
    m_currentShip = 0;
    return;
  }

  while (m_currentShip < wave.ships.size()) {
    WaveShip& waveShip = wave.ships[m_currentShip];
    if (waveShip.start < m_elapsedTime) {
      m_manager.addEnemy(waveShip.ship, waveShip.position, waveShip.velocity);
      m_currentShip++;
    } else {
      break;
    }
  }

}
