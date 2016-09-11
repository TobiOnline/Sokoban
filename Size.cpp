// Copyright Tobias Faller 2016

#include "Size.h"

namespace Sokoban {

Size::Size() : width(0), height(0) { }
Size::Size(uint32_t w, uint32_t h) : width(w), height(h) { }
Size::Size(const Size& other) : width(other.width), height(other.height) {}
Size::~Size() { }

uint32_t Size::getWidth() {
  return width;
}
uint32_t Size::getHeight() {
  return height;
}

void Size::setWidth(uint32_t w) {
  this->width = w;
}
void Size::setHeight(uint32_t h) {
  this->height = h;
}

bool Size::operator==(const Size& other) const {
  return (other.width == width) && (other.height == height);
}

}  // namespace Sokoban

