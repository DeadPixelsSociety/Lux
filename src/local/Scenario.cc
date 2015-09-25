#include "Scenario.h"

#include "Config.h"

static Scenario::Wave wave0 {
  5.0f,
  {
  }
};

// two at the same time
static Scenario::Wave wave01 {
  5.0f,
  {
    { ShipClass::BOOTES, { 0.3f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.7f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
  }
};

// alternate left/right
static Scenario::Wave wave02 {
  6.0f,
  {
    { ShipClass::BOOTES, { 0.3f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.7f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 1.0f },
    { ShipClass::BOOTES, { 0.3f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 2.0f },
    { ShipClass::BOOTES, { 0.7f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 3.0f },
  }
};

// stairs
static Scenario::Wave wave03 {
  6.0f,
  {
    { ShipClass::BOOTES, { 0.2f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.4f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 1.0f },
    { ShipClass::BOOTES, { 0.6f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 2.0f },
    { ShipClass::BOOTES, { 0.8f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 3.0f },
  }
};

// cross
static Scenario::Wave wave04 {
  4.0f,
  {
    { ShipClass::BOOTES, { 0.1f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.9f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { -WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.0f },
  }
};

static Scenario::Wave wave10 {
  4.0f,
  {
    { ShipClass::CYGNUS, { 0.3f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
  }
};

static Scenario::Wave wave11 {
  4.0f,
  {
    { ShipClass::CYGNUS, { 0.5f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.2f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.5f },
    { ShipClass::CYGNUS, { 0.8f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.5f },
  }
};

static Scenario::Wave wave12 {
  5.0f,
  {
    { ShipClass::CYGNUS, { 0.05f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.95f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { -WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.5f },
    { ShipClass::CYGNUS, { 0.5f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 1.0f },
  }

};

// diagonal
static Scenario::Wave wave13 {
  4.0f,
  {
    { ShipClass::CYGNUS, { 0.05f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.15f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.0f },
  }
};

// anti-diagonal
static Scenario::Wave wave14 {
  4.0f,
  {
    { ShipClass::CYGNUS, { 0.85f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { -WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.95f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { -WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.0f },
  }
};

// diagonal and anti-diagonal
static Scenario::Wave wave15 {
  5.0f,
  {
    { ShipClass::CYGNUS, { 0.05f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.15f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.85f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { -WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.5f },
    { ShipClass::CYGNUS, { 0.95f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { -WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.5f },
  }
};

// cross
static Scenario::Wave wave20 {
  4.0f,
  {
    { ShipClass::DRACO, { 0.1f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::DRACO, { 0.9f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { -WINDOW_H / 3.0f, WINDOW_H / 3.0f }, 0.0f },
  }
};

// double stairs of death
static Scenario::Wave wave32 {
  4.0f,
  {
    { ShipClass::ERIDANUS, { 0.2f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.5f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.4f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.5f },
    { ShipClass::ERIDANUS, { 0.7f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.5f },
    { ShipClass::ERIDANUS, { 0.6f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 1.0f },
    { ShipClass::ERIDANUS, { 0.9f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 1.0f },
  }
};

// super 7 squad
static Scenario::Wave wave33 {
  4.0f,
  {
    { ShipClass::ERIDANUS, { 0.2f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.3f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.4f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.5f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.6f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.7f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.8f * WINDOW_W, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
  }
};

// static Scenario::Wave waveN {
//   10.0f,
//   {
//     { ShipClass::BOOTES, { WINDOW_W / 2.0f, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 0.0f },
//     { ShipClass::CYGNUS, { WINDOW_W / 2.0f, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 1.5f },
//     { ShipClass::DRACO, { WINDOW_W / 2.0f, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 3.0f },
//     { ShipClass::ERIDANUS, { WINDOW_W / 2.0f, -Enemy::ENEMY_HEIGHT }, { 0.0f, WINDOW_H / 3.0f }, 4.5f },
//   }
// };


Scenario::Scenario(EnemyManager& manager, EventManager& events, ResourceManager &resources)
: m_manager(manager)
, m_events(events)
, m_elapsedTime(0)
, m_currentWave(0)
, m_currentShip(0)
, m_font(nullptr)
, m_win(true)
, m_highScore({0, 0, 0, 0, 0})
, m_updateScore(true)
{
  m_events.registerHandler<ScoreEvent>(&Scenario::onScoreEvent, this);
  m_events.registerHandler<DeadEvent>(&Scenario::onDeadEvent, this);

  m_waves.push_back(wave0);

  m_waves.push_back(wave01);
  m_waves.push_back(wave01);
  m_waves.push_back(wave02);
  m_waves.push_back(wave02);
  m_waves.push_back(wave03);
  m_waves.push_back(wave04);

  m_waves.push_back(wave10);
  m_waves.push_back(wave11);
  m_waves.push_back(wave12);
  m_waves.push_back(wave13);
  m_waves.push_back(wave14);
  m_waves.push_back(wave15);

  m_waves.push_back(wave20);

  m_waves.push_back(wave32);
  m_waves.push_back(wave33);

  m_waves.push_back(wave0);

  m_font = resources.getFont("jupiter.ttf");
  assert(m_font != nullptr);
}

static constexpr const float MENU_TIME = 15.0f;

void Scenario::update(float dt) {
  m_elapsedTime += dt;

  // End of game
  if (m_currentWave == m_waves.size()) {
    if (m_updateScore && m_win) {
      // Add the new high score
      m_highScore.push_back(m_currentScore);

      // Remove the lower score
      std::sort(m_highScore.begin(), m_highScore.end(), std::greater<unsigned int>());
      m_highScore.erase(m_highScore.end() - 1);
      m_updateScore = false;
    }
    if (m_elapsedTime > MENU_TIME)
    {
      m_elapsedTime = 0.0f;
      m_currentWave = 0;
      m_currentShip = 0;
      m_win = true;
      RestartGameEvent event;
      m_events.triggerEvent(&event);
      m_updateScore = true;
    }
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

void Scenario::render(sf::RenderWindow& window) {
  if (m_currentWave != m_waves.size()) {
    return;
  }

  sf::Text text;
  text.setFont(*m_font);
  std::string message;
  if (m_win) {
    message = "Bravo ! Vous avez fini le jeu.\n";
  }
  else {
    message = "Dommage ! Vous avez perdu le jeu.\n";
  }
  text.setString(message + "Votre score est de : " + std::to_string(m_currentScore) + "\nLa nouvelle partie commence dans : " + std::to_string(std::lround(MENU_TIME - m_elapsedTime)));
  text.setCharacterSize(30);
  text.setColor(sf::Color::White);

  // Display the high score
  text.setString(text.getString() + "\n\nMeilleur score :");
  for (unsigned int i = 0; i < m_highScore.size(); ++i) {
    text.setString(text.getString() + "\n" + std::to_string(i + 1) + " - " + std::to_string(m_highScore[i]));
  }

  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  text.setPosition(WINDOW_W / 2.0f, WINDOW_H / 2.0f);

  window.draw(text);
}

EventStatus Scenario::onDeadEvent(EventType type, Event *event) {
  auto dead = static_cast<DeadEvent *>(event);

  if (dead->origin != Origin::HERO) {
    return EventStatus::KEEP;
  }

  // Jump to end
  m_currentWave = m_waves.size() - 1;
  m_elapsedTime = 0.0f;
  m_win = false;

  return EventStatus::KEEP;
}
