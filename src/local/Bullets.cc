#include "Bullets.h"

#include <cassert>
#include <iostream>

#include "Config.h"
#include "Enemy.h"
#include "Hero.h"

static constexpr float RADIUS = 3.0f;

Bullets::Bullets(EventManager& events) {
  events.registerHandler<HeroPositionEvent>(&Bullets::onPositionEvent, this);
  events.registerHandler<EnemyPositionEvent>(&Bullets::onPositionEvent, this);
  events.registerHandler<ShootEvent>(&Bullets::onShootEvent, this);
}


void Bullets::addBullet(Origin origin, const sf::Vector2f& pos, const sf::Vector2f& velocity, const sf::Color& color) {
  Bullet bullet;
  bullet.origin = origin;
  bullet.pos = pos;
  bullet.velocity = velocity;
  bullet.color = color;

  m_bullets.push_back(bullet);
}

static constexpr float EXTRA = 10.0f;

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
    shape.setFillColor(bullet.color);
    shape.setPosition(bullet.pos);
    window.draw(shape);
  }
}

EventStatus Bullets::onPositionEvent(EventType type, Event *event) {
  assert(type == EnemyPositionEvent::type || type == HeroPositionEvent::type);

  sf::Vector2f pos;
  Origin origin;
  Entity *entity;

  if (type == EnemyPositionEvent::type) {
    pos = static_cast<EnemyPositionEvent*>(event)->pos;
    origin = Origin::ENEMY;
    entity = static_cast<EnemyPositionEvent*>(event)->enemy;
  } else {
    pos = static_cast<HeroPositionEvent*>(event)->pos;
    origin = Origin::HERO;
    entity = static_cast<HeroPositionEvent*>(event)->hero;
  }

  for (Bullet& bullet : m_bullets) {
    if (origin == bullet.origin) {
      continue;
    }

    if (pos.x - 30.0f <= bullet.pos.x && bullet.pos.x <= pos.x + 30.0f && pos.y - 30.0f <= bullet.pos.y && bullet.pos.y <= pos.y + 30.0f) {
      std::cout << "Collision: " << entity << '\n';
      entity->kill();
      bullet.active = false;
    }
  }

  return EventStatus::KEEP;
}

EventStatus Bullets::onShootEvent(EventType type, Event *event) {
  auto shoot = static_cast<ShootEvent *>(event);

  addBullet(shoot->origin, shoot->pos, shoot->velocity, shoot->color);

  return EventStatus::KEEP;
}
