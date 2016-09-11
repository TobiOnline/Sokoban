// Copyright Tobias Faller 2016

#ifndef PROJEKT_DISPLAY_DISPLAY_H_
#define PROJEKT_DISPLAY_DISPLAY_H_

#include "../Map/Map.h"
#include "../Map/StaticMap.h"
#include "../Map/State.h"

namespace Sokoban {

/*
 * Provides a basic class for displaying a sokoban map.
 */
class Display {
 protected:
  /*
   * Creates a new display object.
   */
  Display();

  bool _valid;

 public:
  /*
   * Destroys this display instance.
   */
  virtual ~Display();

  /*
   * Sets the underlying map for this display.
   */
  virtual void setMap(const Map* map) = 0;

  /*
   * Updates the displayed state of this display.
   */
  virtual void updateState(const State* state) = 0;

  /*
   * Retrieves if this display was correctly initialized.
   */
  virtual bool isValid() const;
};

}  // namespace Sokoban

#endif  // PROJEKT_DISPLAY_DISPLAY_H_
