// Copyright Tobias Faller 2016

#include <iostream>
#include <cstdio>
#include <string>

#include "Game/Game.h"
#include "Size.h"

using std::cout;
using std::endl;

void printUsage(char* prog);

/*
 * Provides the main method and option-parsing.
 */
int main(int argc, char** argv) {
  uint32_t undoCount = 0;
  Sokoban::Size scale(0, 0);

  int opt;
  while ((opt = getopt(argc, argv, "u:x:y:")) != -1) {
    switch (opt) {
      case 'u':
        try {
          int64_t value = std::stoul(std::string(optarg));
          if ((value <= 0) || (value > UINT32_MAX)) {
            printUsage(argv[0]);
            return 1;
          }

          undoCount = value;
        } catch (const std::invalid_argument& invArgEx) {
          printUsage(argv[0]);
          return 1;
        } catch (const std::out_of_range& outOfRngEx) {
          printUsage(argv[0]);
          return 1;
        }

        break;
      case 'x':
        try {
          int64_t value = std::stoul(std::string(optarg));
          if ((value <= 0) || (value > UINT32_MAX)) {
            printUsage(argv[0]);
            return 1;
          }

          scale.width = value;
        } catch (const std::invalid_argument& invArgEx) {
          printUsage(argv[0]);
          return 1;
        } catch (const std::out_of_range& outOfRngEx) {
          printUsage(argv[0]);
          return 1;
        }

        break;
      case 'y':
        try {
          int64_t value = std::stoul(std::string(optarg));
          if ((value <= 0) || (value > UINT32_MAX)) {
            printUsage(argv[0]);
            return 1;
          }

          scale.height = value;
        } catch (const std::invalid_argument& invArgEx) {
          printUsage(argv[0]);
          return 1;
        } catch (const std::out_of_range& outOfRngEx) {
          printUsage(argv[0]);
          return 1;
        }

        break;
      case '?':
        printUsage(argv[0]);
        return 1;
      default:
        abort();
    }
  }

  Sokoban::Game game((optind < argc) ? argv[optind] : ".");

  if (undoCount != 0)
    game.setUndoCount(undoCount);

  Sokoban::Size displayScale = game.getScale();
  displayScale.width = (scale.width > 0) ? scale.width : displayScale.width;
  displayScale.height = (scale.height > 0) ? scale.height : displayScale.height;
  game.setScale(displayScale);

  game.play();
}

/*
 * Prints the usage information of this program.
 */
void printUsage(char* prog) {
  cout << endl;
  cout << "Usage: " << prog << " arguments <levels>" << endl;
  cout << "Arguments:" << endl;
  cout << "\tu: Amount of steps which can be undone" << endl;
  cout << "\tx: Horizontal scale of the display" << endl;
  cout << "\ty: Vertical scale of the display" << endl;
  cout << endl;
  cout << "<levels>:" << endl;
  cout << "\tDirectory to list level files out of" << endl;
}
