#ifndef LOCAL_STARS_H
#define LOCAL_STARS_H

#include <array>

#include "Entity.h"
#include "Random.h"

class Stars : public Entity {
public:
  static constexpr std::size_t COUNT = 100;

  Stars(Engine& engine, float velocity, float radius);

  virtual int priority() const override;

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
};


#endif // LOCAL_STARS_H
