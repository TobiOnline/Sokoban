// Copyright Tobias Faller 2016

#include "Stack.h"

#include "MemoryBlock.h"
#include "StackFrame.h"

namespace Sokoban {

/*
 * This stack is implemented as list of memory blocks.
 * The variable _index points always at the next free element of the current
 * block.
 * If no more blocks are available memory is allocated and appended to the
 * linked list.
 * If the number of free blocks is larger than MAX_BLOCKS_FREE then
 * the unused blocks are deleted until a unused block-count of
 * MAX_BLOCKS_FREE is reached.
 */

Stack::Stack() {
  _root = new SokobanStack::MemoryBlock;
  _last = _current = _root;
  _index = 0;
  _blockCount = 1;
  _blockIndex = 0;
}

Stack::~Stack() {
  while (_last->_previousBlock) {
    SokobanStack::MemoryBlock* currentBlock = _last;
    _last = _last->_previousBlock;

    delete currentBlock;
  }

  delete _root;
}

void Stack::get(StackFrame* frame) const {
  if ((_index == 0) && (_current == _root))
    return;

  uint8_t* block
      = ((_index == 0) ? _current->_previousBlock : _current)->_memory;
  uint32_t position = (_index == 0) ?
      ((SokobanStack::MEMORY_BLOCK_SIZE * 2) - 1) : (_index - 1);

  frame->_data = (block[position / 2] >> ((position % 2) * 4)) & 0x0F;
}

void Stack::pop(StackFrame* frame) {
  if ((_index == 0) && (_current == _root))
    return;

  get(frame);

  if (_index != 0) {
    _index--;
    return;
  }

  _index = (SokobanStack::MEMORY_BLOCK_SIZE * 2) - 1;
  _current = _current->_previousBlock;
  _blockIndex--;

  while ((_blockCount - _blockIndex) > MAX_BLOCKS_FREE) {
    _last = _last->_previousBlock;
    _blockCount--;

    delete _last->_nextBlock;
  }
}

void Stack::push(const StackFrame& frame) {
  _current->_memory[_index / 2]
    &= ~((static_cast<uint8_t>(0x0F)) << ((_index % 2) * 4));
  _current->_memory[_index / 2] |= (frame._data << ((_index % 2) * 4));

  _index++;
  if (_index / 2 >= SokobanStack::MEMORY_BLOCK_SIZE) {
    _index = 0;

    if (_current != _last) {
      _current = _current->_nextBlock;
    } else {
      _last = new SokobanStack::MemoryBlock;
      _last->_previousBlock = _current;
      _current->_nextBlock = _last;

      _current = _last;

      _blockCount++;
      _blockIndex++;
    }
  }
}

bool Stack::isEmpty() const {
  return ((_index == 0) && (_current == _root));
}

}  // namespace Sokoban
