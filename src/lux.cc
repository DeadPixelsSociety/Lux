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

#include "local/Bonus.h"
#include "local/Bullets.h"
#include "local/Camera.h"
#include "local/Config.h"
#include "local/Enemy.h"
#include "local/Event.h"
#include "local/Group.h"
#include "local/Hero.h"
#include "local/Particles.h"
#include "local/Random.h"
#include "local/Resources.h"
#include "local/Scenario.h"
#include "local/Sensor.h"
#include "local/Stars.h"
#include "local/WindowGeometry.h"
#include "local/WindowSettings.h"
#include "path.h"

int main() {
  Engine engine(std::time(nullptr));

  static constexpr unsigned INITIAL_WIDTH = 800;
  static constexpr unsigned INITIAL_HEIGHT = 600;

  WindowSettings settings(INITIAL_WIDTH, INITIAL_HEIGHT, "Lux - Year of Light");
  WindowGeometry geometry(INITIAL_WIDTH, INITIAL_HEIGHT);

  sf::RenderWindow window;
  settings.applyTo(window);

  EventManager events;

  ResourceManager resources;
  resources.addSearchDir(GAME_DATADIR);

  Bullets bullets(events, resources);
  BonusManager bonus(events, resources, engine);

  Sensor sensor(window);
  EnemyManager enemies(engine, events, resources);
  Hero hero(sensor, events, resources);

  Particles particles(events, engine);

  Stars stars1(engine, 125, 1.5f);
  Stars stars2(engine, 75, 1.25f);
  Stars stars3(engine,  20, 1.0f, true);

  Scenario scenario(enemies, events, resources);

  Group group;
  group.addEntity(sensor).addEntity(enemies).addEntity(hero);
  group.addEntity(stars1);
  group.addEntity(stars2);
  group.addEntity(stars3);
  group.addEntity(bullets);
  group.addEntity(particles);
  group.addEntity(scenario);
  group.addEntity(bonus);

  // add cameras
  CameraManager cameras;

  FixedRatioCamera mainCamera(WINDOW_W, WINDOW_H, {WINDOW_W / 2.0f, WINDOW_H / 2.0f});
  cameras.addCamera(mainCamera);

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      cameras.update(event);
      geometry.update(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // update

    sf::Time elapsed = clock.restart();
    float dt = elapsed.asSeconds();
    group.update(dt);
    //scenario.update(dt);

    // render

    window.clear(sf::Color::Black);
    mainCamera.configure(window);
    group.render(window);


    window.display();
  }

  return 0;
}
