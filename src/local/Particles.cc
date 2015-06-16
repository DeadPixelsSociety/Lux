#include "Particles.h"

#include <cmath>

Particles::Particles(EventManager& events, Engine& engine)
: m_engine(engine)
{
  events.registerHandler<DeadEvent>(&Particles::onDeadEvent, this);
}

int Particles::priority() const {
  return 1;
}

void Particles::update(float dt) {
  for (ParticleSystem& sys : m_particles_systems) {
    sys.elapsed += dt;

    // If it's end of animation
    if (sys.elapsed >= sys.lifetime) {
      continue;
    }

    for (std::size_t i = 0; i < sys.particles.size(); ++i) {
      Particle& p = sys.particles[i];
      p.lifetime -= dt;

      if (p.lifetime < 0.0f) {
        sys.vertices[i].color.a = 0x00;
        continue;
      }

      sys.vertices[i].position += p.velocity * dt;

      float ratio = (p.lifetime + 2) / (sys.lifetime + 2);
      sys.vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
  }

  // Delete the old animations
  const auto trash = std::partition(m_particles_systems.begin(), m_particles_systems.end(), [](const ParticleSystem &sys) {
    return sys.elapsed < sys.lifetime;
  });

  m_particles_systems.erase(trash, m_particles_systems.end());
}

void Particles::render(sf::RenderWindow& window) {
  for (ParticleSystem& sys : m_particles_systems) {
    window.draw(sys.vertices);
  }
}

static constexpr std::size_t PARTICLES_COUNT = 400;
static constexpr float LIFETIME_MAX = 1.5f;
static constexpr float LIFETIME_MIN = 0.1f;


EventStatus Particles::onDeadEvent(EventType type, Event *event) {
  auto dead = static_cast<DeadEvent*>(event);

  ParticleSystem sys;

  sys.vertices.resize(PARTICLES_COUNT);
  sys.vertices.setPrimitiveType(sf::Points);
  sys.elapsed = 0.0f;

  std::uniform_real_distribution<float> dist_angle(0, 2 * 3.1415926f);
  std::uniform_real_distribution<float> dist_norm(0.0f, 150.0f);
  std::uniform_real_distribution<float> dist_lifetime(0.0f, 100.0f);

  for (std::size_t i = 0; i < PARTICLES_COUNT; ++i) {
    Particle p;

    float aleaNumber = dist_lifetime(m_engine);
    if (aleaNumber < 50.0f) 
      p.lifetime = 0.2f * (aleaNumber / 50.0f);
    else if (aleaNumber < 75.0f) 
      p.lifetime = 0.8f * (aleaNumber / 75.0f);
    else 
      p.lifetime = 1.5f * (aleaNumber / 100.0f);

    //p.lifetime = dist_lifetime(m_engine);

    float angle = dist_angle(m_engine);
    float norm = dist_norm(m_engine);

    p.velocity.x = norm * std::cos(angle);
    p.velocity.y = norm * std::sin(angle);

    sys.particles.push_back(p);

    sys.vertices[i].position = dead->pos;
    sys.vertices[i].color = sf::Color(0xFF, 0xA0, 0x00);
  }

  sys.lifetime = LIFETIME_MAX;

  m_particles_systems.push_back(sys);
  return EventStatus::KEEP;
}
