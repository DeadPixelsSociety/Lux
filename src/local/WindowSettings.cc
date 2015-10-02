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

#include "WindowSettings.h"

void WindowSettings::toggleFullscreen() {
  m_fullscreen = !m_fullscreen;
}

void WindowSettings::applyTo(sf::Window& window) {
  sf::VideoMode mode = m_mode;
  sf::Uint32 style = sf::Style::Default;

  if (m_fullscreen) {
    auto size = window.getSize();
    m_mode.width = size.x;
    m_mode.height = size.y;

    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    mode = modes.front();

    style |= sf::Style::Fullscreen;
  }

  window.create(mode, m_title, style, m_settings);
}

