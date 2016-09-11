// Copyright Tobias Faller 2016

#include "RLEParser.h"

#include <string>
#include <cmath>
#include <algorithm>

using Sokoban::SokobanParser::Tokens;

namespace Sokoban {

char getNormalToken(char c);

RLEParser::RLEParser() { }
RLEParser::~RLEParser() { }

ssize_t RLEParser::getNextTerminator(const std::string& data,
    uint32_t offset) {

  uint32_t size = data.size();
  if (offset >= size)
    return -1;

  for (uint32_t index = offset; index < size; index++) {
    switch (data[index]) {
    case '|':
      return index;
    default:
      break;
    }
  }

  return -1;
}

uint32_t RLEParser::readLine(std::string line, uint32_t lineNumber) {
  uint32_t size = line.length();
  uint32_t tokenIndex = 0;
  uint32_t number = 0;
  uint32_t numberIndex = 0;

  for (uint32_t index = 0; index < size; index++) {
    char c = line[index];

    switch (c) {
    case '\r':
    case '\n':
      number = 0;
      numberIndex = 0;
      break;

    case '|':
      tokenIndex = 0;
      break;

    case '0':
      numberIndex++;
      break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      number += ((c + 1) - '1') * static_cast<uint32_t>(std::pow(10.0,
          static_cast<double>(numberIndex)));
      numberIndex++;
      break;

    default:
      uint32_t count = std::max(1, static_cast<int32_t>(number));

      for (uint32_t tIndex = 0; tIndex < count; tIndex++) {
        addToken(getNormalToken(c), tokenIndex, lineNumber);
        tokenIndex++;
      }
      break;
    }
  }

  return 0;
}

char getNormalToken(char c) {
  switch (c) {
  case '-':
  case '_':
    return Tokens::Floor;
  default:
    return c;
  }
}

}  // namespace Sokoban
