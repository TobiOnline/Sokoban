// Copyright Tobias Faller 2016

#ifndef PROJEKT_DISPLAY_HIGHSCOREDISPLAY_H_
#define PROJEKT_DISPLAY_HIGHSCOREDISPLAY_H_

#include <curses.h>

#include <vector>
#include <string>

#include "../Rectangle.h"
#include "../Game/HighscoreEntry.h"
#include "../Game/HighscoreTable.h"

namespace Sokoban {

/*
 * Proivdes a display for all highscores of a level.
 * If a new record is achieved it can be passed with the setNewHighscore
 * function to enable the user to input a player name.
 */
class HighscoreDisplay {
 private:
  WINDOW* _window;

  bool _enabled;
  Rectangle _location;

  std::string _map;
  bool _creatingNewScore;
  std::string _newScoreName;
  HighscoreEntry* _newScore;
  HighscoreTable* _highscore;

 public:
  /*
   * Creates a new HighscoreDisplay drawing its contents to the provided
   * window.
   */
  explicit HighscoreDisplay(WINDOW* window);

  /*
   * Destroys this HighscoreDisplay.
   */
  virtual ~HighscoreDisplay();

  /*
   * Receives input from the user.
   * Returns false if a quit signal was detected.
   */
  bool input(uint32_t key);

  /*
   * Sets if this display is enabled.
   */
  void setEnabled(bool enabled);

  /*
   * Returns if this display is enabled.
   */
  bool isEnabled() const;

  /*
   * Sets the rectangle of this display.
   */
  void setRectangle(const Rectangle& rectangle);

  /*
   * Returns the rectangle of this dispaly.
   */
  const Rectangle& getRectangle() const;

  /*
   * Sets the new generated highscore entry.
   */
  void setNewScore(const HighscoreEntry* entry, const std::string& map);

  /*
   * Loads the saved highscores for the provided map
   * from the disk.
   * Returns if the highscore list could be loaded.
   */
  bool load(const std::string& map);

  /*
   * Returns the current highscore table.
   */
  HighscoreTable* getHighscore() const;

  /*
   * Draws the content onto the screen.
   */
  void update();

  /*
   * Returns if the user is typing a name.
   */
  bool isTypingName() const;

 protected:
  /*
   * Converts a highscore entry to a string.
   */
  static std::string scoreToString(const HighscoreEntry& score);
};

}  // namespace Sokoban

#endif  // PROJEKT_DISPLAY_HIGHSCOREDISPLAY_H_
