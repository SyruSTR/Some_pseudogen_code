#include "mapObject.h"
#include "../../Map/map.h"

#include "gtest/gtest.h"

class MapCreateTest : public testing::Test {
  protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(MapCreateTest, CreateEmptyMap) {
  genetic_things::Map *map = new genetic_things::Map(1,1);
  EXPECT_NE(map, nullptr);
  delete map;
}

TEST_F(MapCreateTest, Incorrect_width) {
  genetic_things::Map *map = nullptr;
  try {
    map = new genetic_things::Map(-10,1);
  }
  catch (std::out_of_range const & err) {
    EXPECT_EQ(err.what(), std::string("width and height must be greater than 0"));
  }
  catch (...) {
    FAIL() << "Expected /'width and height must be greater than 0/'";
  }
  delete map;
}

TEST_F(MapCreateTest, Incorrect_height) {
  genetic_things::Map *map = nullptr;
  try {
    map = new genetic_things::Map(1,-1);
  }
  catch (std::out_of_range const & err) {
    EXPECT_EQ(err.what(), std::string("width and height must be greater than 0"));
  }
  catch (...) {
    FAIL() << "Expected /'width and height must be greater than 0/'";
  }
  delete map;
}

TEST_F(MapCreateTest, Incorrect_height_and_width) {
  genetic_things::Map *map = nullptr;
  try {
    map = new genetic_things::Map(-10,-2);
  }
  catch (std::out_of_range const & err) {
    EXPECT_EQ(err.what(), std::string("width and height must be greater than 0"));
  }
  catch (...) {
    FAIL() << "Expected /'width and height must be greater than 0/'";
  }
  delete map;
}

TEST_F(MapCreateTest, Create_3x3_map_with_borders) {
  genetic_things::Map *map = new genetic_things::Map(3,3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == 1 && j == 1) {
        EXPECT_EQ(map->getObject(i,j)->getType(), genetic_things::EMPTY);
      }else
        EXPECT_EQ(map->getObject(i,j)->getType(), genetic_things::WALL);
    }
  }
}