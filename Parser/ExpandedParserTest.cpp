// Copyright Tobias Faller 2016

#include "ExpandedParser.h"

#include <gtest/gtest.h>

#include "../Parser/ExpandedParser.h"

namespace Sokoban {

TEST(ExpandedParser, readFromString) {
  try {
    // Check if the override works
    Parser* parser = new ExpandedParser();
    const Map* map = parser->readData("###\r\n#@#\r\n#$#\r\n#.#\r\n###");
    const StaticMap* sMap = map->getMap();
    const State* state = map->getInitialState();

    // Check if no error
    ASSERT_TRUE(map);
    ASSERT_TRUE(sMap);
    ASSERT_TRUE(state);

    // Check for walls
    ASSERT_TRUE(sMap->isBlock(0, 0));
    ASSERT_TRUE(sMap->isBlock(1, 0));
    ASSERT_TRUE(sMap->isBlock(2, 0));
    ASSERT_TRUE(sMap->isBlock(0, 1));
    ASSERT_TRUE(sMap->isBlock(2, 1));
    ASSERT_TRUE(sMap->isBlock(0, 2));
    ASSERT_TRUE(sMap->isBlock(2, 2));
    ASSERT_TRUE(sMap->isBlock(0, 3));
    ASSERT_TRUE(sMap->isBlock(2, 3));
    ASSERT_TRUE(sMap->isBlock(0, 4));
    ASSERT_TRUE(sMap->isBlock(1, 4));
    ASSERT_TRUE(sMap->isBlock(2, 4));

    // Check for target
    ASSERT_TRUE(sMap->isTarget(1, 3));

    // Check for box
    const std::unordered_map<Coordinate, BoxState>* boxes = state->getBoxes();
    ASSERT_EQ(boxes->size(), 1);

    ASSERT_NE(boxes->find(Coordinate(1, 2)), boxes->end());

    // Check player position
    ASSERT_EQ(Coordinate(1, 1), state->getPlayerPosition());
  } catch (const Sokoban::SokobanParser::Error& exception) {
    FAIL() << "Sokoban::SokobanParser::Error: " << exception << std::endl;
  }
}

}  // namespace Sokoban
