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

#include "Entity.h"
#include "Event.h"
#include "Resources.h"

enum BonusType {
  LIFE,  
};

class BonusManager : public Entity
{
public:
  BonusManager(EventManager& events, ResourceManager &resources);

  void addBonus(const sf::Vector2f& pos, const sf::Vector2f& velocity, const BonusType &type);
  
  virtual void update(float dt) override;
  virtual void render(sf::RenderWindow& window) override;

  EventStatus onDropBonusEvent(EventType type, Event *event);
  EventStatus onLocationEvent(EventType type, Event *event);

private:
  struct Bonus {
    sf::Vector2f pos;
    sf::Vector2f velocity;
    BonusType type;
    bool active;
  };

  std::vector<Bonus> m_bonus;
  sf::Texture *m_lifeTexture;
};

#endif // _LOCAL_BONUS_H
