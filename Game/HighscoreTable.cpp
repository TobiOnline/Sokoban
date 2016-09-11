// Copyright Tobias Faller 2016

#include "HighscoreTable.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

#include "HighscoreEntry.h"

namespace Sokoban {

HighscoreTable::HighscoreTable() : _entries() { }
HighscoreTable::HighscoreTable(const HighscoreTable& table) : _entries() {
  for (const HighscoreEntry& entry : table._entries) {
    _entries.push_back(HighscoreEntry(entry));
  }
}
HighscoreTable::~HighscoreTable() { }

bool HighscoreTable::load(std::string file) {
  _entries.clear();

  std::ifstream in;
  in.open(file, std::iostream::binary | std::iostream::in);

  while (in.good() && !in.eof()) {
    HighscoreEntry entry;

    in.read(reinterpret_cast<char*>(&entry.steps),
        sizeof(uint32_t) / sizeof(char));
    if (in.eof()) {
      in.close();
      return false;
    }

    in.read(reinterpret_cast<char*>(&entry.time),
        sizeof(double) / sizeof(char));
    if (in.eof()) {
      in.close();
      return false;
    }

    uint16_t nameSize;
    in.read(reinterpret_cast<char*>(&nameSize),
        sizeof(uint16_t) / sizeof(char));
    if (in.eof()) {
      in.close();
      return false;
    }

    char* buffer = new char[nameSize + 1];
    memset(buffer, 0, nameSize + 1);

    in.read(buffer, nameSize);
    if (in.eof()) {
      in.close();
      return false;
    }

    entry.name = std::string(buffer);
    delete[] buffer;

    _entries.push_back(std::move(entry));
  }

  in.close();
  return true;
}
bool HighscoreTable::save(std::string file) const {
  std::ofstream out;
  out.open(file, std::iostream::binary | std::iostream::out
      | std::iostream::ate);

  if (!out.good())
    return false;

  for (const HighscoreEntry entry : _entries) {
    out.write(reinterpret_cast<const char*>(&entry.steps),
        sizeof(uint32_t) / sizeof(char));
    out.write(reinterpret_cast<const char*>(&entry.time),
        sizeof(double) / sizeof(char));

    uint16_t nameSize = entry.name.length();
    out.write(reinterpret_cast<char*>(&nameSize),
        sizeof(uint16_t) / sizeof(char));

    out.write(entry.name.c_str(), nameSize);
  }

  out.flush();
  out.close();
  return true;
}

const std::vector<HighscoreEntry>* HighscoreTable::getHighscoreList() const {
  return &_entries;
}

void HighscoreTable::add(const HighscoreEntry entry) {
  _entries.push_back(entry);
  std::sort(_entries.begin(), _entries.end(), [](const HighscoreEntry& a,
      const HighscoreEntry& b) {
    return a.steps < b.steps;
  });

  while (_entries.size() > SokobanHighscore::MAX_HIGHSCORE_SIZE) {
    _entries.pop_back();
  }
}

void HighscoreTable::clear() {
  _entries.clear();
}

}  // namespace Sokoban
