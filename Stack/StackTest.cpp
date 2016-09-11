// Copyright Tobias Faller 2016

#include "Stack.h"

#include <gtest/gtest.h>

namespace Sokoban {

TEST(Stack, Constructor) {
  Stack stack;

  ASSERT_EQ(1, stack._blockCount);
  ASSERT_EQ(0, stack._blockIndex);

  ASSERT_NE(nullptr, stack._root);
  ASSERT_NE(nullptr, stack._last);
  ASSERT_NE(nullptr, stack._current);

  ASSERT_EQ(0, stack._index);
}

TEST(Stack, PushPop) {
  Stack stack;

  StackFrame stackFrame;
  stackFrame.setDirection(Direction::Right);
  stackFrame.setMoveBox(false);
  stackFrame.setSpecial(false);
  stack.push(stackFrame);

  ASSERT_EQ(0x01, stack._root->_memory[0] & 0x0F);
  ASSERT_EQ(1, stack._index);

  stackFrame.setSpecial(true);
  stackFrame.setMoveBox(true);
  stackFrame.setDirection(Direction::Up);
  stack.push(stackFrame);

  ASSERT_EQ(0xE1, stack._root->_memory[0]);
  ASSERT_EQ(2, stack._index);

  stack.push(stackFrame);

  ASSERT_EQ(0xE1, stack._root->_memory[0]);
  ASSERT_EQ(0x0E, stack._root->_memory[1] & 0x0F);
  ASSERT_EQ(3, stack._index);

  memset(&stackFrame, 0, sizeof(StackFrame));
  stack.pop(&stackFrame);

  ASSERT_EQ(0xE1, stack._root->_memory[0]);
  ASSERT_EQ(Direction::Up, stackFrame.getDirection());
  ASSERT_TRUE(stackFrame.isSpecial());
  ASSERT_TRUE(stackFrame.isMoveBox());
  ASSERT_EQ(2, stack._index);

  memset(&stackFrame, 0, sizeof(StackFrame));
  stack.pop(&stackFrame);

  ASSERT_EQ(0x01, stack._root->_memory[0] & 0x0F);
  ASSERT_EQ(Direction::Up, stackFrame.getDirection());
  ASSERT_TRUE(stackFrame.isSpecial());
  ASSERT_TRUE(stackFrame.isMoveBox());
  ASSERT_EQ(1, stack._index);

  // memset(&stackFrame, 0, sizeof(StackFrame));
  stack.pop(&stackFrame);
  ASSERT_EQ(Direction::Right, stackFrame.getDirection());
  ASSERT_FALSE(stackFrame.isSpecial());
  ASSERT_FALSE(stackFrame.isMoveBox());
}

// 10 memory blocks
constexpr const uint32_t MAX_STACK_TEST_SIZE = 1024 * 1024 * 10;

TEST(Stack, Memory) {
  Stack stack;
  StackFrame frame;

  for (uint32_t counter = 0; counter < MAX_STACK_TEST_SIZE; ++counter) {
    frame._data = (counter & 0x0F);
    stack.push(frame);
  }

  ASSERT_EQ(11, stack._blockCount);
  ASSERT_EQ(10, stack._blockIndex);
  ASSERT_EQ(0, stack._index);

  for (uint32_t counter = MAX_STACK_TEST_SIZE - 1; counter != UINT32_MAX;
      --counter) {
    stack.pop(&frame);
    ASSERT_EQ((counter & 0x0F), frame._data) << "With index " << counter;
  }

  ASSERT_EQ(11, stack._blockCount);
  ASSERT_EQ(0, stack._blockIndex);
  ASSERT_EQ(0, stack._index);
}

}  // namespace Sokoban
