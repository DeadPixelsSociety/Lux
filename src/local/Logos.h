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

#ifndef LOCAL_LOGOS_H
#define LOCAL_LOGOS_H

#include <game/Entity.h>
#include <game/ResourceManager.h>
#include <game/WindowGeometry.h>

class Logos : public game::Entity {
public:
  Logos(game::ResourceManager &resources, game::WindowGeometry &geometry);

  virtual void render(sf::RenderWindow& window) override;

private:
  game::WindowGeometry &m_geometry;
  sf::Texture *m_dpsTexture;
  sf::Texture *m_fcecTexture;
  sf::Texture *m_ufrTexture;
  sf::Texture *m_ufcTexture;
};

#endif // LOCAL_LOGOS_H
