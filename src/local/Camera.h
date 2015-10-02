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

#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include <SFML/Graphics.hpp>


/**
 * @ingroup graphics
 */
class Camera {
public:
  ~Camera();
  virtual void update(sf::Event& event) = 0;
  virtual void configure(sf::RenderWindow& window) = 0;
};

/**
 * @ingroup graphics
 */
class CameraManager {
public:
  void addCamera(Camera& camera);
  void update(sf::Event& event);
private:
  std::vector<Camera*> m_cameras;
};

/**
 * @ingroup graphics
 */
class SceneCamera : public Camera {
public:
  SceneCamera(float width, const sf::Vector2f& center);

  float getWidth() const {
    return m_width;
  }

  void setWidth(float width) {
    m_width = width;
  }

  const sf::Vector2f& getCenter() const {
    return m_center;
  }

  void setCenter(const sf::Vector2f& center) {
    m_center = center;
  }

private:
  float m_width;
  sf::Vector2f m_center;
};

/**
 * @ingroup graphics
 */
class FixedRatioCamera : public SceneCamera {
public:
  FixedRatioCamera(float width, float height, const sf::Vector2f& center = sf::Vector2f(0.0f, 0.0f));
  virtual void update(sf::Event& event) override;
  virtual void configure(sf::RenderWindow& window) override;

private:
  float m_areaWidth;
  float m_areaHeight;
  float m_ratio;
  sf::View m_view;
};

/**
 * @ingroup graphics
 */
class FlexibleCamera : public SceneCamera {
public:
  FlexibleCamera(float width, const sf::Vector2f& center = sf::Vector2f(0.0f, 0.0f));
  virtual void update(sf::Event& event) override;
  virtual void configure(sf::RenderWindow& window) override;

private:
  sf::View m_view;
};

/**
 * @ingroup graphics
 */
class HeadsUpCamera : public Camera {
public:
  HeadsUpCamera(sf::RenderWindow& window);
  virtual void update(sf::Event& event) override;
  virtual void configure(sf::RenderWindow& window) override;

private:
  sf::View m_view;
};


#endif // GAME_CAMERA_H
