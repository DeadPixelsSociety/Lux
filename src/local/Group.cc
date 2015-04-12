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
#include "Group.h"

#include <cassert>
#include <algorithm>

void Group::update(float dt) {
  // erase-remove idiom
  m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [](const Entity *e) {
    return !e->isAlive();
  }), m_entities.end());

  std::sort(m_entities.begin(), m_entities.end(), [](const Entity * e1, const Entity * e2) {
    return e1->priority() < e2->priority();
  });

  for (auto entity : m_entities) {
    entity->update(dt);
  }
}

void Group::render(sf::RenderWindow& window) {
  for (auto entity : m_entities) {
    entity->render(window);
  }
}

Group& Group::addEntity(Entity& e) {
  m_entities.push_back(&e);

  return *this;
}

Entity *Group::removeEntity(Entity *e) {
  // erase-remove idiom
  auto it = std::remove(m_entities.begin(), m_entities.end(), e);

  if (it != m_entities.end()) {
    m_entities.erase(it, m_entities.end());
    return e;
  }

  return nullptr;
}
