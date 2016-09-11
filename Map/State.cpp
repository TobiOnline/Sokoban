// Copyright Tobias Falelr 2016

#include "State.h"

namespace Sokoban {

State::State() : _player(0, 0), _boxes() {}
State::State(const State* state)
    : _player(state->_player),
      _boxes(state->_boxes.cbegin(), state->_boxes.cend()) {}
State::~State() {}

const std::unordered_map<Coordinate, BoxState>* State::getBoxes() const {
  return &_boxes;
}
std::unordered_map<Coordinate, BoxState>* State::getBoxes() {
  return &_boxes;
}

Coordinate State::getPlayerPosition() const {
  return _player;
}

void State::setPlayerPosition(Coordinate position) {
  _player = position;
}

State* State::clone() const {
  return new State(this);
}

}  // namespace Sokoban
