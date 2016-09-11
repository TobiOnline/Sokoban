// Copyright Tobias Faller 2016

#ifndef PROJEKT_SIZE_H_
#define PROJEKT_SIZE_H_

#include <stdint.h>

namespace Sokoban {

/*
 * Defines a combination of width and height of type uint32_t.
 */
struct Size {
  uint32_t width;
  uint32_t height;

  /*
   * Creates a new object with size of 0x0.
   */
  Size();

  /*
   * Creates a new object with a specified width and height.
   */
  Size(uint32_t width, uint32_t height);

  /*
   * Copies the size of another object.
   */
  Size(const Size& other);

  /*
   * Destroys this size object.
   */
  ~Size();

  /*
   * Returns the width of this object.
   */
  uint32_t getWidth();

  /*
   * Returns the height of this object.
   */
  uint32_t getHeight();

  /*
   * Sets the width of this object.
   */
  void setWidth(uint32_t width);

  /*
   * Sets the height of this object.
   */
  void setHeight(uint32_t height);

  /*
   * Compares this object to another size object and returns true if
   * both width and height of the objects are equal.
   */
  bool operator==(const Size& other) const;
};

}  // namespace Sokoban

#endif  // PROJEKT_SIZE_H_
