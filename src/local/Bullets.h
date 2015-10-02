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
#ifndef LOCAL_BULLETS_H
#define LOCAL_BULLETS_H

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/ResourceManager.h>

#include "Game.h"

class Bullets : public game::Entity {
public:
  Bullets(game::EventManager& events, game::ResourceManager &manager);

  void addBullet(Origin origin, ShipClass shipClass, const sf::Vector2f& pos, const sf::Vector2f& velocity);

  virtual void update(float dt) override;
  virtual void render(sf::RenderWindow& window) override;

private:
  game::EventStatus onLocationEvent(game::EventType type, game::Event *event);
  game::EventStatus onShootEvent(game::EventType type, game::Event *event);

private:
  struct Bullet {
    Origin origin;
    sf::Vector2f pos;
    sf::Vector2f velocity;
    sf::Texture *texture;
    bool active;
  };

  std::vector<Bullet> m_bullets;
  sf::Texture *m_bulletBlueTexture;
  sf::Texture *m_bulletGreenTexture;
  sf::Texture *m_bulletYellowTexture;
  sf::Texture *m_bulletPurpleTexture;
};


#endif // LOCAL_BULLETS_H
