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
#ifndef GAME_RESOURCE_H
#define GAME_RESOURCE_H

#include <string>
#include <map>
#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "Assets.h"


class ResourceManager : public AssetManager {
public:
  sf::Font *getFont(const boost::filesystem::path& path);
  sf::SoundBuffer *getSoundBuffer(const boost::filesystem::path& path);
  sf::Texture *getTexture(const boost::filesystem::path& path);

private:
  template<typename T>
  class ResourceCache {
  public:
    T *findResource(const boost::filesystem::path& key);
    T *loadResource(const boost::filesystem::path& key, const boost::filesystem::path& path);
  private:
    std::map<boost::filesystem::path, std::unique_ptr<T>> m_cache;
  };

private:
  ResourceCache<sf::Font> m_fonts;
  ResourceCache<sf::SoundBuffer> m_sounds;
  ResourceCache<sf::Texture> m_textures;

private:
  template<typename T>
  T *getResource(const boost::filesystem::path& path, ResourceCache<T>& cache);
};

#endif // GAME_RESOURCE_H
