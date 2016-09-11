// Copyright Tobias Faller 2016

#include "MapBuilder.h"

#include <gtest/gtest.h>

#include <utility>

using Sokoban::SokobanBuilder::Error;

namespace Sokoban {

TEST(MapBuilder, EmptyMap) {
  MapBuilder* builder = new MapBuilder();
  auto result = builder->build();

  ASSERT_EQ(result.first, Error::Success);
  ASSERT_NE(nullptr, result.second);
  auto map = result.second;

  // Player must at least have one space to "move"
  ASSERT_GE(map->getWidth(), 1);
  ASSERT_GE(map->getHeight(), 1);

  ASSERT_TRUE(map->getMap()->isEmpty(0, 0));
}

TEST(MapBuilder, Reset) {
  MapBuilder* builder = new MapBuilder();
  builder
    ->addBox(1, 2)
    ->addTarget(1, 3)
    ->addBlock(2, 2)
    ->addBlock(3, 2)
    ->setPlayer(1, 1);

  auto result = builder->reset()->build();

  ASSERT_EQ(result.first, Error::Success);
  ASSERT_NE(nullptr, result.second);
  auto map = result.second;

  // Player must at least have one space to "move"
  ASSERT_GE(map->getWidth(), 1);
  ASSERT_GE(map->getHeight(), 1);

  ASSERT_TRUE(map->getMap()->isEmpty(0, 0));
}

TEST(MapBuilder, Build) {
  MapBuilder* builder = new MapBuilder();
  builder
    ->addBox(2, 1)
    ->addTarget(3, 1)
    ->addBlocks(1, 0, 3, 0)
    ->addBlocks(1, 2, 3, 2)
    ->addBlock(0, 1)
    ->addBlock(4, 1)
    ->setPlayer(1, 1);

  auto result = builder->build();

  ASSERT_EQ(result.first, Error::Success);
  ASSERT_NE(nullptr, result.second);

  auto map = result.second;
  auto staticMap = map->getMap();

  // Player must at least have one space to "move"
  ASSERT_GE(map->getWidth(), 5);
  ASSERT_GE(map->getHeight(), 3);

  ASSERT_TRUE(staticMap->isEmpty(0, 0));
  ASSERT_TRUE(staticMap->isEmpty(4, 0));
  ASSERT_TRUE(staticMap->isEmpty(0, 2));
  ASSERT_TRUE(staticMap->isEmpty(4, 2));

  ASSERT_TRUE(staticMap->isBlock(1, 0));
  ASSERT_TRUE(staticMap->isBlock(2, 0));
  ASSERT_TRUE(staticMap->isBlock(3, 0));
  ASSERT_TRUE(staticMap->isBlock(1, 2));
  ASSERT_TRUE(staticMap->isBlock(2, 2));
  ASSERT_TRUE(staticMap->isBlock(3, 2));
  ASSERT_TRUE(staticMap->isBlock(0, 1));
  ASSERT_TRUE(staticMap->isBlock(4, 1));
}

}  // namespace Sokoban
