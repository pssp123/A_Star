#include <iostream>

//#include "gtest/gtest.h"

#include "Map.hpp"
#include "Generator.hpp"
#include "PathAlgorithm.hpp"

int main(int argc, char* argv[]) {
//	 testing::InitGoogleTest(&argc, argv);
//	 RUN_ALL_TESTS();
	Map map(Vec2i(0,0),Vec2i(15,0));
	Generator::Instance()->generataMap(map);
	Path path = Generator::Instance()->getShortPath(map);
//	for(auto ite = path.rbegin(); ite != path.rend(); ite++)
//		printf("p:(%d,%d)\n",ite->x_, ite->y_);
	map.printMap(path);
	return 0;
}