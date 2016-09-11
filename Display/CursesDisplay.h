// Copyright Tobias Faller 2016

#ifndef PROJEKT_DISPLAY_CURSESDISPLAY_H_
#define PROJEKT_DISPLAY_CURSESDISPLAY_H_

#include "Display.h"

#include <curses.h>

#include "../Map/Map.h"
#include "../Map/StaticMap.h"
#include "../Map/State.h"

#include "../Coordinate.h"
#include "../Size.h"
#include "../Rectangle.h"

namespace Sokoban {

/*
 * Provides a interface for a (n)curses driven display.
 * The display provides a basic sheme also used by the sokoban level format.
 */
class CursesDisplay : public Display {
 protected:
  WINDOW* _window;

  const Map* _map;
  const StaticMap* _staticMap;
  const State* _state;

  bool _enabled;
  Rectangle _rectangle;

 public:
  /*
   * Creates a new Display at position (0/0) with
   * no map.
   */
  explicit CursesDisplay(WINDOW* window);

  /*
   * Destroys the Display leaving the window usable.
   */
  virtual ~CursesDisplay();

  /*
   * Sets the underlying map for this Display.
   */
  void setMap(const Map* map) override;

  /*
   * Updates the displayed state of this Display.
   */
  void updateState(const State* state) override;

  /*
   * Returns the drawn map.
   */
  const Map* getMap() const;

  /*
   * Returns the drawn state.
   */
  const State* getState() const;

  /*
   * Enables / disables this Display instance.
   */
  void setEnabled(bool enabled);

  /*
   * Sets the position of this Display instance.
   */
  void setPosition(const Coordinate& position);

  /*
   * Gets the current position of this Display.
   */
  Coordinate getPosition() const;

  /*
   * Sets the size of this Display.
   */
  void setSize(const Size& size);

  /*
   * Returns the size of this Display.
   */
  Size getSize() const;

  /*
   * Sets the rectangle of this Dispaly.
   */
  void setRectangle(const Rectangle& rectangle);

  /*
   * Gets the rectangle of this Display.
   */
  Rectangle getRectangle() const;

  /*
   * Returns if this Display is enabled.
   */
  bool isEnabled();

  /*
   * Draws the level onto the Display.
   */
  virtual void update();

 protected:
  static char getCharForState(StaticType type, const State* state,
      const Coordinate& coordinate);
};

}  // namespace Sokoban

#endif  // PROJEKT_DISPLAY_CURSESDISPLAY_H_
