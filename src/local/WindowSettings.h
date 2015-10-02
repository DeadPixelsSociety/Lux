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


#ifndef GAME_WINDOW_SETTINGS_H
#define GAME_WINDOW_SETTINGS_H

#include <string>

#include <SFML/Window.hpp>

/**
 * @ingroup graphics
 */
class WindowSettings {
public:
  WindowSettings(unsigned initial_width, unsigned initial_height, std::string title)
  : m_mode(initial_width, initial_height)
  , m_title(std::move(title))
  , m_fullscreen(false)
  {
    m_settings.antialiasingLevel = 8;
  }

  void toggleFullscreen();
  void applyTo(sf::Window& window);

private:
  sf::VideoMode m_mode;
  std::string m_title;
  bool m_fullscreen;
  sf::ContextSettings m_settings;
};


#endif // GAME_WINDOW_SETTINGS_H
