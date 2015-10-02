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
#include "Action.h"

#include <cassert>

Action::Action(std::string name)
  : m_name(std::move(name))
  , m_type(Type::INSTANTANEOUS) {
}

void Action::setContinuous() {
  m_type = Type::CONTINUOUS;
}

bool Action::isContinuous() const {
  return m_type == Type::CONTINUOUS;
}

void Action::setInstantaneous() {
  m_type = Type::INSTANTANEOUS;
}

bool Action::isInstantaneous() const {
  return m_type == Type::INSTANTANEOUS;
}

void Action::addGamepadAxisControl(unsigned int id, sf::Joystick::Axis axis, Direction dir) {
  std::unique_ptr<Control> ptr(new GamepadAxisControl(id, axis, dir));
  m_controls.push_back(std::move(ptr));
}

void Action::addGamepadButtonControl(unsigned int id, unsigned int button) {
  std::unique_ptr<Control> ptr(new GamepadButtonControl(id, button));
  m_controls.push_back(std::move(ptr));
}

void Action::addKeyControl(sf::Keyboard::Key key) {
  std::unique_ptr<Control> ptr(new KeyControl(key));
  m_controls.push_back(std::move(ptr));
}

void Action::addMouseButtonControl(sf::Mouse::Button button) {
  std::unique_ptr<Control> ptr(new MouseButtonControl(button));
  m_controls.push_back(std::move(ptr));
}

void Action::addCloseControl() {
  std::unique_ptr<Control> ptr(new CloseControl);
  m_controls.push_back(std::move(ptr));
}

void Action::update(const sf::Event& event) {
  for (auto& control : m_controls) {
    control->update(event);
  }
}

bool Action::isActive() {
  for (auto& control : m_controls) {
    if (control->isActive()) {
      return true;
    }
  }

  return false;
}

void Action::reset() {
  if (isContinuous()) {
    return;
  }

  for (auto& control : m_controls) {
    control->reset();
  }
}

// ActionManager

void ActionManager::addAction(Action& action) {
  m_actions.push_back(&action);
}

void ActionManager::update(const sf::Event& event) {
  for (auto action : m_actions) {
    action->update(event);
  }
}

void ActionManager::reset() {
  for (auto action : m_actions) {
    action->reset();
  }
}

