// Copyright Tobias Faller 2016

#ifndef PROJEKT_GAME_GAME_H_
#define PROJEKT_GAME_GAME_H_

#include <curses.h>

#include <string>

#include "MapEntry.h"
#include "LevelSelector.h"

#include "GameLogic.h"

#include "../Display/ColoredDisplay.h"
#include "../Display/HighscoreDisplay.h"

namespace Sokoban {

class Game;

namespace SokobanGame {

constexpr const uint32_t GAME_WIDTH = 30;
constexpr const uint32_t GAME_HEIGHT = 15;

enum State : uint32_t {
  Invalid, LevelSelect, Play, Highscore
};

}  // namespace SokobanGame

/*
 * Provides a class for a visual sokoban instance.
 * The game is started via the play function and provides a level selector
 * able to handle folders and display a preview of the level.
 */
class Game {
 private:
  std::string _directory;
  SokobanGame::State _state;

  WINDOW* _window;
  LevelSelector* _levelSelector;
  ColoredDisplay* _display;
  HighscoreDisplay* _highscoreDisplay;

  const MapEntry* _mapEntry;
  GameLogic _gameLogic;

  bool _quit;

  /*
   * Initializes the display and ncurses.
   */
  uint32_t initDisplay();

  /*
   * Destroys the display and uninitializes ncurses.
   */
  void destroyDisplay();

  /*
   * Gets called if a level was selected via LevelSelector.
   */
  void onLevelSelected(const MapEntry& level, const Map* map, bool highscore);

  /*
   * Handles user input
   */
  bool handleKey();

 public:
  /*
   * Creates a new Game instance with a working-directory.
   */
  explicit Game(const std::string& directory);

  /*
   * Destroys this instance of Sokoban.
   */
  ~Game();

  /*
   * Starts this game.
   */
  void play();

  /*
   * Sets the number of steps which can be undone.
   */
  void setUndoCount(uint32_t count);

  /*
   * Returns the number of steps which can be undone.
   */
  uint32_t getUndoCount() const;

  /*
   * Sets the scale of the level display.
   */
  void setScale(const Size& scale);

  /*
   * Returns the scale of the level display.
   */
  Size getScale() const;
};

}  // namespace Sokoban

#endif  // PROJEKT_GAME_GAME_H_
