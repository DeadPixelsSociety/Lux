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

#include "Logos.h"

Logos::Logos(game::ResourceManager &resources, game::WindowGeometry &geometry)
: m_geometry(geometry)
, m_dpsTexture(nullptr)
, m_fcecTexture(nullptr)
, m_ufrTexture(nullptr)
, m_ufcTexture(nullptr) {
  // Load texture
  m_dpsTexture = resources.getTexture("logo_dps.png");
  assert(m_dpsTexture != nullptr);

  m_fcecTexture = resources.getTexture("logo_fcec.png");
  assert(m_fcecTexture != nullptr);

  m_ufrTexture = resources.getTexture("logo_ufr.jpeg");
  assert(m_ufrTexture != nullptr);

  m_ufcTexture = resources.getTexture("logo_ufc.jpeg");
  assert(m_ufcTexture != nullptr);
}

static constexpr float LOGO_WIDTH = 128.0f;
static constexpr float RIGHT_PADDING = 15.0f;
static constexpr float BOTTOM_PADDING = 76.0f;
static constexpr float SECOND_LINE_PADDING = BOTTOM_PADDING + 15.0f + 98.0f;
static constexpr float FCEC_PADDING = (36 - 61) / 2.0f;
static constexpr float UFR_PADDING = (73 - 98) / 2.0f;

void Logos::render(sf::RenderWindow& window) {
  sf::Sprite spriteDPS;
  spriteDPS.setTexture(*m_dpsTexture);
  spriteDPS.setPosition(RIGHT_PADDING, m_geometry.getYFromBottom(BOTTOM_PADDING));
  window.draw(spriteDPS);

  sf::Sprite spriteFCEC;
  spriteFCEC.setTexture(*m_fcecTexture);
  spriteFCEC.setPosition(RIGHT_PADDING * 2.0f + LOGO_WIDTH, m_geometry.getYFromBottom(BOTTOM_PADDING + FCEC_PADDING));
  window.draw(spriteFCEC);

  sf::Sprite spriteUFR;
  spriteUFR.setTexture(*m_ufrTexture);
  spriteUFR.setPosition(RIGHT_PADDING, m_geometry.getYFromBottom(SECOND_LINE_PADDING + UFR_PADDING));
  window.draw(spriteUFR);

  sf::Sprite spriteUFC;
  spriteUFC.setTexture(*m_ufcTexture);
  spriteUFC.setPosition(RIGHT_PADDING * 2.0f + LOGO_WIDTH, m_geometry.getYFromBottom(SECOND_LINE_PADDING));
  window.draw(spriteUFC);
}
