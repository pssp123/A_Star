//
// Created by pierre on 18-5-3.
//
#include <cstdint>
#include "Vec2.hpp"
#include "Generator.hpp"
#include "PathAlgorithm.hpp"

void Generator::generataMap(Map& map) {
	//set boundary
	for(int16_t i = -20; i < 20; i++)
		map.setCell(-20,i,OBSTACLE);
	for(int16_t i = -20; i < 20; i++)
		map.setCell(20,i,OBSTACLE);
	for(int16_t i = -20; i < 20; i++)
		map.setCell(i,-20,OBSTACLE);
	for(int16_t i = -20; i < 20; i++)
		map.setCell(i,20,OBSTACLE);
	//set wall
	for(int16_t i = -10; i <= 10; i++)
		map.setCell(10,i,OBSTACLE);
	for(int16_t i = -8; i <= 10; i++)
		map.setCell(-10,i,OBSTACLE);
	for(int16_t i = -10; i <= 10; i++)
		map.setCell(i,10,OBSTACLE);
	for(int16_t i = -10; i <= 10; i++)
		map.setCell(i,-10,OBSTACLE);

	//set current and target
	map.setCell(map.getCurrent().x_,map.getCurrent().y_,START);
	map.setCell(map.getTarget().x_,map.getTarget().y_,TARGET);
}


RBT Generator::getShortPath(const Map &map) {
	PathAlgorithm pathAlgorithm;
	return pathAlgorithm.getShortPath(map);
}
