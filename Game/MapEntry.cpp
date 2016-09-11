// Copyright Tobias Faller 2016

#include "MapEntry.h"

#include <string>

namespace Sokoban {

MapEntry::MapEntry(const std::string& name, const std::string& path)
  : _name(name), _path(path) { }
MapEntry::MapEntry(const MapEntry& mapEntry)
  : _name(mapEntry._name), _path(mapEntry._path) { }
MapEntry::~MapEntry() { }

const std::string& MapEntry::getName() const {
  return _name;
}

const std::string& MapEntry::getPath() const {
  return _path;
}

}  // namespace Sokoban
