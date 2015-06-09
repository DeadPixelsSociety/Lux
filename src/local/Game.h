#ifndef LOCAL_GAME_H
#define LOCAL_GAME_H

#include <SFML/Graphics.hpp>

#include "Event.h"

class Hero;

struct HeroPositionEvent : public Event {
  static const EventType type = "HeroPositionEvent"_type;
  sf::Vector2f pos;
  Hero *hero;
};

class Enemy;

struct EnemyPositionEvent : public Event {
  static const EventType type = "EnemyPositionEvent"_type;
  sf::Vector2f pos;
  Enemy *enemy;
};

enum class Origin {
  HERO,
  ENEMY,
};

struct ShootEvent : public Event {
  static const EventType type = "ShootEvent"_type;
  Origin origin;
  sf::Vector2f pos;
  sf::Vector2f velocity;
  sf::Color color;
};

struct DeadEvent : public Event {
  static const EventType type = "DeadEvent"_type;
  Origin origin;
  sf::Vector2f pos;
};

#endif // LOCAL_GAME_H
