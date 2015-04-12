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
#include "Sensor.h"

#include <cassert>
#include <cmath>

#include "Config.h"

void Sensor::update(float dt) {
  auto pos = sf::Mouse::getPosition(m_window);

  int w = (WINDOW_W / SENSOR_W);
  int h = (WINDOW_H / SENSOR_H);

  for (std::size_t j = 0; j < SENSOR_H; ++j) {
    for (std::size_t i = 0; i < SENSOR_W; ++i) {
      int x = i * w + w / 2;
      int y = j * h + h / 2;

      double dist = std::hypot(pos.x - x, pos.y - y);
      double value = 127.0 * std::exp(-dist * dist * 0.00001);
      assert(0.0 <= value && value <= 127.0);

      values[j][i] = static_cast<uint8_t>(value);

//         std::cout << static_cast<unsigned>(values[j][i]) << ' ';
    }

//       std::cout << '\n';
  }

//     std::cout << '\n';
}

void Sensor::render(sf::RenderWindow& window) {
  float w = (WINDOW_W / SENSOR_W);
  float h = (WINDOW_H / SENSOR_H);

  for (std::size_t j = 0; j < SENSOR_H; ++j) {
    for (std::size_t i = 0; i < SENSOR_W; ++i) {
      float x = i * w;
      float y = j * h;

      sf::RectangleShape shape({ w, h });
      shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF, values[j][i] * 2));
      shape.setPosition(x, y);
      window.draw(shape);
    }
  }


}

sf::Vector2f Sensor::getCenter() const {
  float w = (WINDOW_W / SENSOR_W);
  float h = (WINDOW_H / SENSOR_H);

  sf::Vector2f pos(0.0f, 0.0f);
  float total = 0;

  for (std::size_t j = 0; j < SENSOR_H; ++j) {
    for (std::size_t i = 0; i < SENSOR_W; ++i) {
      float x = i * w + w / 2;
      float y = j * h + h / 2;

      float p = static_cast<float>(values[j][i]) * static_cast<float>(values[j][i]);

      pos.x += x * p;
      pos.y += y * p;
      total += p;
    }
  }

  pos.x /= total;
  pos.y /= total;
  return pos;
}

