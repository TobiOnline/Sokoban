// Copyright Tobias Faller 2016

#ifndef PROJEKT_GAME_LEVELSELECTOR_H_
#define PROJEKT_GAME_LEVELSELECTOR_H_

#include <curses.h>

#include <string>
#include <vector>
#include <functional>

#include "MapEntry.h"
#include "../Coordinate.h"

#include "../Parser/ExpandedParser.h"
#include "../Parser/RLEParser.h"

#include "../Display/Display.h"
#include "../Display/CursesDisplay.h"

namespace Sokoban {

namespace SokobanLevelSelector {

const constexpr uint32_t DISPLAYED_ROWS = 10;
const constexpr uint32_t WINDOW_WIDTH = 30;

/*
 * Descibes all possible actions supported by the LevelSelector class.
 */
enum Input : uint32_t {
  Up, Down, PageUp, PageDown, Select, Highscore
};

}  // namespace SokobanLevelSelector

/*
 * A class for displaying a list of sokoban levels.
 * It provides a adjustable number of files and scrolling.
 * If a file is selected the callback function is called.
 */
class LevelSelector {
 private:
  const std::string& _path;
  std::string _relativePath;
  std::function<void(const MapEntry&, const Map* map, bool highscore)>
    _callback;

  std::vector<std::string> _directories;
  std::vector<MapEntry> _maps;

  uint32_t _index;

  WINDOW* _window;
  Rectangle _rectangle;
  uint32_t _maxFileName;

  bool _enabled;

  ExpandedParser _expandedParser;
  RLEParser _rleParser;
  CursesDisplay* _display;

  /*
   * Updates the drawn content of this level selector.
   */
  void update();

  /*
   * Reloads the content of the current directory.
   */
  void refreshContent();

 public:
  /*
   * Creates a new LevelSelector.
   */
  LevelSelector(const std::string& _path, WINDOW* window,
      std::function<void(const MapEntry&, const Map*, bool)> callback);

  /*
   * Destroys this LevelSelector instance.
   */
  ~LevelSelector();

  /*
   * Enables / Disables this LevelSelector instance.
   */
  void setEnabled(bool enabled);

  /*
   * Returns if this LevelSelecltor is enabled.
   */
  bool isEnabled() const;

  /*
   * Applies an input-command to this LevelSelector instance.
   */
  void input(SokobanLevelSelector::Input input);

  /*
   * Returns the position of this LevelSelector.
   */
  Coordinate getPosition() const;

  /*
   * Sets the position of this LevelSelector.
   */
  void setPosition(const Coordinate& coordinate);

  /*
   * Returns the size of this LevelSelector.
   */
  Size getSize() const;

  /*
   * Sets the size of this LevelSelector.
   */
  void setSize(const Size& coordinate);

  /*
   * Returns the drawing rectangle of this LevelSelector.
   */
  Rectangle getRectangle() const;

  /*
   * Sets the drawing rectangle of this LevelSelector.
   */
  void setRectangle(const Rectangle& rectangle);

  /*
   * Gets the maximum file name size displayed.
   * If the name is longer it will be clipped in the current directory
   * listing.
   */
  uint32_t getMaxFileNameSize() const;

  /*
   * Sets the maximum file name size displayed.
   * If the name is longer it will be clipped in the current directory
   * listing.
   */
  void setMaxFileNameSize(uint32_t max);
};

}  // namespace Sokoban

#endif  // PROJEKT_GAME_LEVELSELECTOR_H_
