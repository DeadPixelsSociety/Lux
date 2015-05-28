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
#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

class AssetManager {
public:
  void addSearchDir(boost::filesystem::path path);

  boost::filesystem::path getAbsolutePath(const boost::filesystem::path& relative_path);

private:
  std::vector<boost::filesystem::path> m_searchdirs;
};

#endif // GAME_ASSETS_H
