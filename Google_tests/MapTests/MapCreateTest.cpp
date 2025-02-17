#include "../../Map/map.h"

#include "gtest/gtest.h"

class MapCreateTest : public testing::Test {
  protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(MapCreateTest, CreateMap) {
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