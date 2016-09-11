// Copyright Tobias Faller 2016

#ifndef PROJEKT_STACK_STACK_H_
#define PROJEKT_STACK_STACK_H_

#include <gtest/gtest.h>

#include "MemoryBlock.h"
#include "StackFrame.h"

namespace Sokoban {

constexpr const uint32_t MAX_BLOCKS_FREE = 512;

/*
 * Provides a stack class containing a variable amount of elements stored in
 * continous blocks of memory. The stack frames (3 to 4 bits of size) are
 * stored as set of two in one byte.
 * This should save memory and runtime (allocation) for using with the solver.
 */
class Stack {
  FRIEND_TEST(Stack, Constructor);
  FRIEND_TEST(Stack, PushPop);
  FRIEND_TEST(Stack, Memory);

 private:
  SokobanStack::MemoryBlock* _root;
  SokobanStack::MemoryBlock* _current;
  SokobanStack::MemoryBlock* _last;

  uint32_t _blockCount;
  uint32_t _blockIndex;
  uint32_t _index;

 public:
  /*
   * Creates a new stack with initial size 0 and one memory block pre-allocated.
   */
  Stack();

  /*
   * Destroys this stack and all of its data.
   */
  ~Stack();

  /*
   * Retrieves the first element of this stack and writes it into
   * the provided StackFrame.
   */
  void get(StackFrame* frame) const;

  /*
   * Appends the provided element to this stack.
   * This method allocates memory if needed.
   */
  void push(const StackFrame& frame);

  /*
   * Retrieves and deletes the first element of this stack and writes it into
   * the provided StackFrame.
   */
  void pop(StackFrame* frame);

  /*
   * Returns true if this stack is empty. False if not.
   */
  bool isEmpty() const;
};

}  // namespace Sokoban

#endif  // PROJEKT_STACK_STACK_H_
