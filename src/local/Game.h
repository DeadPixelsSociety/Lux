/*
 * Lux
 *
 * Copyright (c) 2015, Julien Bernard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
  CYGNUS,
  DRACO,
  ERIDANUS,
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
  ShipClass shipClass;
  sf::Vector2f pos;
  sf::Vector2f velocity;
};

struct DeadEvent : public Event {
  static const EventType type = "DeadEvent"_type;
  Origin origin;
  ShipClass ship;
  sf::Vector2f pos;
};

struct ScoreEvent : public Event {
  static const EventType type = "ScoreEvent"_type;
  unsigned int score;
};

struct RestartGameEvent : public Event {
  static const EventType type = "RestartGameEvent"_type;
};

struct DropBonusEvent : public Event {
  static const EventType type = "DropBonusEvent"_type;
  sf::Vector2f pos;
};

struct WinGameEvent : public Event {
  static const EventType type = "WinGameEvent"_type;
  unsigned int bonusScore;
};

#endif // LOCAL_GAME_H
