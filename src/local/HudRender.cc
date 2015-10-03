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

#include "HudRender.h"

#include "Game.h"

HudRender::HudRender(game::EventManager &events, game::ResourceManager &resources, game::WindowGeometry &geometry)
: m_geometry(geometry)
, m_score(0.0f)
, m_life(0.0f) 
, m_font(nullptr) {
  // Load font
  m_font = resources.getFont("jupiter.ttf");
  assert(m_font != nullptr);

  // Register event
  events.registerHandler<ScoreEvent>(&HudRender::onScoreEvent, this);
  events.registerHandler<LifeEvent>(&HudRender::onLifeEvent, this);
}

static constexpr float HEALTH_WIDTH = 200.0f;
static constexpr float HEALTH_HEIGHT = 5.0f;
static constexpr float HEALTH_THICKNESS = 1.0f;
static constexpr float HEALTH_PADDING = 40.0f;
static constexpr float SCORE_PADDING = 200.0f;

void HudRender::render(sf::RenderWindow& window) {
  sf::RectangleShape rectangleShape({ HEALTH_WIDTH, HEALTH_HEIGHT });
  rectangleShape.setOrigin(0.0f, HEALTH_HEIGHT);
  rectangleShape.setPosition(m_geometry.getXCentered(HEALTH_WIDTH), m_geometry.getYFromBottom(HEALTH_PADDING));
  rectangleShape.setOutlineColor(sf::Color::White);
  rectangleShape.setOutlineThickness(HEALTH_THICKNESS);
  rectangleShape.setFillColor(sf::Color::Transparent);
  window.draw(rectangleShape);

  sf::RectangleShape healthRectangle({ HEALTH_WIDTH * m_life, HEALTH_HEIGHT });
  healthRectangle.setOrigin(0.0f, HEALTH_HEIGHT);
  healthRectangle.setPosition(m_geometry.getXCentered(HEALTH_WIDTH), m_geometry.getYFromBottom(HEALTH_PADDING));
  healthRectangle.setFillColor(sf::Color::Red);
  window.draw(healthRectangle);

  sf::Text text;
  text.setFont(*m_font);
  text.setString("Score : " + std::to_string(m_score));
  text.setCharacterSize(24);
  text.setColor(sf::Color::White);

  // FixMe: fix the vertical align
  text.setOrigin(0.0f, text.getLocalBounds().height + text.getLocalBounds().top);
  text.setPosition(m_geometry.getXFromRight(0.0f) * 0.80f, m_geometry.getYFromBottom(HEALTH_PADDING));

  window.draw(text);
}

game::EventStatus HudRender::onScoreEvent(game::EventType type, game::Event *event) {
  auto scoreEvent = static_cast<ScoreEvent *>(event);

  m_score = scoreEvent->score;

  return game::EventStatus::KEEP;
}

game::EventStatus HudRender::onLifeEvent(game::EventType type, game::Event *event) {
  auto lifeEvent = static_cast<LifeEvent *>(event);

  m_life = lifeEvent->life;

  return game::EventStatus::KEEP;
}
