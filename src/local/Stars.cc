#include "Stars.h"

#include <cstdio>

#include "Config.h"

// static constexpr float VELOCITY_MIN = 30.0;
// static constexpr float VELOCITY_MAX = 50.0;


Stars::Stars(Engine& engine, float velocity, float radius)
: m_engine(engine)
, m_velocity(velocity)
, m_radius(radius)
{

  std::uniform_real_distribution<float> dist_x(0.0, WINDOW_W);
  std::uniform_real_distribution<float> dist_y(0.0, WINDOW_H);

  for (Star& star : m_stars) {
    star.pos.x = dist_x(m_engine);
    star.pos.y = dist_y(m_engine);
    star.color = sf::Color::White;
  }
}

int Stars::priority() const {
  return -1;
}

void Stars::update(float dt) {
  std::uniform_real_distribution<float> dist_x(0.0, WINDOW_W);

  for (Star& star : m_stars) {
    if (star.pos.y > WINDOW_H) {
      star.pos.x = dist_x(m_engine);
      star.pos.y = -1;
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
