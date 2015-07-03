#ifndef LOCAL_GAME_H
#define LOCAL_GAME_H

#include <SFML/Graphics.hpp>

#include "Event.h"
#include "Entity.h"
#include "Ship.h"

enum class Origin {
  HERO,
  ENEMY,
};

// Named after: https://en.wikipedia.org/wiki/88_modern_constellations
enum class ShipClass {
  ANTLIA,
  BOOTES,
};

struct LocationEvent : public Event {
  static const EventType type = "LocationEvent"_type;
  Origin origin;
  sf::Vector2f pos;
  Ship *ship;
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
  ShipClass ship;
  sf::Vector2f pos;
};

#endif // LOCAL_GAME_H
