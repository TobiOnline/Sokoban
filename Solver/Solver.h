// Copyright Tobias Faller 2016

#ifndef PROJEKT_SOLVER_SOLVER_H_
#define PROJEKT_SOLVER_SOLVER_H_

#include "SolverState.h"
#include "../Map/Map.h"


namespace Sokoban {

/*
 * Provides a class for solving already loaded sokoban levels.
 * This class will probably never be implemented because of the lack of free
 * time.
 */
class Solver {
 public:
  void solve(const Map* map,
    void(*callback)(Sokoban::SokobanSolver::State state));
};

}  // namespace Sokoban

#endif  // PROJEKT_SOLVER_SOLVER_H_
