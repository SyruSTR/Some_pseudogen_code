#include "../../Map/map.h"

#include "gtest/gtest.h"

class MapCreateTest : public testing::Test {
  protected:
  genetic_things::Map* map;

    virtual void SetUp() {
      map = new genetic_things::Map(50,10);
    }

    virtual void TearDown() {
      delete map;
    }
};

TEST_F(MapCreateTest, CreateMap) {

}