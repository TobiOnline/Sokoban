// Copyright Tobias Faller

#include "StaticMap.h"

#include <gtest/gtest.h>

namespace Sokoban {

TEST(StaticMap, GetSet) {
  StaticMap* map = new StaticMap(4, 4);
  ASSERT_EQ(4, map->getWidth());
  ASSERT_EQ(4, map->getHeight());

  for (uint32_t index = 0; index < 16; ++index) {
    ASSERT_EQ(StaticType::Nothing, map->get(index % 4, index / 4));
  }

  map->set(1, 2, StaticType::Block);
  ASSERT_EQ(StaticType::Block, map->get(1, 2));
  map->set(1, 2, StaticType::Nothing);
  ASSERT_EQ(StaticType::Nothing, map->get(1, 2));

  // Check for overwrite
  map->set(2, 2, StaticType::Target);
  ASSERT_EQ(StaticType::Target, map->get(2, 2));
  map->set(2, 2, StaticType::Block);
  ASSERT_EQ(StaticType::Block, map->get(2, 2));
  map->set(2, 2, StaticType::Nothing);
  ASSERT_EQ(StaticType::Nothing, map->get(2, 2));

  // Check for near fields
  ASSERT_EQ(StaticType::Nothing, map->get(1, 2));
  ASSERT_EQ(StaticType::Nothing, map->get(3, 2));

  delete map;
}


TEST(StaticMap, Types) {
  StaticMap* map = new StaticMap(5, 8);
  ASSERT_EQ(5, map->getWidth());
  ASSERT_EQ(8, map->getHeight());

  for (uint32_t index = 0; index < 5*8; index++) {
    ASSERT_EQ(StaticType::Nothing, map->get(index % 5, index / 5));
  }

  map->set(1, 0, StaticType::Nothing);
  ASSERT_TRUE(map->isEmpty(1, 0));
  ASSERT_FALSE(map->isBlock(1, 0));
  ASSERT_FALSE(map->isTarget(1, 0));

  map->set(2, 0, StaticType::Block);
  ASSERT_FALSE(map->isEmpty(2, 0));
  ASSERT_TRUE(map->isBlock(2, 0));
  ASSERT_FALSE(map->isTarget(2, 0));

  map->set(3, 0, StaticType::Target);
  ASSERT_FALSE(map->isEmpty(3, 0));
  ASSERT_FALSE(map->isBlock(3, 0));
  ASSERT_TRUE(map->isTarget(3, 0));

  delete map;
}

TEST(StaticMap, Size) {
  StaticMap* map = new StaticMap(42, 4);
  ASSERT_EQ(42, map->getWidth());
  ASSERT_EQ(4, map->getHeight());

  for (uint32_t index = 0; index < 42 * 4; index++) {
    ASSERT_EQ(StaticType::Nothing, map->get(index % 42, index / 42));
  }

  delete map;
}

}  // namespace Sokoban
