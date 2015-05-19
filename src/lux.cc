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
#include <cassert>
#include <cstdint>
#include <cmath>
#include <ctime>

#include <iostream>

#include <SFML/Graphics.hpp>

#include "local/Bullets.h"
#include "local/Config.h"
#include "local/Enemy.h"
#include "local/Event.h"
#include "local/Group.h"
#include "local/Hero.h"
#include "local/Random.h"
#include "local/Sensor.h"
#include "local/Stars.h"


int main() {
  Engine engine(std::time(nullptr));

  sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Lux");

  EventManager events;

  Bullets bullets(events);

  Sensor sensor(window);
  Enemy enemy(sf::Vector2f(WINDOW_W * 0.5f, -1.0f), sf::Vector2f(0.0f, WINDOW_H / 3.0f), events);
  Hero hero(sensor, events);

  Stars stars1(engine, 200, 1.5f);
  Stars stars2(engine, 100, 1.25f);
  Stars stars3(engine,  20, 1.0f);

  Group group;
  group.addEntity(sensor).addEntity(enemy).addEntity(hero);
  group.addEntity(stars1);
  group.addEntity(stars2);
  group.addEntity(stars3);
  group.addEntity(bullets);

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // update

    sf::Time elapsed = clock.restart();
    float dt = elapsed.asSeconds();
    group.update(dt);

    // render

    window.clear(sf::Color::Black);
    group.render(window);


    window.display();
  }

  return 0;
}
