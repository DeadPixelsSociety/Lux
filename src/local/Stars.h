#ifndef LOCAL_STARS_H
#define LOCAL_STARS_H

#include <array>

#include <game/Entity.h>

#include "Random.h"

class Stars : public game::Entity {
public:
  static constexpr std::size_t COUNT = 50;
  static constexpr float FREQUENCY_WHITE_STAR = 0.25f;

  Stars(Engine& engine, float velocity, float radius, bool lastPlan = false);

  virtual void update(float dt) override;
  virtual void render(sf::RenderWindow& window) override;

private:
  struct Star {
    sf::Vector2f pos;
    sf::Color color;
  };

  Engine& m_engine;
  float m_velocity;
  float m_radius;
  std::array<Star, COUNT> m_stars;
  bool m_lastPlan;
};


#endif // LOCAL_STARS_H
