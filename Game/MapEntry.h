// Copyright Tobias Faller 2016

#ifndef PROJEKT_GAME_MAPENTRY_H_
#define PROJEKT_GAME_MAPENTRY_H_

#include <string>

namespace Sokoban {

/*
 * Defines a map selectable by the LevelSelector class.
 * It holds the name of the map name and its path.
 */
class MapEntry {
 private:
  std::string _name;
  std::string _path;

 public:
  /*
   * Creates a new MapEntry with a name and a path.
   */
  MapEntry(const std::string& name, const std::string& path);

  /*
   * Creates a copy of this MapEntry.
   */
  explicit MapEntry(const MapEntry& mapEntry);

  /*
   * Destroys this MapEntry object.
   */
  ~MapEntry();

  /*
   * Returns the name of this MapEntry.
   */
  const std::string& getName() const;

  /*
   * Returns the path of this MapEntry.
   */
  const std::string& getPath() const;
};

}  // namespace Sokoban

#endif  // PROJEKT_GAME_MAPENTRY_H_
