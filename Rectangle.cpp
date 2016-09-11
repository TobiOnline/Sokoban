// Copyright Tobias Faller 2016

#include "Rectangle.h"
#include "Coordinate.h"
#include "Size.h"

namespace Sokoban {

Rectangle::Rectangle() : x(0), y(0), width(0), height(0) { }
Rectangle::Rectangle(uint32_t posX, uint32_t posY, uint32_t w, uint32_t h)
    : x(posX), y(posY), width(w), height(h) { }
Rectangle::Rectangle(const Coordinate& coordinate, const Size& size)
    : x(coordinate.x), y(coordinate.y), width(size.width), height(size.height)
{ }
Rectangle::Rectangle(const Rectangle& other)
    : x(other.x), y(other.y), width(other.width), height(other.height) { }
Rectangle::~Rectangle() { }

uint32_t Rectangle::getX() const {
  return x;
}
uint32_t Rectangle::getY() const {
  return y;
}
Coordinate Rectangle::getPosition() const {
  return std::move(Coordinate(x, y));
}

uint32_t Rectangle::getWidth() const {
  return width;
}
uint32_t Rectangle::getHeight() const {
  return height;
}
Size Rectangle::getSize() const {
  return std::move(Size(width, height));
}

void Rectangle::setX(uint32_t posX) {
  x = posX;
}
void Rectangle::setY(uint32_t posY) {
  y = posY;
}
void Rectangle::setPosition(const Coordinate& coordinate) {
  x = coordinate.x;
  y = coordinate.y;
}

void Rectangle::setWidth(uint32_t w) {
  width = w;
}
void Rectangle::setHeight(uint32_t h) {
  height = h;
}
void Rectangle::setSize(const Size& size) {
  width = size.width;
  height = size.height;
}

}  // namespace Sokoban
