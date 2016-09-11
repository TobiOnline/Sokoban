// Copyright Tobias Faller 2016

#ifndef PROJEKT_MAP_STATICMAP_H_
#define PROJEKT_MAP_STATICMAP_H_

#include <stdint.h>
#include <gtest/gtest_prod.h>

#include <set>

#include "../Coordinate.h"

namespace Sokoban {

class MapBuilder;

/*
 * Defines the two types of static elements.
 */
enum StaticType {
  Nothing = 0,
  Block = 1,
  Target = 2
};

/*
 * Defines a index out of bounds error.
 */
constexpr const uint32_t INDEX_OUT_OF_BOUNDS = 0xE1;

/*
 * Defines the static contents of the current map.
 * E.g: walls and targets.
 */
class StaticMap {
  FRIEND_TEST(StaticMap, GetSet);
  FRIEND_TEST(StaticMap, Types);
  FRIEND_TEST(StaticMap, Size);

  friend class MapBuilder;

 private:
  uint8_t* _map;
  uint32_t _width;
  uint32_t _height;

  std::set<Coordinate> _targets;

  /*
   * Protected constructor for the SokobanBuilder.
   */
  StaticMap(uint32_t width, uint32_t height);

  /*
   * Protected constructor for cloning.
   */
  explicit StaticMap(const StaticMap* map);

 public:
  /*
   * Destroys the static map and its internal memory block.
   */
  ~StaticMap();

  /*
   * Returns the field at the provided position of this map or Nothing if the
   * field is empty.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
  StaticType get(Coordinate position) const;

  /*
   * Returns the field at the provided position of this map or Nothing if the
   * field is empty.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
  StaticType get(uint32_t x, uint32_t y) const;

  /*
   * Checks if the field at the provided position is a block.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
  bool isBlock(Coordinate position) const;

  /*
   * Checks if the field at the provided position is a block.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
  bool isBlock(uint32_t x, uint32_t y) const;

  /*
   * Checks if the field at the provided position is a target for a block.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
  bool isTarget(Coordinate position) const;

  /*
   * Checks if the field at the provided position is a target for a block.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
  bool isTarget(uint32_t x, uint32_t y) const;

  /*
   * Checks if the field at the provided position is a empty.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
  bool isEmpty(Coordinate position) const;

  /*
   * Checks if the field at the provided position is a empty.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
  bool isEmpty(uint32_t x, uint32_t y) const;

  /*
   * Sets the field at the provided position to a specified type.
   * This method overwrites the old value.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
  void set(Coordinate position, StaticType type);

  /*
   * Sets the field at the provided position to a specified type.
   * This method overwrites the old value.
   * If the position is out of this map a INDEX_OUT_OF_BOUNDS exception is
   * thrown.
   */
  void set(uint32_t x, uint32_t y, StaticType type);

  /*
   * Returns the width of the map.
   */
  uint32_t getWidth() const;

  /*
   * Returns the height of the map.
   */
  uint32_t getHeight() const;

  /*
   * Clones this StaticMap.
   */
  StaticMap* clone() const;

  /*
   * Returns all positions of the targets.
   */
  const std::set<Coordinate>* getTargets() const;
};

}  // namespace Sokoban

#endif  // PROJEKT_MAP_STATICMAP_H_
