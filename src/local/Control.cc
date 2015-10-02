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

#include "Control.h"

#include <cassert>


// control

Control::~Control() {
}


// gamepad axis control

static const char *axisName(sf::Joystick::Axis axis) {
  return "?";
}

GamepadAxisControl::GamepadAxisControl(unsigned int id, sf::Joystick::Axis axis, Direction dir)
  : Control("gamepad (axis)", axisName(axis))
  , m_id(id)
  , m_axis(axis)
  , m_dir(dir) {
}

void GamepadAxisControl::update(const sf::Event& event) {
  if (event.type == sf::Event::JoystickMoved) {
    if (event.joystickMove.joystickId == m_id && event.joystickMove.axis == m_axis) {
      switch (m_dir) {
        case Direction::POSITIVE:
          setActive(event.joystickMove.position > 50.0f);
          break;
        case Direction::NEGATIVE:
          setActive(event.joystickMove.position < -50.0f);
          break;
      }
    }
  }
}


// gamepad button control

GamepadButtonControl::GamepadButtonControl(unsigned int id, unsigned int button)
  : Control("gamepad (button)", std::to_string(button))
  , m_id(id)
  , m_button(button) {
}

void GamepadButtonControl::update(const sf::Event& event) {
  if (event.type == sf::Event::JoystickButtonPressed) {
    if (event.joystickButton.joystickId == m_id && event.joystickButton.button == m_button) {
      setActive();
    }
  }

  if (event.type == sf::Event::JoystickButtonReleased) {
    if (event.joystickButton.joystickId == m_id && event.joystickButton.button == m_button) {
      setActive(false);
    }
  }
}


// key control

static const char *keyName(sf::Keyboard::Key key) {
  return "?";
}

KeyControl::KeyControl(sf::Keyboard::Key key)
  : Control("keyboard", keyName(key))
  , m_key(key) {

}

void KeyControl::update(const sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == m_key) {
      setActive();
    }
  }

  if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == m_key) {
      setActive(false);
    }
  }
}


// mouse button control

const char *buttonName(sf::Mouse::Button button) {
  return "?";
}

MouseButtonControl::MouseButtonControl(sf::Mouse::Button button)
  : Control("mouse", buttonName(button))
  , m_button(button) {
}

void MouseButtonControl::update(const sf::Event& event) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == m_button) {
      setActive();
    }
  }

  if (event.type == sf::Event::MouseButtonReleased) {
    if (event.mouseButton.button == m_button) {
      setActive(false);
    }
  }
}


// close control

CloseControl::CloseControl()
  : Control("window", "close") {
}

void CloseControl::update(const sf::Event& event) {
  if (event.type == sf::Event::Closed) {
    setActive();
  }
}

