// Copyright Tobias Faller 2016

#include "BasicParser.h"

#include <string>

using Sokoban::SokobanParser::Tokens;
using Sokoban::SokobanParser::Error;

namespace Sokoban {

BasicParser::BasicParser() { }
BasicParser::~BasicParser() { }

uint32_t BasicParser::tokenizeData(const std::string& data, uint32_t* line) {
  ssize_t nextTerminator;
  uint32_t index = 0;

  while (true) {
    nextTerminator = getNextTerminator(data, index);
    if ((nextTerminator < 0) || (nextTerminator < index)) {
      break;
    }

    if (nextTerminator - index <= 1) {
      index = nextTerminator + 1;
      continue;
    }

    readLine(data.substr(index, nextTerminator - index), *line);
    (*line)++;

    index = nextTerminator + 1;
  }

  return index;
}

void BasicParser::addToken(char c, uint32_t x, uint32_t y) {
  switch (c) {
  case Tokens::Floor:
    break;
  case Tokens::Wall:
    _mapBuilder.addBlock(x, y);
    break;
  case Tokens::Box:
    _mapBuilder.addBox(x, y);
    break;
  case Tokens::BoxOnGoal:
    _mapBuilder.addBox(x, y);
    _mapBuilder.addTarget(x, y);
    break;
  case Tokens::Player:
    _mapBuilder.setPlayer(x, y);
    break;
  case Tokens::PlayerOnGoal:
    _mapBuilder.setPlayer(x, y);
    _mapBuilder.addTarget(x, y);
    break;
  case Tokens::Goal:
    _mapBuilder.addTarget(x, y);
    break;
  default:
    throw Error::InvalidChar;
  }
}

const Map* BasicParser::readData(std::string data) {
  _mapBuilder.reset();

  uint32_t line = 0;
  uint32_t index = tokenizeData(data, &line);
  if ((index + 1) < data.length())
    readLine(data.substr(index), line);

  return _mapBuilder.build().second;
}

const Map* BasicParser::readStream(FILE* stream) {
  _mapBuilder.reset();

  char* buffer = nullptr;
  uint64_t bufferLength = 0;

  std::string data;

  int32_t lineLength;
  uint32_t index = 0;
  uint32_t line = 0;
  while ((lineLength = getline(&buffer, &bufferLength, stream)) > 0) {
    data.append(buffer, buffer + lineLength);

    index = tokenizeData(data, &line);
    data = data.substr(index, data.size() - index);
  }

  if ((index + 1) < data.size())
    readLine(data.substr(index), line);


  if (buffer)
    free(buffer);  // Allocated using malloc

  return _mapBuilder.build().second;
}

const Map* BasicParser::readStream(std::istream* stream) {
  _mapBuilder.reset();

  std::string buffer;
  std::string data;

  uint32_t lineLength;
  uint32_t index = 0;
  uint32_t line = 0;
  for (;;) {
    std::getline(*stream, data);

    if (data.size() <= 0) {
      break;
    }
    buffer.append(data);

    index = tokenizeData(buffer, &line);
    buffer = buffer.substr(index, buffer.size() - index);
  }

  if ((index + 1) < buffer.length())
    readLine(buffer.substr(index), line);

  return _mapBuilder.build().second;
}

}  // namespace Sokoban
