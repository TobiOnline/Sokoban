// Copyright Tobias Faller 2016

#ifndef PROJEKT_RECTANGLE_H_
#define PROJEKT_RECTANGLE_H_

#include <stdint.h>

#include "Coordinate.h"
#include "Size.h"

namespace Sokoban {

/*
 * Defines a rectangle with location and size of type uint32_t.
 */
struct Rectangle {
  uint32_t x;
  uint32_t y;
  uint32_t width;
  uint32_t height;

  /*
   * Creates a new rectangle object with location 0,0 and size 0x0.
   */
  Rectangle();

  /*
   * Creates a new rectangle object with provided position and size.
   */
  Rectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

  /*
   * Creates a new rectangle object with provided position and size.
   */
  Rectangle(const Coordinate& coordinate, const Size& size);

  /*
   * Copies the location and size information from another rectangle object.
   */
  Rectangle(const Rectangle& other);

  /*
   * Destroys this rectangle object.
   */
  ~Rectangle();

  /*
   * Returns the x coordinate of this rectangle.
   */
  uint32_t getX() const;

  /*
   * Returns the y coordinate of this rectangle.
   */
  uint32_t getY() const;

  /*
   * Returns the position of this rectangle.
   */
  Coordinate getPosition() const;

  /*
   * Returns the width of this rectangle.
   */
  uint32_t getWidth() const;

  /*
   * Returns the height of this rectangle.
   */
  uint32_t getHeight() const;

  /*
   * Returns the size of this rectangle.
   */
  Size getSize() const;

  /*
   * Sets the x coordinate of this rectangle.
   * The size and y coordinate stays unaffected.
   */
  void setX(uint32_t x);

  /*
   * Sets the y coordinate of this rectangle.
   * The size and x coordinate stays unaffected.
   */
  void setY(uint32_t y);

  /*
   * Sets the position of this rectangle.
   * The size is not affected by this operation.
   */
  void setPosition(const Coordinate& coordinate);

  /*
   * Sets the width of this rectangle.
   */
  void setWidth(uint32_t width);

  /*
   * Sets the height of this rectangle.
   */
  void setHeight(uint32_t height);

  /*
   * Sets the size of this rectangle.
   */
  void setSize(const Size& size);
};

}  // namespace Sokoban

#endif  // PROJEKT_RECTANGLE_H_
