#include "Bullets.h"

#include <iostream>

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

void Bullets::update(float dt) {
  for (Bullet& bullet : m_bullets) {
    bullet.pos += bullet.velocity * dt;
  }
}

void Bullets::render(sf::RenderWindow& window) {
  for (Bullet bullet : m_bullets) {
    sf::CircleShape shape(RADIUS);
    shape.setOrigin(RADIUS, RADIUS);
    shape.setFillColor(bullet.color);
    shape.setPosition(bullet.pos);
    window.draw(shape);
  }
}

EventStatus Bullets::onPositionEvent(EventType type, Event *event) {

  

  return EventStatus::KEEP;
}

EventStatus Bullets::onShootEvent(EventType type, Event *event) {
  auto shoot = static_cast<ShootEvent *>(event);

  addBullet(shoot->origin, shoot->pos, shoot->velocity, shoot->color);

  return EventStatus::KEEP;
}
