// Copyright Tobias Faller 2016

#include "StackFrame.h"

#include <stdint.h>
#include <gtest/gtest.h>

namespace Sokoban {

TEST(StackFrame, Constructor) {
  StackFrame frame;

  ASSERT_EQ(0, frame._data);
  ASSERT_FALSE(frame.isMoveBox());
  ASSERT_FALSE(frame.isSpecial());
  ASSERT_EQ(Direction::Left, frame.getDirection());
}

TEST(StackFrame, GetSet) {
  StackFrame frame;

  frame.setDirection(Direction::Left);
  ASSERT_EQ(0x00, frame._data);
  ASSERT_FALSE(frame.isMoveBox());
  ASSERT_FALSE(frame.isSpecial());
  ASSERT_EQ(Direction::Left, frame.getDirection());

  frame.setDirection(Direction::Right);
  ASSERT_EQ(0x01, frame._data);
  ASSERT_FALSE(frame.isMoveBox());
  ASSERT_FALSE(frame.isSpecial());
  ASSERT_EQ(Direction::Right, frame.getDirection());

  frame.setDirection(Direction::Up);
  ASSERT_EQ(0x02, frame._data);
  ASSERT_FALSE(frame.isMoveBox());
  ASSERT_FALSE(frame.isSpecial());
  ASSERT_EQ(Direction::Up, frame.getDirection());

  frame.setDirection(Direction::Down);
  ASSERT_EQ(0x03, frame._data);
  ASSERT_FALSE(frame.isMoveBox());
  ASSERT_FALSE(frame.isSpecial());
  ASSERT_EQ(Direction::Down, frame.getDirection());

  frame.setMoveBox(true);
  frame.setDirection(Direction::Right);
  ASSERT_EQ(0x01 | 0x04, frame._data);
  ASSERT_TRUE(frame.isMoveBox());
  ASSERT_FALSE(frame.isSpecial());
  ASSERT_EQ(Direction::Right, frame.getDirection());

  frame.setSpecial(true);
  ASSERT_EQ(0x01 | 0x04 | 0x08, frame._data);
  ASSERT_TRUE(frame.isMoveBox());
  ASSERT_TRUE(frame.isSpecial());
  ASSERT_EQ(Direction::Right, frame.getDirection());

  frame.setSpecial(false);
  ASSERT_EQ(0x01 | 0x04, frame._data);
  ASSERT_TRUE(frame.isMoveBox());
  ASSERT_FALSE(frame.isSpecial());
  ASSERT_EQ(Direction::Right, frame.getDirection());

  frame.setMoveBox(false);
  ASSERT_EQ(0x01, frame._data);
  ASSERT_FALSE(frame.isMoveBox());
  ASSERT_FALSE(frame.isSpecial());
  ASSERT_EQ(Direction::Right, frame.getDirection());

  frame.setDirection(Direction::Up);
  ASSERT_EQ(0x02, frame._data);
  ASSERT_FALSE(frame.isMoveBox());
  ASSERT_FALSE(frame.isSpecial());
  ASSERT_EQ(Direction::Up, frame.getDirection());
}

}  // namespace Sokoban
