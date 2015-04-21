#include "PhysicEngine.h"

#include "Hero.h"

PhysicEngine::PhysicEngine(Bullets &bullets) 
: m_bullets(bullets)
, m_hero(nullptr) {
  //ctor
}

void PhysicEngine::setHero(Hero &hero) {
  m_hero = &hero;
}

void PhysicEngine::shoot(Entity &entity, sf::Vector2f pos, sf::Vector2f velocity, sf::Color color) {
  m_bullets.addBullet(pos, velocity, color);
}
