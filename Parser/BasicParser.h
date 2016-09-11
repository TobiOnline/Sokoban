// Copyright Tobias Faller

#ifndef PROJEKT_PARSER_BASICPARSER_H_
#define PROJEKT_PARSER_BASICPARSER_H_

#include <string>

#include "../Map/MapBuilder.h"
#include "Parser.h"

namespace Sokoban {

namespace SokobanParser {

  enum Tokens : char {
    Wall = '#',
    Player = '@',
    PlayerOnGoal = '+',
    Box = '$',
    BoxOnGoal = '*',
    Goal = '.',
    Floor = ' '
  };

}  // namespace SokobanParser

/*
 * Defines a base class for the sokoban level parser.
 */
class BasicParser : public Parser {
 private:
  /*
   * Small subroutine for splitting a string into lines.
   * Returns the remaining chars in the buffer.
   */
  uint32_t tokenizeData(const std::string& data, uint32_t* line);

 protected:
  MapBuilder _mapBuilder;

  /*
   * Creates a new instance of this parser.
   */
  BasicParser();

  /*
   * Parses a line of data and appends it to the MapBuilder.
   */
  virtual uint32_t readLine(std::string line, uint32_t lineNumber) = 0;

  /*
   * Returns the next vertical separator for this stream.
   */
  virtual ssize_t getNextTerminator(const std::string& data, uint32_t offset)
      = 0;

  /*
   * Interprets the provided Token as object at position x, y and adds
   * it to the builder.
   */
  void addToken(char c, uint32_t x, uint32_t y);

 public:
  /*
   * Destroys this parser.
   */
  virtual ~BasicParser();

  /*
   * Reads a file stream and interprets it as sokoban level.
   */
  const Map* readStream(FILE* stream) override;

  /*
   * Reads a stream and interprets it as sokoban level.
   */
  const Map* readStream(std::istream* stream) override;

  /*
   * Reads some data and interprets it as sokoban level.
   */
  const Map* readData(const std::string data) override;
};

}  // namespace Sokoban

#endif  // PROJEKT_PARSER_BASICPARSER_H_
