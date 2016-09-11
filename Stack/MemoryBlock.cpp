// Copyright Tobias Faller 2016

#include "../Stack/MemoryBlock.h"

namespace Sokoban {

namespace SokobanStack {

MemoryBlock::MemoryBlock() : _nextBlock(nullptr), _previousBlock(nullptr) {
  _memory = new uint8_t[MEMORY_BLOCK_SIZE];
}

MemoryBlock::~MemoryBlock() {
  delete[] _memory;
}

}  // namespace SokobanStack

}  // namespace Sokoban
