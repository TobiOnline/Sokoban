// Copyright Tobias Faller

#include "StackFrame.h"

#include <stdint.h>

#include "../Direction.h"

namespace Sokoban {

StackFrame::StackFrame() : _data(0x00) { }
StackFrame::StackFrame(const StackFrame& frame) : _data(frame._data) { }
StackFrame::~StackFrame() { }

Direction StackFrame::getDirection() const {
  return static_cast<Direction>(_data & 0x03);
}
void StackFrame::setDirection(Direction direction) {
  _data &= ~(static_cast<uint8_t>(0x03));
  _data |= direction;
}

bool StackFrame::isMoveBox() const {
  return (_data & 0x04);
}
void StackFrame::setMoveBox(bool moveBox) {
  if (moveBox) {
    _data |= 0x04;
  } else {
    _data &= ~(static_cast<uint8_t>(0x04));
  }
}

bool StackFrame::isSpecial() const {
  return (_data & 0x08);
}
void StackFrame::setSpecial(bool special) {
  if (special) {
    _data |= 0x08;
  } else {
    _data &= ~(static_cast<uint8_t>(0x08));
  }
}

}  // namespace Sokoban
