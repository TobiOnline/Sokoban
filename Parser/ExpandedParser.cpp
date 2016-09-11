// Copyright Tobias Faller 2016

#include "ExpandedParser.h"

#include <string>

namespace Sokoban {

ExpandedParser::ExpandedParser() { }
ExpandedParser::~ExpandedParser() { }

ssize_t ExpandedParser::getNextTerminator(const std::string& data,
    uint32_t offset) {

  uint32_t size = data.size();
  if (offset >= size)
    return -1;

  bool lineEnd = false;
  for (uint32_t index = offset; index < size; index++) {
    switch (data[index]) {
    case '\r':
      lineEnd = true;
      break;
    case '\n':
      return index - (lineEnd ? 1 : 0);
    default:
      break;
    }
  }

  return -1;
}

uint32_t ExpandedParser::readLine(std::string line, uint32_t lineNumber) {
  uint32_t size = line.length();

  for (uint32_t index = 0; index < size; index++) {
    char c = line[index];
    switch (c) {
    case '\r':
    case '\n':
      break;
    default:
      addToken(c, index, lineNumber);
      break;
    }
  }

  return 0;
}

}  // namespace Sokoban
