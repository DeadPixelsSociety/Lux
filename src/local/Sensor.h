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
#ifndef LOCAL_SENSOR_H
#define LOCAL_SENSOR_H

#include <cstddef>
#include <cstdint>

#include <config.h>
#ifndef LUX_MOUSE_CONTROL
#include <mutex>
#include <thread>
#endif // LUX_MOUSE_CONTROL


#include <SFML/Graphics.hpp>

#include <game/Entity.h>

struct sp_port;

class Sensor : public game::Entity {
public:
#ifndef LUX_MOUSE_CONTROL
  static constexpr std::size_t SENSOR_W = 4;
  static constexpr std::size_t SENSOR_H = 4;
#else
  static constexpr std::size_t SENSOR_W = 8;
  static constexpr std::size_t SENSOR_H = 6;
#endif // LUX_MOUSE_CONTROL

#ifndef LUX_MOUSE_CONTROL
  Sensor();
  ~Sensor();

  Sensor(const Sensor&) = delete;
  Sensor& operator=(const Sensor&) = delete;
#else
  Sensor(sf::Window& window);
#endif // LUX_MOUSE_CONTROL


  virtual void update(float dt) override;

  virtual void render(sf::RenderWindow& window) override;

  sf::Vector2f getCenter() const;

private:
#ifndef LUX_MOUSE_CONTROL
  sp_port *m_port;

  std::thread m_thread;
  std::mutex m_mutex;

  typedef std::array<uint8_t, 2 * 16 + 3> Buffer;

  std::array<Buffer, 2> m_bufs; // SPACE + \n + \r
  std::size_t m_index;

  uint16_t values[SENSOR_H][SENSOR_W];
#else
  uint8_t values[SENSOR_H][SENSOR_W];
  sf::Window& m_window;
#endif // LUX_MOUSE_CONTROL
};

#endif // LOCAL_SENSOR_H
