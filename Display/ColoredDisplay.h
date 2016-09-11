// Copyright Tobias Faller 2016

#ifndef PROJEKT_DISPLAY_COLOREDDISPLAY_H_
#define PROJEKT_DISPLAY_COLOREDDISPLAY_H_

#include "Display.h"

#include <curses.h>

#include "CursesDisplay.h"

#include "../Map/Map.h"
#include "../Map/StaticMap.h"
#include "../Map/State.h"

#include "../Coordinate.h"
#include "../Size.h"
#include "../Rectangle.h"

namespace Sokoban {

/*
 * Privides an extended sokoban display supporting colors and a choosable
 * scale factor.
 */
class ColoredDisplay : public CursesDisplay {
 protected:
  Size _scale;

 public:
  /*
   * Creates a new Display at position (0/0) with
   * no map.
   */
  explicit ColoredDisplay(WINDOW* window);

  /*
   * Destroys the Display leaving the window usable.
   */
  virtual ~ColoredDisplay();

  /*
   * Draws the level onto the Display.
   */
  virtual void update();

  /*
   * Sets the scale of this display.
   */
  void setScale(const Size& scale);

  /*
   * Returns the scale of this display.
   */
  Size getScale() const;

 protected:
  /*
   * Returns the color for a displayed character.
   */
  static uint16_t getColorForChar(char c);

  /*
   * Modifies a character before displaying it.
   */
  static char modifyChar(char c);
};

}  // namespace Sokoban

#endif  // PROJEKT_DISPLAY_COLOREDDISPLAY_H_
