// Copyright Tobias Faller 2016

#ifndef PROJEKT_STACK_MEMORYBLOCK_H_
#define PROJEKT_STACK_MEMORYBLOCK_H_

#include <stdint.h>
#include <gtest/gtest_prod.h>

namespace Sokoban {

class Stack;
class Stack_PushPop_Test;

namespace SokobanStack {

constexpr const uint32_t MEMORY_BLOCK_SIZE = 512 * 1024;

/*
 * Provides a managed block of memory directly accessible by the stack class.
 */
class MemoryBlock {
  FRIEND_TEST(Sokoban::Stack, PushPop);

  friend class Sokoban::Stack;

 private:
  SokobanStack::MemoryBlock* _nextBlock;
  SokobanStack::MemoryBlock* _previousBlock;

  uint8_t* _memory;

 public:
  /*
   * Creates a new memory block with a size of MEMORY_BLOCK_SIZE bytes.
   */
  MemoryBlock();

  /*
   * Destroys the memory block with its data.
   */
  ~MemoryBlock();
};

}  // namespace SokobanStack
}  // namespace Sokoban

#endif  // PROJEKT_STACK_MEMORYBLOCK_H_
