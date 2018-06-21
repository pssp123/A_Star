#include <iostream>
#include <time.h>
#include <zconf.h>

//#include "gtest/gtest.h"

#include "Map.hpp"
#include "Generator.hpp"

int main(int argc, char* argv[]) {
//	 testing::InitGoogleTest(&argc, argv);
//	 RUN_ALL_TESTS();
	Map map(Node(0,0),Node(15,0));
	Generator::Instance()->generataMap(map);
	auto start_time  = clock();
	RBT path = Generator::Instance()->getShortPath(map);
	double delt_time = double(clock() - start_time) / CLOCKS_PER_SEC;
	printf("time:%lf\n",delt_time);
	map.printMap(path);
	return 0;
}