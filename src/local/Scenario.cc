#include "Scenario.h"

unsigned int Scenario::m_currentPlayer = 1;

static constexpr float AREA_WIDTH = 800;
static constexpr float AREA_HEIGHT = 600;

static Scenario::Wave wave0 {
  5.0f,
  {
  }
};

// two at the same time
static Scenario::Wave wave01 {
  5.0f,
  {
    { ShipClass::BOOTES, { 0.3f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.7f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

// alternate left/right
static Scenario::Wave wave02 {
  6.0f,
  {
    { ShipClass::BOOTES, { 0.3f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.7f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 1.0f },
    { ShipClass::BOOTES, { 0.3f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 2.0f },
    { ShipClass::BOOTES, { 0.7f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 3.0f },
  }
};

// stairs
static Scenario::Wave wave03 {
  6.0f,
  {
    { ShipClass::BOOTES, { 0.2f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.4f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 1.0f },
    { ShipClass::BOOTES, { 0.6f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 2.0f },
    { ShipClass::BOOTES, { 0.8f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 3.0f },
  }
};

// cross
static Scenario::Wave wave04 {
  4.0f,
  {
    { ShipClass::BOOTES, { 0.1f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.9f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

// Line
static Scenario::Wave wave05 {
  4.0f,
  {
    { ShipClass::BOOTES, { 0.2f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.3f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.4f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.5f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.6f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.7f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::BOOTES, { 0.8f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

static Scenario::Wave wave10 {
  4.0f,
  {
    { ShipClass::CYGNUS, { 0.5f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

static Scenario::Wave wave11 {
  4.0f,
  {
    { ShipClass::CYGNUS, { 0.5f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.2f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.5f },
    { ShipClass::CYGNUS, { 0.8f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.5f },
  }
};

static Scenario::Wave wave12 {
  5.0f,
  {
    { ShipClass::CYGNUS, { 0.05f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.95f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.5f },
    { ShipClass::CYGNUS, { 0.5f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 1.0f },
  }

};

// diagonal
static Scenario::Wave wave13 {
  4.0f,
  {
    { ShipClass::CYGNUS, { 0.05f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.15f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

// anti-diagonal
static Scenario::Wave wave14 {
  4.0f,
  {
    { ShipClass::CYGNUS, { 0.85f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.95f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

// diagonal and anti-diagonal
static Scenario::Wave wave15 {
  5.0f,
  {
    { ShipClass::CYGNUS, { 0.05f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.15f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.85f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.5f },
    { ShipClass::CYGNUS, { 0.95f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.5f },
  }
};

// V squad
static Scenario::Wave wave16 {
  8.0f,
  {
    { ShipClass::CYGNUS, { 0.50f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::CYGNUS, { 0.35f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.3f },
    { ShipClass::CYGNUS, { 0.65f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.3f },
    { ShipClass::CYGNUS, { 0.20f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.6f },
    { ShipClass::CYGNUS, { 0.80f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.6f },
  }
};

static Scenario::Wave wave20 {
  4.0f,
  {
    { ShipClass::DRACO, { 0.5f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

// cross
static Scenario::Wave wave21 {
  4.0f,
  {
    { ShipClass::DRACO, { 0.1f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::DRACO, { 0.9f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

// alternate left/right
static Scenario::Wave wave22 {
  6.0f,
  {
    { ShipClass::DRACO, { 0.3f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::DRACO, { 0.7f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 1.0f },
    { ShipClass::DRACO, { 0.3f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 2.0f },
    { ShipClass::DRACO, { 0.7f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 3.0f },
  }
};

// anti-diagonal
static Scenario::Wave wave23 {
  6.0f,
  {
    { ShipClass::DRACO, { 0.95f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::DRACO, { 0.95f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.5f },
    { ShipClass::DRACO, { 0.95f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 1.0f },
    { ShipClass::DRACO, { 0.95f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 1.5f },
  }
};

// alternate left/right
static Scenario::Wave wave24 {
  6.0f,
  {
    { ShipClass::DRACO, { 0.3f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::DRACO, { 0.7f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 1.0f },
    { ShipClass::DRACO, { 0.3f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 2.0f },
    { ShipClass::DRACO, { 0.7f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 3.0f },
  }
};

// double stairs of death
static Scenario::Wave wave25 {
  4.0f,
  {
    { ShipClass::DRACO, { 0.2f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::DRACO, { 0.5f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::DRACO, { 0.4f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.5f },
    { ShipClass::DRACO, { 0.7f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.5f },
    { ShipClass::DRACO, { 0.6f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 1.0f },
    { ShipClass::DRACO, { 0.9f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 1.0f },
  }
};

static Scenario::Wave wave30 {
  4.0f,
  {
    { ShipClass::ERIDANUS, { 0.5f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

// diagonal
static Scenario::Wave wave31 {
  4.0f,
  {
    { ShipClass::ERIDANUS, { 0.05f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.15f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

// cross
static Scenario::Wave wave32 {
  4.0f,
  {
    { ShipClass::ERIDANUS, { 0.1f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.9f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

// diagonal and anti-diagonal
static Scenario::Wave wave33 {
  5.0f,
  {
    { ShipClass::ERIDANUS, { 0.05f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.15f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.85f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.5f },
    { ShipClass::ERIDANUS, { 0.95f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { -AREA_HEIGHT / 3.0f, AREA_HEIGHT / 3.0f }, 0.5f },
  }
};

// V squad
static Scenario::Wave wave34 {
  8.0f,
  {
    { ShipClass::ERIDANUS, { 0.50f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.35f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.3f },
    { ShipClass::ERIDANUS, { 0.65f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.3f },
    { ShipClass::ERIDANUS, { 0.20f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.6f },
    { ShipClass::ERIDANUS, { 0.80f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.6f },
  }
};

// double stairs of death
static Scenario::Wave wave35 {
  4.0f,
  {
    { ShipClass::ERIDANUS, { 0.2f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.5f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.4f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.5f },
    { ShipClass::ERIDANUS, { 0.7f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.5f },
    { ShipClass::ERIDANUS, { 0.6f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 1.0f },
    { ShipClass::ERIDANUS, { 0.9f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 1.0f },
  }
};

// super 7 squad
static Scenario::Wave wave36 {
  4.0f,
  {
    { ShipClass::ERIDANUS, { 0.2f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.3f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.4f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.5f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.6f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.7f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
    { ShipClass::ERIDANUS, { 0.8f * AREA_WIDTH, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
  }
};

// static Scenario::Wave waveN {
//   10.0f,
//   {
//     { ShipClass::BOOTES, { AREA_WIDTH / 2.0f, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 0.0f },
//     { ShipClass::CYGNUS, { AREA_WIDTH / 2.0f, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 1.5f },
//     { ShipClass::DRACO, { AREA_WIDTH / 2.0f, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 3.0f },
//     { ShipClass::ERIDANUS, { AREA_WIDTH / 2.0f, -Enemy::ENEMY_HEIGHT }, { 0.0f, AREA_HEIGHT / 3.0f }, 4.5f },
//   }
// };


Scenario::Scenario(EnemyManager& manager, game::EventManager& events, game::ResourceManager &resources)
: m_manager(manager)
, m_events(events)
, m_elapsedTime(0)
, m_currentWave(0)
, m_currentShip(0)
, m_font(nullptr)
, m_win(true)
, m_highScore({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}})
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
  m_waves.push_back(wave05);

  m_waves.push_back(wave10);
  m_waves.push_back(wave11);
  m_waves.push_back(wave12);
  m_waves.push_back(wave13);
  m_waves.push_back(wave14);
  m_waves.push_back(wave15);
  m_waves.push_back(wave16);

  m_waves.push_back(wave20);
  m_waves.push_back(wave21);
  m_waves.push_back(wave22);
  m_waves.push_back(wave23);
  m_waves.push_back(wave24);
  m_waves.push_back(wave25);

  m_waves.push_back(wave30);
  m_waves.push_back(wave31);
  m_waves.push_back(wave32);
  m_waves.push_back(wave01);
  m_waves.push_back(wave33);
  m_waves.push_back(wave02);
  m_waves.push_back(wave34);
  m_waves.push_back(wave12);
  m_waves.push_back(wave35);
  m_waves.push_back(wave36);

  m_waves.push_back(wave0);

  m_font = resources.getFont("jupiter.ttf");
  assert(m_font != nullptr);
}

static constexpr const float MENU_TIME = 15.0f;
static constexpr const unsigned int WIN_BONUS_SCORE = 5000;

void Scenario::update(float dt) {
  m_elapsedTime += dt;

  // End of game
  if (m_currentWave == m_waves.size()) {
    if (m_updateScore) {
      // If the player win, add the bonus score
      if (m_win) {
        WinGameEvent event;
        event.bonusScore = WIN_BONUS_SCORE;
        m_events.triggerEvent(&event);
        m_currentScore += WIN_BONUS_SCORE;
      }

      Score heightScore(m_currentPlayer, m_currentScore);

      // Add the new high score
      m_highScore.push_back(heightScore);

      // Remove the lower score
      std::sort(m_highScore.begin(), m_highScore.end(), [](Score a, Score b) {
        return a.score > b.score;
      });
      m_highScore.erase(m_highScore.end() - 1);
      m_updateScore = false;
    }
    if (m_elapsedTime > MENU_TIME)
    {
      m_elapsedTime = 0.0f;
      m_currentWave = 0;
      m_currentShip = 0;
      m_win = true;
      m_currentPlayer++;
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
    message = "Bravo joueur #" + std::to_string(m_currentPlayer) + " ! Vous avez fini le jeu.\n";
    message += "Vous gagnez un bonus de " + std::to_string(WIN_BONUS_SCORE) + "\n";
  }
  else {
    message = "Dommage joueur #" + std::to_string(m_currentPlayer) + " ! Vous avez perdu le jeu.\n";
  }

  text.setString(message + "Votre score est de : " + std::to_string(m_currentScore) + "\nLa nouvelle partie commence dans : " + std::to_string(static_cast<int>(MENU_TIME - m_elapsedTime)));

  text.setCharacterSize(30);
  text.setColor(sf::Color::White);

  // Display the high score
  text.setString(text.getString() + "\n\nMeilleur score :");
  for (unsigned int i = 0; i < m_highScore.size(); ++i) {
    text.setString(text.getString() + "\n" + std::to_string(i + 1) + " - Joueur #" + std::to_string(m_highScore[i].idPlayer) + " : " + std::to_string(m_highScore[i].score));
  }

  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  text.setPosition(AREA_WIDTH / 2.0f, AREA_HEIGHT / 2.0f);

  window.draw(text);
}

game::EventStatus Scenario::onDeadEvent(game::EventType type, game::Event *event) {
  auto dead = static_cast<DeadEvent *>(event);

  if (dead->origin != Origin::HERO) {
    return game::EventStatus::KEEP;
  }

  // Jump to end
  m_currentWave = m_waves.size() - 1;
  m_elapsedTime = 0.0f;
  m_win = false;

  return game::EventStatus::KEEP;
}
