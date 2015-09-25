#include "Bullets.h"

#include <cassert>
#include <iostream>

#include "Config.h"
#include "Enemy.h"
#include "Hero.h"

static constexpr float RADIUS = 5.0f;

Bullets::Bullets(EventManager& events, ResourceManager &manager) 
: m_bulletBlueTexture(nullptr)
, m_bulletGreenTexture(nullptr) {
  events.registerHandler<LocationEvent>(&Bullets::onLocationEvent, this);
  events.registerHandler<ShootEvent>(&Bullets::onShootEvent, this);

  // Load the texture
  m_bulletBlueTexture = manager.getTexture("bullet_blue.png");
  assert(m_bulletBlueTexture != nullptr);

  m_bulletGreenTexture = manager.getTexture("bullet_green.png");
  assert(m_bulletGreenTexture != nullptr);
}


void Bullets::addBullet(Origin origin, const sf::Vector2f& pos, const sf::Vector2f& velocity) {
  Bullet bullet;
  bullet.origin = origin;
  bullet.pos = pos;
  bullet.velocity = velocity;
  if (origin == Origin::HERO) {
    bullet.texture = m_bulletBlueTexture;
  }
  else {
    bullet.texture = m_bulletGreenTexture;
  }
  bullet.active = true;

  m_bullets.push_back(bullet);
}

static constexpr float EXTRA = 100.0f;

void Bullets::update(float dt) {
  sf::FloatRect screen(-EXTRA, -EXTRA, WINDOW_W + 2 * EXTRA, WINDOW_H + 2 * EXTRA);

  for (Bullet& bullet : m_bullets) {
    bullet.pos += bullet.velocity * dt;

    if (!screen.contains(bullet.pos)) {
      bullet.active = false;
    }
  }

  m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [](const Bullet& b) { return !b.active; }), m_bullets.end());
}

void Bullets::render(sf::RenderWindow& window) {
  for (Bullet& bullet : m_bullets) {
    sf::CircleShape shape(RADIUS);
    shape.setOrigin(RADIUS, RADIUS);
    shape.setTexture(bullet.texture);
    shape.setPosition(bullet.pos);
    window.draw(shape);
  }
}

static bool isTargetReached(const sf::Vector2f& shipPos, const sf::Vector2f& bulletPos) {
  return shipPos.x - 30.0f <= bulletPos.x && bulletPos.x <= shipPos.x + 30.0f
      && shipPos.y - 30.0f <= bulletPos.y && bulletPos.y <= shipPos.y + 30.0f;
}

EventStatus Bullets::onLocationEvent(EventType type, Event *event) {
  assert(type == LocationEvent::type);

  auto loc = static_cast<LocationEvent*>(event);

  for (Bullet& bullet : m_bullets) {
    if (loc->origin == bullet.origin) {
      continue;
    }

    if (isTargetReached(loc->pos, bullet.pos)) {
      loc->ship->impact(10.0f);
      bullet.active = false;
    }
  }

  return EventStatus::KEEP;
}

EventStatus Bullets::onShootEvent(EventType type, Event *event) {
  auto shoot = static_cast<ShootEvent *>(event);

  addBullet(shoot->origin, shoot->pos, shoot->velocity);

  return EventStatus::KEEP;
}
