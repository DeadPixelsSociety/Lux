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

#include "Camera.h"


Camera::~Camera() {
  // nothing
}

void CameraManager::addCamera(Camera& camera) {
  m_cameras.push_back(&camera);
}

void CameraManager::update(sf::Event& event) {
  for (auto camera : m_cameras) {
    camera->update(event);
  }
}


SceneCamera::SceneCamera(float width, const sf::Vector2f& center)
: m_width(width)
, m_center(center)
{
}


FixedRatioCamera::FixedRatioCamera(float width, float height, const sf::Vector2f& center)
: SceneCamera(width, center)
, m_areaWidth(width)
, m_areaHeight(height)
, m_ratio(width / height)
, m_view(center, { width, height })
{
}

void FixedRatioCamera::update(sf::Event& event) {
  if (event.type != sf::Event::Resized) {
    return;
  }

  float w = static_cast<float>(event.size.width);
  float h = static_cast<float>(event.size.height);

  float ratioEvent = w / h;

  sf::FloatRect vp;
  if (ratioEvent < m_ratio) {
    vp.left = 0.0f;
    vp.width = 1.0f;

    float r = (m_areaHeight * (w / m_areaWidth)) / h;
    vp.top = (1.0f - r) / 2.0f;
    vp.height = r;
  }
  else {
    vp.top = 0.0f;
    vp.height = 1.0f;

    float r = (m_areaWidth * (h / m_areaHeight)) / w;
    vp.left = (1.0f - r) / 2.0f;
    vp.width = r;
  }

  m_view.setViewport(vp);
}

void FixedRatioCamera::configure(sf::RenderWindow& window) {
  m_view.setCenter(getCenter());
  window.setView(m_view);
}


FlexibleCamera::FlexibleCamera(float width, const sf::Vector2f& center)
: SceneCamera(width, center)
{

}

void FlexibleCamera::update(sf::Event& event) {
  if (event.type != sf::Event::Resized) {
    return;
  }

  float w = static_cast<float>(event.size.width);
  float h = static_cast<float>(event.size.height);

  float height = getWidth() / w * h;

  m_view.setSize(getWidth(), height);
}

void FlexibleCamera::configure(sf::RenderWindow& window) {
  m_view.setCenter(getCenter());
  window.setView(m_view);
}


HeadsUpCamera::HeadsUpCamera(sf::RenderWindow& window) {
  m_view = window.getDefaultView();
}

void HeadsUpCamera::update(sf::Event& event) {
  if (event.type != sf::Event::Resized) {
    return;
  }

  float w = static_cast<float>(event.size.width);
  float h = static_cast<float>(event.size.height);

  m_view.reset({ 0.0f, 0.0f, w, h });
}

void HeadsUpCamera::configure(sf::RenderWindow& window) {
  window.setView(m_view);
}

