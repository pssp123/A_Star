#include <iostream>

//#include "gtest/gtest.h"

#include "Map.hpp"
#include "Generator.hpp"

int main(int argc, char* argv[]) {
//	 testing::InitGoogleTest(&argc, argv);
//	 RUN_ALL_TESTS();
	Map map(Vec2Set(0,0),Vec2Set(15,0));
	Generator::Instance()->generataMap(map);
	PathSet path = Generator::Instance()->getShortPath(map);
	map.printMap(path);
	return 0;
}