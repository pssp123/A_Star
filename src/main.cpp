#include <iostream>
#include "gtest/gtest.h"
#include "Map.hpp"
#include "Generator.hpp"

int main(int argc, char* argv[]) {
//	 testing::InitGoogleTest(&argc, argv);
//	 RUN_ALL_TESTS();
	Map map(Vec2i(0,0),Vec2i(8,8));
	Generator::Instance()->generataMap(map);
	Path path = Generator::Instance()->getShortPath(map);
	return 0;
}