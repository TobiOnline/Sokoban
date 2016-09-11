// Copyright Tobias Faller 2016

#ifndef PROJEKT_PARSER_PARSER_H_
#define PROJEKT_PARSER_PARSER_H_

#include <stdio.h>

#include <string>
#include <iostream>

#include "../Map/Map.h"

namespace Sokoban {

namespace SokobanParser {

enum Error : uint32_t {
  InvalidChar = 0xE1
};

}  // namespace SokobanParser

/*
 * Defines a basic interface for the sokoban level parser.
 */
class Parser {
 protected:
  /*
   * Creates a new parser for a sokoban map.
   */
  Parser();

 public:
  /*
   * Destroys this parser.
   */
  virtual ~Parser();

  /*
   * Reads a file stream and interprets it as sokoban level.
   */
  virtual const Map* readStream(FILE* stream) = 0;

  /*
   * Reads a stream and interprets it as sokoban level.
   */
  virtual const Map* readStream(std::istream* stream) = 0;

  /*
   * Reads some data and interprets it as sokoban level.
   */
  virtual const Map* readData(const std::string data) = 0;

  /*
   * Reads a file and interprets it as sokoban level.
   */
  virtual const Map* readFile(const std::string path);
};

}  // namespace Sokoban

#endif  // PROJEKT_PARSER_PARSER_H_
