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

#ifndef LOCAL_ACTION_H
#define LOCAL_ACTION_H

#include <memory>
#include <vector>

#include "Control.h"

/**
* @brief An action that can be triggered by different controls.
*
* @ingroup graphics
*/
class Action {
public:
/**
 * @brief Construct an action with a name.
 *
 * @param name the name of the action.
 */
Action(std::string name);

/**
 * @brief Get the name of the action.
 *
 * @return the name of the action.
 */
const std::string& getName() const {
  return m_name;
}


/**
 * @name Type of the action
 * @{
 */
/**
 * @brief Set the action continuous.
 *
 * A continuous action is an action that is active as long as the user do
 * not desactivate it. A reset() call does not desactivate the action.
 *
 * @sa reset(), setInstantaneous()
 */
void setContinuous();

/**
 * @brief Tell whether the action is continuous.
 *
 * @return true if the action is continuous.
 */
bool isContinuous() const;

/**
 * @brief Set the action instantaneous.
 *
 * An instantaneous action is an action that is active until the next
 * reset() call.
 *
 * @sa reset(), setContinuous()
 */
void setInstantaneous();

/**
 * @brief Tell whether the action is instantaneous.
 *
 * @return true if the action is instantaneous.
 */
bool isInstantaneous() const;
/** @} */

/**
 * @name Controls for the action
 * @{
 */
/**
 * @brief Add a gamepad axis control.
 *
 * @param id the id of the gamepad.
 * @param axis the axis of the gamepad.
 * @param dir the direction of the axis of the gamepad.
 *
 * @sa GamepadAxisControl
 */
void addGamepadAxisControl(unsigned int id, sf::Joystick::Axis axis, Direction dir);

/**
 * @brief Add a gamepad button control.
 *
 * @param id the id of the gamepad.
 * @param button the button of the gamepad
 *
 * @sa GamepadButtonControl
 */
void addGamepadButtonControl(unsigned int id, unsigned int button);

/**
 * @brief Add a key control.
 *
 * @param key the key of the keyboard.
 *
 * @sa KeyControl
 */
void addKeyControl(sf::Keyboard::Key key);

/**
 * @brief Add a mouse button control.
 *
 * @param button the button of the mouse.
 *
 * @sa MouseButtonControl
 */
void addMouseButtonControl(sf::Mouse::Button button);

/**
 * @brief Add a close control.
 *
 * @sa CloseControl
 */
void addCloseControl();
/** @} */

/**
 * @name State of the action
 * @{
 */
/**
 * @brief Update the state of the action thanks to an event.
 *
 * @param event the event to update the action.
 *
 * @sa Control::update()
 */
void update(const sf::Event& event);

/**
 * @brief Tell whether the action is active.
 *
 * An action is active if at least one of its control is active.
 *
 * @return true if the action is active.
 *
 * @sa Control::isActive()
 */
bool isActive();

/**
 * @brief Reset the state of the action.
 *
 * This function depends of the type of the action.
 *
 * @sa setContinuous(), setInstantaneous(), Control::reset()
 */
void reset();
/** @} */

private:
enum class Type {
  INSTANTANEOUS,
  CONTINUOUS,
};

const std::string m_name;
Type m_type;
std::vector<std::unique_ptr<Control>> m_controls;
};

/**
* @brief A set of actions.
*
* @ingroup graphics
*/
class ActionManager {
public:
/**
 * @brief Add an action.
 *
 * @param action the action to add to the set.
 */
void addAction(Action& action);

/**
 * @brief Update all the actions.
 *
 * @param event the event to update the actions.
 *
 * @sa Action;:update()
 */
void update(const sf::Event& event);

/**
 * @brief Reset all the actions.
 *
 * @sa Action::reset()
 */
void reset();

private:
std::vector<Action*> m_actions;
};

#endif // LOCAL_ACTION_H
