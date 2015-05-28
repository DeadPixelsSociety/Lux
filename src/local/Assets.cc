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
#include "Assets.h"

#include <iostream>
#include <cassert>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

void AssetManager::addSearchDir(boost::filesystem::path path) {
  std::cout << "Added a new search directory: " << path.string() << std::endl;
  m_searchdirs.emplace_back(std::move(path));
}

boost::filesystem::path AssetManager::getAbsolutePath(const boost::filesystem::path& relative_path) {
  if (relative_path.is_absolute()) {
    assert(fs::is_regular_file(relative_path));
    std::cout << "Found a resource file: " << relative_path.string() << std::endl;
    return relative_path;
  }

  for (fs::path base : m_searchdirs) {
    fs::path absolute_path = base / relative_path;

    if (fs::is_regular_file(absolute_path)) {
      std::cout << "Found a resource file: " << absolute_path.string() << std::endl;
      return absolute_path;
    }
  }

  std::cerr << "Could not find the following file: " << relative_path.string() << std::endl;
  return fs::path();

}
