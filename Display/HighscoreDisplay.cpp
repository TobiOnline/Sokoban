// Copyright Tobias Faller 2016

#include "HighscoreDisplay.h"

#include <vector>
#include <string>
#include <cstring>

#include "../Rectangle.h"
#include "../Game/HighscoreEntry.h"
#include "../Game/LevelSelector.h"

namespace Sokoban {

HighscoreDisplay::HighscoreDisplay(WINDOW* window)
    : _window(window), _enabled(false), _location(0, 0, 30, 15) {
  _newScore = nullptr;
  _creatingNewScore = false;
  _newScoreName = std::string("No name");
  _map = std::string();

  _highscore = new HighscoreTable();
}

HighscoreDisplay::~HighscoreDisplay() {
  if (_highscore)
    delete _highscore;

  if (_newScore)
    delete _newScore;
}

void HighscoreDisplay::setEnabled(bool enabled) {
  _enabled = enabled;
}

bool HighscoreDisplay::isEnabled() const {
  return _enabled;
}

void HighscoreDisplay::setRectangle(const Rectangle& rectangle) {
  _location = rectangle;
}

const Rectangle& HighscoreDisplay::getRectangle() const {
  return _location;
}

HighscoreTable* HighscoreDisplay::getHighscore() const {
  return _highscore;
}

bool HighscoreDisplay::load() {
  std::string name(_map);
  name.append(".score");

  return _highscore->load(name);
}

void HighscoreDisplay::setMap(const std::string& map) {
  _map = map;
}

void HighscoreDisplay::setNewScore(const HighscoreEntry& entry) {
  _creatingNewScore = true;

  if (_newScore)
    delete _newScore;

  _newScore = new HighscoreEntry(entry);
}

void HighscoreDisplay::resetNewScore() {
  _creatingNewScore = false;
}

void HighscoreDisplay::update() {
  wmove(_window, _location.y, _location.x);
  waddstr(_window, "\tSteps Time Name");

  uint32_t scoreOffset = 2;
  if (_newScore) {
    scoreOffset = 6;

    wmove(_window, _location.y + 2, _location.x);
    waddstr(_window, "New Score:");

    wmove(_window, _location.y + 3, _location.x);
    waddstr(_window, "\t");
    waddstr(_window, scoreToString(*_newScore).c_str());

    if (_creatingNewScore) {
      wmove(_window, _location.y + 4, _location.x);
      waddstr(_window, "Name: ");
      wattron(_window, A_STANDOUT);
      waddstr(_window, _newScoreName.c_str());

      wattron(_window, A_UNDERLINE | A_BLINK);
      waddch(_window, ' ');

      wattroff(_window, A_STANDOUT | A_UNDERLINE | A_BLINK);
    }
  }

  const std::vector<HighscoreEntry>* entries = _highscore->getHighscoreList();
  std::vector<HighscoreEntry>::const_iterator it = entries->cbegin();
  std::vector<HighscoreEntry>::const_iterator end = entries->cend();

  char buffer[128];

  uint32_t index = 0;
  while (it != end) {
    wmove(_window, _location.y + scoreOffset + index, _location.x);

    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "%u", ++index);

    waddstr(_window, buffer);
    waddstr(_window, "\t");
    waddstr(_window, scoreToString(*it).c_str());

    ++it;
  }
}

std::string HighscoreDisplay::scoreToString(const HighscoreEntry& score) {
  std::string s;
  char buffer[512];

  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, sizeof(buffer), "%5u %.2f %s", score.steps, score.time,
      score.name.c_str());

  s.append(buffer);

  return std::move(s);
}

bool HighscoreDisplay::input(uint32_t key) {
  if (((key >= 'a') && (key <= 'z')) || ((key >= 'A') && (key <= 'Z'))
      || (key == ' ')) {
    char buffer[2];

    buffer[0] = key;
    buffer[1] = '\0';

    _newScoreName.append(buffer);
  } else {
    switch (key) {
    /* case 'q':  // Quit / Close
    case KEY_CLOSE:
      return false; */
    case '\b':  // Backspace
    case 127:  // Delete
    case KEY_BACKSPACE:
      if (_newScoreName.size() > 0)
        _newScoreName.pop_back();
      break;
    case KEY_ENTER:
    case '\r':
    case '\n':
      _newScore->name = std::string(_newScoreName);
      resetNewScore();

      std::string name(_map);
      name.append(".score");

      // We only modify a copy here to keep the new entry splitted.
      HighscoreTable newTable(*_highscore);
      newTable.add(*_newScore);
      newTable.save(name);
      break;
    }
  }

  return true;
}

bool HighscoreDisplay::isTypingName() const {
  return _creatingNewScore;
}

}  // namespace Sokoban
