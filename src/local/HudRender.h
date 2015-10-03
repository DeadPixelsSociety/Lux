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

#ifndef LOCAL_HUD_RENDER_H
#define LOCAL_HUD_RENDER_H

#include <game/Entity.h>
#include <game/EventManager.h>
#include <game/ResourceManager.h>
#include <game/WindowGeometry.h>

class HudRender : public game::Entity {
public:
  HudRender(game::EventManager &events, game::ResourceManager &resources, game::WindowGeometry &geometry);

  virtual void render(sf::RenderWindow& window) override;

  game::EventStatus onScoreEvent(game::EventType type, game::Event *event);
  game::EventStatus onLifeEvent(game::EventType type, game::Event *event);

private:
  game::WindowGeometry &m_geometry;
  unsigned int m_score;
  float m_life;
  sf::Font *m_font;
};

#endif // LOCAL_HUD_RENDER_H