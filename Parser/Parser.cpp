// Copyright Tobias Faller 2016

#include "Parser.h"

#include <string>

namespace Sokoban {

Parser::Parser() { }
Parser::~Parser() { }

const Map* Parser::readFile(const std::string path) {
  if (path.empty())
    return nullptr;

  FILE* file = fopen(path.c_str(), "r");
  if (!file)
    return nullptr;

  const Map* map = readStream(file);
  fclose(file);

  return map;
}

}  // namespace Sokoban
