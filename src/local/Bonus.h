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
#ifndef LOCAL_BONUS_H
#define LOCAL_BONUS_H

#include <vector>

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/ResourceManager.h>

#include "Random.h"

enum BonusType : int {
  LIFE = 0,
  UPGRADE_WEAPON = 1,
};

class BonusManager : public game::Entity {
public:
  BonusManager(game::EventManager& events, game::ResourceManager &resources, Engine &engine);

  void addBonus(const sf::Vector2f& pos, const sf::Vector2f& velocity, const BonusType &type);
  
  virtual void update(float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  game::EventStatus onDropBonusEvent(game::EventType type, game::Event *event);
  game::EventStatus onLocationEvent(game::EventType type, game::Event *event);

private:
  struct Bonus {
    sf::Vector2f pos;
    sf::Vector2f velocity;
    BonusType type;
    bool active;
  };

  Engine &m_engine;
  std::vector<Bonus> m_bonus;
  sf::Texture *m_lifeTexture;
  sf::Texture *m_weaponTexture;
};

#endif // _LOCAL_BONUS_H
