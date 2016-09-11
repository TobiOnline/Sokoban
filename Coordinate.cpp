// Copyright Tobias Faller 2016

#include "Coordinate.h"

namespace Sokoban {

Coordinate::Coordinate(uint32_t posX, uint32_t posY) : x(posX), y(posY) { }
Coordinate::Coordinate() : Coordinate(0, 0) { }
Coordinate::~Coordinate() { }

void Coordinate::set(uint32_t posX, uint32_t posY) {
  this->x = posX;
  this->y = posY;
}

uint32_t Coordinate::getX() const {
  return x;
}
uint32_t Coordinate::getY() const {
  return y;
}

bool Coordinate::operator==(const Coordinate& other) const {
  return (x == other.x) && (y == other.y);
}

bool Coordinate::operator<(const Coordinate& other) const {
  return (y < other.y) || (x < other.x);
}

}  // namespace Sokoban
