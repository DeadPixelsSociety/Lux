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
#include "Resources.h"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;


template<typename T>
T *ResourceManager::ResourceCache<T>::findResource(const boost::filesystem::path& key) {
  auto it = m_cache.find(key);

  if (it != m_cache.end()) {
    return it->second.get();
  }

  return nullptr;
}

template<typename T>
T *ResourceManager::ResourceCache<T>::loadResource(const boost::filesystem::path& key, const boost::filesystem::path& path) {
  std::unique_ptr<T> obj(new T);

  bool loaded = obj->loadFromFile(path.string());
  assert(loaded);

  auto inserted = m_cache.emplace(key, std::move(obj));
  assert(inserted.second);

  return inserted.first->second.get();
}

sf::Font *ResourceManager::getFont(const boost::filesystem::path& path) {
  return getResource(path, m_fonts);
}

sf::SoundBuffer *ResourceManager::getSoundBuffer(const boost::filesystem::path& path) {
  return getResource(path, m_sounds);
}

sf::Texture *ResourceManager::getTexture(const boost::filesystem::path& path) {
  return getResource(path, m_textures);
}

template<typename T>
T *ResourceManager::getResource(const boost::filesystem::path& path, ResourceCache<T>& cache) {
  auto res = cache.findResource(path);

  if (res != nullptr) {
    return res;
  }

  auto absolute_path = getAbsolutePath(path);

  if (absolute_path.empty()) {
    return nullptr;
  }

  return cache.loadResource(path, absolute_path);
}
