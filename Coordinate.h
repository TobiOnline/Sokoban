// Copyright Tobias Faller 2016

#ifndef PROJEKT_COORDINATE_H_
#define PROJEKT_COORDINATE_H_

#include <stdint.h>

#include <functional>

namespace Sokoban {

/*
 * Defines a coordinate with x and y position of type uint32_t.
 */
struct Coordinate {
  uint32_t x;
  uint32_t y;

  /*
   * Creates a new location with position 0x0.
   */
  Coordinate();

  /*
   * Creates a new location with provided coordinates.
   */
  Coordinate(uint32_t x, uint32_t y);

  /*
   * Destroys this coordinate object.
   */
  ~Coordinate();

  /*
   * Sets the location of this coordinate object.
   */
  void set(uint32_t x, uint32_t y);

  /*
   * Returns the x coordinate of this object.
   */
  uint32_t getX() const;

  /*
   * Returns the y coordinate of this object.
   */
  uint32_t getY() const;

  /*
   * Compares two locations and returns true if bot x and y coordinates are
   * equal.
   */
  bool operator==(const Coordinate& other) const;

  /*
   * Returns true if the y location of this coordinate is lower.
   * If the y coordinates are equal the algorithm is checking if the x
   * coordinate is lower than the one of the other object.
   */
  bool operator<(const Coordinate& other) const;
};

}  // namespace Sokoban

namespace std {

/*
 * Provides a hash function for the Coordinate struct.
 */
template <> struct hash<Sokoban::Coordinate> {
    size_t operator()(Sokoban::Coordinate const & c) const {
        return hash<uint64_t>()(static_cast<uint64_t>(c.x)
            ^ (static_cast<uint64_t>(c.y) << 32));
    }
};

}  // namespace std

#endif  // PROJEKT_COORDINATE_H_
