//#include <gtest/gtest.h>
#include <Map.hpp>

//
// Created by pierre on 18-5-3.
//
/*class MapTest : public testing::Test{
public:
	virtual void SetUp(){
		map.setCell(2,1,CLEANABLE);
		map.setCell(-2,1,CLEANABLE);
		map.setCell(99,1,CLEANABLE);
		map.setCell(-99,1,CLEANABLE);
	}
	Map map;
private:
};

TEST_F(MapTest,setCellTest){
	EXPECT_EQ(1,map.cleanMap_[102][99]);
	EXPECT_EQ(1,map.cleanMap_[98][99]);
	EXPECT_EQ(1,map.cleanMap_[199][99]);
	EXPECT_EQ(1,map.cleanMap_[1][99]);
}
TEST_F(MapTest,getCellTest){
	EXPECT_EQ(1,map.getCell(2,1));
	EXPECT_EQ(1,map.getCell(-2,1));
	EXPECT_EQ(1,map.getCell(99,1));
	EXPECT_EQ(1,map.getCell(-99,1));
}
TEST_F(MapTest,clearTest){
	map.clearMap();
	for(auto j = map.xMin_; j <= map.xMax_; j++){
		for(auto k = map.yMin_; k <= map.yMax_; k++){
			EXPECT_EQ(0,map.getCell(j,k));
		}
	}
}*/
