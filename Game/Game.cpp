// Copyright Tobias Faller 2016

#include "Game.h"

#include <unistd.h>
#include <curses.h>

#include <string>
#include <functional>
#include <utility>

#include "GameLogic.h"

#include "../Display/ColoredDisplay.h"
#include "../Display/HighscoreDisplay.h"

#include "../Map/Map.h"
#include "../Map/State.h"
#include "../Map/StaticMap.h"

namespace Sokoban {

Game::Game(const std::string& directory) {
  _state = SokobanGame::State::LevelSelect;
  _quit = false;
  _directory = directory;

  _mapEntry = nullptr;

  if (initDisplay() != 0) {
    _state = SokobanGame::State::Invalid;
    return;
  }

  _display = new ColoredDisplay(_window);
  if (!_display->isValid()) {
    _state = SokobanGame::State::Invalid;
    return;
  }

  _display->setEnabled(false);
  _display->setRectangle(Rectangle(0, 3, SokobanGame::GAME_WIDTH,
      SokobanGame::GAME_HEIGHT));

  _levelSelector = new LevelSelector(_directory, _window,
    [this](const MapEntry& level, const Map* map, bool highscore) {
      this->onLevelSelected(level, map, highscore);
    });
  _levelSelector->setEnabled(false);
  _levelSelector->setRectangle(Rectangle(0, 0, SokobanGame::GAME_WIDTH,
      SokobanGame::GAME_HEIGHT));

  _highscoreDisplay = new HighscoreDisplay(_window);
  _highscoreDisplay->setEnabled(false);
  _highscoreDisplay->setRectangle(Rectangle(0, 0, SokobanGame::GAME_WIDTH,
      SokobanGame::GAME_HEIGHT));

  _gameLogic.setUndoCount(5);
}

Game::~Game() {
  if (_levelSelector)
    delete _levelSelector;

  if (_display)
    delete _display;

  if (_highscoreDisplay)
    delete _highscoreDisplay;

  if (_mapEntry)
    delete _mapEntry;

  destroyDisplay();
}

void Game::play() {
  if (_state == SokobanGame::State::Invalid)
    return;

  _levelSelector->setEnabled(true);

  while (!_quit) {
    if (!handleKey()) {
      return;
    }

    usleep(10);
  }
}

void Game::onLevelSelected(const MapEntry& level, const Map* map,
    bool highscore) {
  _levelSelector->setEnabled(false);

  if (highscore) {
    _highscoreDisplay->setMap(level.getPath());
    _highscoreDisplay->load();
    _highscoreDisplay->setEnabled(true);

    werase(_window);
    _highscoreDisplay->update();
    wrefresh(_window);

    _state = SokobanGame::State::Highscore;
    return;
  }

  _state = SokobanGame::State::Play;

  if (_mapEntry)
    delete _mapEntry;
  _mapEntry = new MapEntry(level);
  _gameLogic.reset(map);

  wclear(_window);
  _display->setMap(map);
  _display->updateState(_gameLogic.getState());
  _display->setEnabled(true);
  wrefresh(_window);
}

uint32_t Game::initDisplay() {
  _window = initscr();
  if (!_window) {
    printf("Could not init curse!");
    return 1;
  }

  raw();
  nonl();
  cbreak();  // No waiting for char

  noecho();  // Don't print char
  curs_set(false);  // Don't show the cursor

  keypad(stdscr, true);  // Special keycodes.
  nodelay(stdscr, true);  // Don't buffer the input

  return 0;
}

void Game::destroyDisplay() {
  endwin();
}

bool Game::handleKey() {
  int key = getch();

  switch (_state) {
  case SokobanGame::State::LevelSelect:
  {
    switch (key) {
    case 'q':  // Quit / Close
    case KEY_CLOSE:
      return false;
    case 'h':  // Highscore
      _levelSelector->input(SokobanLevelSelector::Input::Highscore);
      break;
    case KEY_UP:
      _levelSelector->input(SokobanLevelSelector::Input::Up);
      break;
    case KEY_DOWN:
      _levelSelector->input(SokobanLevelSelector::Input::Down);
      break;
    case KEY_PPAGE:
      _levelSelector->input(SokobanLevelSelector::Input::PageUp);
      break;
    case KEY_NPAGE:
      _levelSelector->input(SokobanLevelSelector::Input::PageDown);
      break;
    case ' ':
      _levelSelector->input(SokobanLevelSelector::Input::Select);
      break;
    }
    break;
  }
  case SokobanGame::State::Play:
  {
    switch (key) {
    case KEY_CLOSE:  // Quit / Close
      return false;
    case 'm':  // Menu
    case 'q':  // Quit to menu
      _display->setEnabled(false);
      _levelSelector->setEnabled(true);
      _state = SokobanGame::State::LevelSelect;
      return true;
    case KEY_UP:
      if (_gameLogic.update(SokobanGameLogic::Command::Up))
        _display->updateState(_gameLogic.getState());
      break;
    case KEY_DOWN:
      if (_gameLogic.update(SokobanGameLogic::Command::Down))
        _display->updateState(_gameLogic.getState());
      break;
    case KEY_LEFT:
      if (_gameLogic.update(SokobanGameLogic::Command::Left))
        _display->updateState(_gameLogic.getState());
      break;
    case KEY_RIGHT:
      if (_gameLogic.update(SokobanGameLogic::Command::Right))
        _display->updateState(_gameLogic.getState());
      break;
    case 'U':  // undo
    case 'u':
      if (_gameLogic.update(SokobanGameLogic::Command::Undo))
        _display->updateState(_gameLogic.getState());
      break;
    case 'R':  // reset
    case 'r':
      _gameLogic.reset(_display->getMap());
      break;
    default:
      break;
    }

    if (_gameLogic.isFinished()) {
      _highscoreDisplay->setMap(_mapEntry->getPath());
      _highscoreDisplay->load();

      HighscoreEntry entry;
      entry.steps = _gameLogic.getSteps();
      entry.time = _gameLogic.getTime();
      entry.name = std::string();
      _highscoreDisplay->setNewScore(entry);

      _display->setEnabled(false);
      _highscoreDisplay->setEnabled(true);

      werase(_window);
      _highscoreDisplay->update();
      wrefresh(_window);

      _state = SokobanGame::State::Highscore;
      break;
    }

    werase(_window);
    _display->update();

    wmove(_window, 0, 0);
    wprintw(_window, "Time: %.2f sec", _gameLogic.getTime());

    wmove(_window, 1, 0);
    wprintw(_window, "Finished: %s", (_gameLogic.isFinished() ? "yes" : "no"));
    wrefresh(_window);
    break;
  }

  case SokobanGame::Highscore:
    if (_highscoreDisplay->isTypingName()) {
      if (!_highscoreDisplay->input(key)) {
        return false;
      }
    } else {
      switch (key) {
      case KEY_CLOSE:  // Quit / Close
        return false;
      case 'm':  // Menu
      case 'q':  // Quit to menu
        _state = SokobanGame::State::LevelSelect;
        _highscoreDisplay->setEnabled(false);
        _levelSelector->setEnabled(true);
        return true;
      case 'r':  // Replay
        _highscoreDisplay->setEnabled(false);
        onLevelSelected(*_mapEntry, _display->getMap(), false);
        return true;
      }
    }

    werase(_window);
    _highscoreDisplay->update();
    wrefresh(_window);
    break;
  default:
    break;
  }

  return true;
}

void Game::setUndoCount(uint32_t count) {
  _gameLogic.setUndoCount(count);
}

uint32_t Game::getUndoCount() const {
  return _gameLogic.getUndoCount();
}

void Game::setScale(const Size& scale) {
  _display->setScale(scale);
}

Size Game::getScale() const {
  return _display->getScale();
}

}  // namespace Sokoban
