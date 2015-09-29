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
#include <cstdio>

#include <libserialport.h>

#include "Config.h"

static void printError(sp_return ret) {
  if (ret > 0) {
    return;
  }

  switch (ret) {
    case SP_OK:
      return;

    case SP_ERR_FAIL:
      std::printf("Error: OS failure: %s\n", sp_last_error_message());
      break;

    case SP_ERR_ARG:
      std::printf("Error: Invalid argument.\n");
      break;

    case SP_ERR_SUPP:
      std::printf("Error: No support.\n");
      break;

    case SP_ERR_MEM:
      std::printf("Error: Memory allocation failure.\n");
      break;

    default:
      std::printf("Error: Unknown error (%i).\n", static_cast<int>(ret));
      break;
  }

  assert(false);
}


Sensor::Sensor()
: m_port(nullptr)
, m_index(0)
{
//   sp_port **list;
//   auto err = sp_list_ports(&list);
//   printError(err);

  std::printf("Configuring sensor...\n");

  auto err = sp_get_port_by_name("/dev/ttyUSB0", &m_port);
  printError(err);

  err = sp_open(m_port, static_cast<sp_mode>(SP_MODE_READ | SP_MODE_WRITE));
  printError(err);

  err = sp_set_baudrate(m_port, 115200);
  printError(err);

  err = sp_set_bits(m_port, 8);
  printError(err);

  err = sp_set_parity(m_port, SP_PARITY_NONE);
  printError(err);

  err = sp_set_stopbits(m_port, 1);
  printError(err);


  std::printf("\t%s\n", sp_get_port_name(m_port));

//   err = sp_set_rts(m_port, SP_RTS_OFF);
//   printError(err);
//
//   err = sp_set_cts(m_port, SP_CTS_IGNORE);
//   printError(err);

  sp_event_set *set;

  err = sp_new_event_set(&set);
  printError(err);

  std::printf("Waiting TX ready...\n");

  err = sp_add_port_events(set, m_port, static_cast<sp_event>(SP_EVENT_TX_READY));
  printError(err);

  err = sp_wait(set, 5000);
  printError(err);

  std::printf("Waiting RX ready...\n");

  err = sp_add_port_events(set, m_port, static_cast<sp_event>(SP_EVENT_RX_READY));
  printError(err);

  err = sp_wait(set, 5000);
  printError(err);

  sp_free_event_set(set);

  std::printf("Sensor ready...\n");

  std::thread t([this]() {
    static const char *cmd = "bn\r";

    for (;;) {
      auto err = sp_blocking_write(m_port, cmd, 3, 500);
      printError(err);

      err = sp_blocking_read(m_port, m_bufs[m_index].data(), m_bufs[m_index].size(), 500);
      printError(err);

      for (auto c : m_bufs[m_index]) {
        std::printf("%.3i ", static_cast<int>(c));
      }

      std::printf("\n");

      {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_index = 1 - m_index;
      }
    }

  });

  m_thread = std::move(t);
}

Sensor::~Sensor() {
  sp_close(m_port);
  sp_free_port(m_port);
}


void Sensor::update(float dt) {
  Buffer buf;

  {
    std::lock_guard<std::mutex> lock(m_mutex);
    buf = m_bufs[1 - m_index];
  }

  std::size_t index = 0;

  for (index = 0; index < SENSOR_H * SENSOR_W; index++) {
    std::size_t j = index % SENSOR_H;
    std::size_t i = index / SENSOR_H;

    uint16_t val = static_cast<uint16_t>(buf[2 * index]) + (static_cast<uint16_t>(buf[2 * index + 1]) << 8);
    values[j][i] = val;
  }


#if 0
  auto pos = sf::Mouse::getPosition(m_window);

  int w = (WINDOW_W / SENSOR_W);
  int h = (WINDOW_H / SENSOR_H);

  for (std::size_t j = 0; j < SENSOR_H; ++j) {
    for (std::size_t i = 0; i < SENSOR_W; ++i) {
      int x = i * w + w / 2;
      int y = j * h + h / 2;

      double dist = std::hypot(pos.x - x, pos.y - y);
      double value = 1023.0 * std::exp(-dist * dist * 0.00001);
      assert(0.0 <= value && value <= 1023.0);

      values[j][i] = static_cast<uint8_t>(value);

//         std::cout << static_cast<unsigned>(values[j][i]) << ' ';
    }

//       std::cout << '\n';
  }

//     std::cout << '\n';

#endif

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

