#include "Particles.h"

#include <cmath>

Particles::Particles(game::EventManager& events, Engine& engine)
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

      float ratio = 0.75f + 0.25f * p.lifetime / sys.lifetime;
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

std::tuple<sf::Color, sf::Color> colorFromShipClass(ShipClass ship) {
  switch (ship) {
    case ShipClass::ANTLIA:
      return std::make_tuple(sf::Color(0x8C, 0xED, 0xDC), sf::Color(0x5D, 0x7F, 0x83));
    case ShipClass::BOOTES:
    case ShipClass::CYGNUS:
    case ShipClass::DRACO:
    case ShipClass::ERIDANUS:
      return std::make_tuple(sf::Color(0x7C, 0xBE, 0x41), sf::Color(0xB6, 0x0B, 0x0B));
  }

  return std::make_tuple(sf::Color::White, sf::Color::White);
}

static constexpr std::size_t PARTICLES_COUNT = 800;
static constexpr float LIFETIME_MAX = 1.5f;
static constexpr float LIFETIME_MIN = 0.1f;


game::EventStatus Particles::onDeadEvent(game::EventType type, game::Event *event) {
  auto dead = static_cast<DeadEvent*>(event);

  ParticleSystem sys;

  sys.vertices.resize(PARTICLES_COUNT);
  sys.vertices.setPrimitiveType(sf::Points);

  std::uniform_real_distribution<float> dist_angle(0, 2 * 3.1415926f);
  std::uniform_real_distribution<float> dist_norm(0.0f, 150.0f);
  std::normal_distribution<float> dist_lifetime(1.0f, 0.166f);
  std::bernoulli_distribution dist_color(0.6);

  sf::Color major;
  sf::Color minor;

  std::tie(major, minor) = colorFromShipClass(dead->ship);

  for (std::size_t i = 0; i < PARTICLES_COUNT; ++i) {
    Particle p;

    p.lifetime = dist_lifetime(m_engine);

    float angle = dist_angle(m_engine);
    float norm = dist_norm(m_engine);

    p.velocity.x = norm * std::cos(angle);
    p.velocity.y = norm * std::sin(angle);

    sys.particles.push_back(p);

    sys.vertices[i].position = dead->pos;
    sys.vertices[i].color = dist_color(m_engine) ? major : minor;
  }

  sys.elapsed = 0.0f;
  sys.lifetime = LIFETIME_MAX;

  m_particles_systems.push_back(sys);
  return game::EventStatus::KEEP;
}
