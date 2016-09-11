// Copyright Tobias Faller 2016

#ifndef PROJEKT_GAME_HIGHSCOREENTRY_H_
#define PROJEKT_GAME_HIGHSCOREENTRY_H_

#include <string>

namespace Sokoban {

/*
 * Provides a highscore list entry containing a needed time in seconds,
 * a number of steps and a possibly empty player name.
 */
struct HighscoreEntry {
  double time;
  uint32_t steps;
  std::string name;
};

}  // namespace Sokoban

#endif  // PROJEKT_GAME_HIGHSCOREENTRY_H_
