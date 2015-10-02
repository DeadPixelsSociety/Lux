#include "Stars.h"

#include <cstdio>

// static constexpr float VELOCITY_MIN = 30.0;
// static constexpr float VELOCITY_MAX = 50.0;

static constexpr float AREA_WIDTH = 800;
static constexpr float AREA_HEIGHT = 600;

Stars::Stars(Engine& engine, float velocity, float radius, bool lastPlan)
: game::Entity(-1)
, m_engine(engine)
, m_velocity(velocity)
, m_radius(radius)
, m_lastPlan(lastPlan)
{
  std::uniform_real_distribution<float> dist_x(0.0, AREA_WIDTH);
  std::uniform_real_distribution<float> dist_y(0.0, AREA_HEIGHT);
  std::uniform_real_distribution<float> dist_frequency(0.0, 1.0);
  std::uniform_int_distribution<int> dist_red(50, 255);
  std::uniform_int_distribution<int> dist_blue(0, 255);

  for (Star& star : m_stars) {
    star.pos.x = dist_x(m_engine);
    star.pos.y = dist_y(m_engine);
    if (m_lastPlan || dist_frequency(m_engine) < FREQUENCY_WHITE_STAR) {
      star.color = sf::Color::White;
    }
    else {
      star.color = sf::Color(dist_red(m_engine), 0, dist_blue(m_engine));
    }
  }
}

void Stars::update(float dt) {
  std::uniform_real_distribution<float> dist_x(0.0, AREA_WIDTH);
  std::uniform_real_distribution<float> dist_frequency(0.0, 1.0);
  std::uniform_int_distribution<int> dist_red(50, 255);
  std::uniform_int_distribution<int> dist_blue(0, 255);

  for (Star& star : m_stars) {
    if (star.pos.y > AREA_HEIGHT) {
      star.pos.x = dist_x(m_engine);
      star.pos.y = -1;
      if (m_lastPlan || dist_frequency(m_engine) < FREQUENCY_WHITE_STAR) {
        star.color = sf::Color::White;
      }
      else {
        star.color = sf::Color(dist_red(m_engine), 0, dist_blue(m_engine));
      }
    }

    star.pos.y += m_velocity * dt;
  }
}

void Stars::render(sf::RenderWindow& window)  {
  sf::CircleShape shape(m_radius);
  shape.setOrigin(m_radius, m_radius);

  for (Star& star : m_stars) {
    shape.setPosition(star.pos);
    shape.setFillColor(star.color);
    window.draw(shape);
  }
}
