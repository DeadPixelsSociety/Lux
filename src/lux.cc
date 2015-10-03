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

#include <game/Action.h>
#include <game/Camera.h>
#include <game/Event.h>
#include <game/EntityManager.h>
#include <game/ResourceManager.h>
#include <game/WindowGeometry.h>
#include <game/WindowSettings.h>

#include "local/Bonus.h"
#include "local/Bullets.h"
#include "local/Enemy.h"
#include "local/Hero.h"
#include "local/Particles.h"
#include "local/Random.h"
#include "local/Scenario.h"
#include "local/Sensor.h"
#include "local/Stars.h"

#include "config.h"

int main() {
  Engine engine(std::time(nullptr));

  static constexpr unsigned INITIAL_WIDTH = 800;
  static constexpr unsigned INITIAL_HEIGHT = 600;

  game::WindowSettings settings(INITIAL_WIDTH, INITIAL_HEIGHT, "Lux - Year of Light");
  game::WindowGeometry geometry(INITIAL_WIDTH, INITIAL_HEIGHT);

  sf::RenderWindow window;
  settings.applyTo(window);
  window.setKeyRepeatEnabled(false);

  game::EventManager events;

  game::ResourceManager resources;
  resources.addSearchDir(GAME_DATADIR);

  // Preload data 
  {
    Enemy e2(ShipClass::BOOTES, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 1.0f, engine, events, resources);
    Enemy e3(ShipClass::CYGNUS, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 1.0f, engine, events, resources);
    Enemy e4(ShipClass::DRACO, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 1.0f, engine, events, resources);
    Enemy e5(ShipClass::ERIDANUS, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 1.0f, engine, events, resources);
  }

  // entities

  game::EntityManager mainEntities;

  Bullets bullets(events, resources);
  mainEntities.addEntity(bullets);

  BonusManager bonus(events, resources, engine);
  mainEntities.addEntity(bonus);

#ifndef LUX_MOUSE_CONTROL
  Sensor sensor;
#else
  Sensor sensor(window);
#endif // LUX_MOUSE_CONTROL
  mainEntities.addEntity(sensor);

  EnemyManager enemies(engine, events, resources);
  mainEntities.addEntity(enemies);

  Hero hero(sensor, events, resources);
  mainEntities.addEntity(hero);

  Particles particles(events, engine);
  mainEntities.addEntity(particles);

  Stars stars1(engine, 125, 1.5f);
  Stars stars2(engine, 75, 1.25f);
  Stars stars3(engine,  20, 1.0f, true);
  mainEntities.addEntity(stars1);
  mainEntities.addEntity(stars2);
  mainEntities.addEntity(stars3);


  game::EntityManager hudEntities;

  Scenario scenario(enemies, events, resources);
  hudEntities.addEntity(scenario);

  // add actions
  game::ActionManager actions;

  game::Action closeWindowAction("Close window");
  closeWindowAction.addCloseControl();
  closeWindowAction.addKeyControl(sf::Keyboard::Escape);
  actions.addAction(closeWindowAction);

  game::Action fullscreenAction("Fullscreen");
  fullscreenAction.addKeyControl(sf::Keyboard::F);
  actions.addAction(fullscreenAction);

  // add cameras
  game::CameraManager cameras;

  static constexpr float AREA_WIDTH = 800;
  static constexpr float AREA_HEIGHT = 600;

  game::FixedRatioCamera mainCamera(AREA_WIDTH, AREA_HEIGHT, {AREA_WIDTH / 2.0f, AREA_HEIGHT / 2.0f});
  cameras.addCamera(mainCamera);

  game::HeadsUpCamera hudCamera(window);
  cameras.addCamera(hudCamera);


  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      actions.update(event);
      cameras.update(event);
      geometry.update(event);
    }

    if (closeWindowAction.isActive()) {
      window.close();
    }

    if (fullscreenAction.isActive()) {
      settings.toggleFullscreen();
      settings.applyTo(window);
      auto sz = window.getSize();

      // fake resize event (not sent when going fullscreen before SFML 2.3.1)
      sf::Event event;
      event.type = sf::Event::Resized;
      event.size.width = sz.x;
      event.size.height = sz.y;
      cameras.update(event);
      geometry.update(event);
    }

    // update
    sf::Time elapsed = clock.restart();
    float dt = elapsed.asSeconds();
    mainEntities.update(dt);
    hudEntities.update(dt);

    // render
    window.clear(sf::Color::Black);

    mainCamera.configure(window);
    mainEntities.render(window);

    hudCamera.configure(window);
    hudEntities.render(window);

    window.display();

    actions.reset();
  }

  return 0;
}
