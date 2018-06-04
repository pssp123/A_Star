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
	map.setCell(map.getCurrent().x,map.getCurrent().y,START);
	map.setCell(map.getTarget().x,map.getTarget().y,TARGET);
}
int Generator::heuristic(int16_t x, int16_t y, Vec2i &target) {
	return static_cast<int>(std::sqrt(std::pow(target.x - x, 2) + std::pow(target.y- y, 2)));
}

Path Generator::getShortPath(const Map &map) {
	return PathAlgorithm::getShortPath(map);
}
