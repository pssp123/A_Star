//
// Created by pierre on 18-5-3.
//
#include <cstdint>
#include <cmath>
#include "Vec2.hpp"
#include "Generator.hpp"
#include "PathAlgorithm.hpp"

void Generator::generataMap(Map& map) {
	//set boundary
	for(int16_t i = -10; i < 10; i++)
		map.setCell(-10,i,OBSTACLE);
	for(int16_t i = -10; i < 10; i++)
		map.setCell(10,i,OBSTACLE);
	for(int16_t i = -10; i < 10; i++)
		map.setCell(i,-10,OBSTACLE);
	for(int16_t i = -10; i < 10; i++)
		map.setCell(i,10,OBSTACLE);

	//set wall
	for(int16_t i = -4; i < 4; i++)
		map.setCell(5,i,OBSTACLE);

	//set current and target
	map.setCell(map.getCurrent().x_,map.getCurrent().y_,START);
	map.setCell(map.getTarget().x_,map.getTarget().y_,TARGET);
}


Path Generator::getShortPath(const Map &map) {
	return PathAlgorithm::getShortPath(map);
}
