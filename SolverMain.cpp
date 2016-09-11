// Copyright Tobias Faller

#include <string>
#include <iostream>

#include "Solver/Solver.h"
#include "Solver/SolverState.h"

#include "Parser/RLEParser.h"

#include "Map/Map.h"
#include "Parser/Parser.h"

using Sokoban::Solver;
using Sokoban::SokobanSolver::State;

using Sokoban::Parser;
using Sokoban::RLEParser;

using Sokoban::Map;

void reportStatus(State state);
void printUsage();

int main(int argc, char** argv) {
  if (argc != 1) {
    printUsage();
    return 0;
  }

  Parser* parser = new RLEParser();
  Solver* solver = new Solver();

  const Map* map = parser->readFile(std::string(argv[0]));
  if (!map) {
    std::cout << "Could not read map!" << std::endl;
    return 0;
  }

  solver->solve(map, reportStatus);

  delete solver;
  delete parser;
}

/*
 * Prints the current solver-status to the console.
 */
void reportStatus(State state) {
  // ToDo
}

/*
 * Prints the usage of this solver program.
 */
void printUsage() {
  std::cout << "Usage: SokobanSolver <level>" << std::endl;
}
