#ifndef LOCAL_PARTICLES_H
#define LOCAL_PARTICLES_H

#include "Entity.h"
#include "Game.h"
#include "Random.h"

class Particles : public Entity {
public:
  Particles(EventManager& events, Engine& engine);

  virtual int priority() const;

  virtual void update(float dt) override;
  virtual void render(sf::RenderWindow& window) override;

private:
  EventStatus onDeadEvent(EventType type, Event *event);

private:
  struct Particle {
    sf::Vector2f velocity;
    float lifetime;
  };

  struct ParticleSystem {
    std::vector<Particle> particles;
    sf::VertexArray vertices;
    float lifetime;
  };

  Engine& m_engine;
  std::vector<ParticleSystem> m_particles_systems;
};


#endif // LOCAL_PARTICLES_H
