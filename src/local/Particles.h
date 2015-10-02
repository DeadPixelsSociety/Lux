#ifndef LOCAL_PARTICLES_H
#define LOCAL_PARTICLES_H

#include <game/Entity.h>
#include <game/EventManager.h>

#include "Game.h"
#include "Random.h"

class Particles : public game::Entity {
public:
  Particles(game::EventManager& events, Engine& engine);

  virtual int priority() const;

  virtual void update(float dt) override;
  virtual void render(sf::RenderWindow& window) override;

private:
  game::EventStatus onDeadEvent(game::EventType type, game::Event *event);

private:
  struct Particle {
    sf::Vector2f velocity;
    float lifetime;
  };

  struct ParticleSystem {
    std::vector<Particle> particles;
    sf::VertexArray vertices;
    float lifetime;
    float elapsed;
  };

  Engine& m_engine;
  std::vector<ParticleSystem> m_particles_systems;
};


#endif // LOCAL_PARTICLES_H
