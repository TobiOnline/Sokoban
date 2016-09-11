// Copyright Tobias Faller 2016

#ifndef PROJEKT_MAP_MAPBUILDER_H_
#define PROJEKT_MAP_MAPBUILDER_H_

#include <stdint.h>

#include <vector>
#include <utility>

#include "Map.h"
#include "StaticMap.h"
#include "../Coordinate.h"

namespace Sokoban {

namespace SokobanBuilder {

/*
 * Defines all possible errors thrown by the MapBuilder class.
 */
enum Error : uint32_t {
  Success, MoreTargetsThanBoxes, SpotTaken
};

}  // namespace SokobanBuilder

/*
 * Defines a builder class for creating Sokoban levels.
 * This builder dynamically allocates memory and returns the
 * fixed-size map.
 */
class MapBuilder {
 private:
  std::vector<Coordinate> _blocks;
  std::vector<Coordinate> _boxes;
  std::vector<Coordinate> _targets;

  Coordinate _player;

  uint32_t _width;
  uint32_t _height;

 public:
  /*
   * Creates a new Sokoban MapBuilder to create levels dynamically.
   */
  MapBuilder();

  /*
   * Destroys this builder and its internal state.
   */
  ~MapBuilder();

  /*
   * Creates a new map without destroying the internal state of this builder.
   * Returns error code Success if the created map is valid.
   * If there are more targets than boxes MoreTargetsThanBoxes will be returned.
   * If there overlapping components (at the same spot) a SpotTaken error
   * will be returned.
   */
  std::pair<SokobanBuilder::Error, const Map*> build() const;

  /*
   * Resets the state of this builder to an empty map.
   */
  MapBuilder* reset();

  /*
   * Adds a block at the provided coordinate.
   */
  MapBuilder* addBlock(Coordinate position);

  /*
   * Adds a block at the provided coordinate.
   */
  MapBuilder* addBlock(uint32_t x, uint32_t y);

  /*
   * Adds a box at the provided coordinate.
   */
  MapBuilder* addBox(Coordinate position);

  /*
   * Adds a box at the provided coordinate.
   */
  MapBuilder* addBox(uint32_t x, uint32_t y);

  /*
   * Sets the position of the player to the provided coordinate.
   */
  MapBuilder* setPlayer(Coordinate position);

  /*
   * Sets the position of the player to the provided coordinate.
   */
  MapBuilder* setPlayer(uint32_t x, uint32_t y);

  /*
   * Adds a target to put a box on at the provided coordinate.
   */
  MapBuilder* addTarget(Coordinate position);

  /*
   * Adds a target to put a box on at the provided coordinate.
   */
  MapBuilder* addTarget(uint32_t x, uint32_t y);

  /*
   * Adds a square of blocks to this builder starting from <from> and going
   * to <to> (inclusive).
   */
  MapBuilder* addBlocks(Coordinate from, Coordinate to);

  /*
   * Adds a square of blocks to this builder starting from <from> and going
   * to <to> (inclusive).
   */
  MapBuilder* addBlocks(uint32_t fromX, uint32_t fromY, uint32_t toX,
      uint32_t toY);
};

}  // namespace Sokoban

#endif  // PROJEKT_MAP_MAPBUILDER_H_
