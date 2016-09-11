// Copyright Tobias Faller

#ifndef PROJEKT_PARSER_RLEPARSER_H_
#define PROJEKT_PARSER_RLEPARSER_H_

#include <string>

#include "BasicParser.h"
#include "Parser.h"

namespace Sokoban {

/*
 * Implements a sokoban level parser with RLE format.
 */
class RLEParser : public BasicParser {
 protected:
  /*
   * Parses a line of data and appends it to the MapBuilder.
   */
  uint32_t readLine(std::string line, uint32_t lineNumber) override;

  /*
   * Returns the next vertical separator for this stream.
   */
  ssize_t getNextTerminator(const std::string& data, uint32_t offset) override;

 public:
  /*
   * Creates a new parser for the normal line-seperated sokoban level format.
   */
  RLEParser();

  /*
   * Destroys this parser.
   */
  virtual ~RLEParser();
};

}  // namespace Sokoban

#endif  // PROJEKT_PARSER_RLEPARSER_H_
