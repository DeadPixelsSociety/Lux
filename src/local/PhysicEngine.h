#ifndef LOCAL_PHYSIC_ENGINE_H
#define LOCAL_PHYSIC_ENGINE_H

#include <vector>

#include "Bullets.h"
#include "Enemy.h"
#include "Entity.h"
class Hero;

class PhysicEngine {
public:
  PhysicEngine(Bullets &bullets);
  
  void setHero(Hero &hero);
  
  void shoot(Entity &entity, sf::Vector2f pos, sf::Vector2f velocity, sf::Color color);
    
private:
  Bullets &m_bullets;
  Hero *m_hero;
};

#endif // LOCAL_PHYSIC_ENGINE_H
