// Copyright Tobias Faller 2016

#ifndef PROJEKT_GAME_HIGHSCORETABLE_H_
#define PROJEKT_GAME_HIGHSCORETABLE_H_

#include <vector>
#include <string>

#include "HighscoreEntry.h"

namespace Sokoban {

namespace SokobanHighscore {

  const constexpr uint32_t MAX_HIGHSCORE_SIZE = 10;

}  // namespace SokobanHighscore

/*
 * Provides a list of highscore entries discarding all elements exceeding
 * MAX_HIGHSCORE_SIZE.
 * The elements are sorted by step-count.
 */
class HighscoreTable {
 private:
  std::vector<HighscoreEntry> _entries;

 public:
  /*
   * Creates a new highscore table.
   */
  HighscoreTable();

  /*
   * Copies a existing highscore table.
   */
  explicit HighscoreTable(const HighscoreTable& table);

  /*
   * Destroys this highscore table and all of its elements.
   */
  ~HighscoreTable();

  /*
   * Loads the highscore table from a file and returns true if succesfull.
   */
  bool load(std::string file);

  /*
   * Saves the highscore table to a file and returns true if succesfull.
   */
  bool save(std::string file) const;

  /*
   * Returns a reference to the internal highscore list.
   */
  const std::vector<HighscoreEntry>* getHighscoreList() const;

  /*
   * Adds a new highscore discarding everything but the
   * SokobanHighscore::MAX_HIGHSOCRE_SIZE elements.
   * The elements are sorted before discarding to keep the best highscores
   * in the list.
   */
  void add(const HighscoreEntry entry);

  /*
   * Removes all highscores from this list.
   */
  void clear();
};

}  // namespace Sokoban

#endif  // PROJEKT_GAME_HIGHSCORETABLE_H_
