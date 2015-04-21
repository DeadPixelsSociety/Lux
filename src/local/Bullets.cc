#include "Bullets.h"

static constexpr float RADIUS = 1.0f;

void Bullets::addBullet(const sf::Vector2f& pos, const sf::Vector2f& velocity, const sf::Color& color) {
  Bullet bullet;
  bullet.pos = pos;
  bullet.velocity = velocity;
  bullet.color = color;
  
  m_bullets.push_back(bullet);
}

void Bullets::update(float dt) {
  for (Bullet bullet : m_bullets) {
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
