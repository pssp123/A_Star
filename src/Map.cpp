//
// Created by pierre on 18-5-3.
//
#include <Map.hpp>
#include "gtest/gtest.h"
using namespace std;
void Map::setCell(int16_t x, int16_t y, CellState status) {
	if(x < x_min)
		x_min = x;
	else if(x > x_max)
		x_max = x;
	if(y < y_min)
		y_min = y;
	else if(y > y_max)
		y_max = y;

	int16_t row = static_cast<int16_t>(MAP_SIZE / 2 + x);
	int16_t column = static_cast<int16_t>(MAP_SIZE / 2 - y);
	if(row > 0 && row < MAP_SIZE && column > 0 && column < MAP_SIZE)
		cleanMap_[row][column] = status;
	else
		printf("%s,%d,setCell out of boundary",__FUNCTION__,__LINE__);
}

CellState Map::getCell(int16_t x, int16_t y) const{
	CellState  status;
	int16_t row = static_cast<int16_t>(MAP_SIZE / 2 + x);
	int16_t column = static_cast<int16_t>(MAP_SIZE / 2 - y);
	if(row > 0 && row < MAP_SIZE && column > 0 && column < MAP_SIZE)
		status = cleanMap_[row][column];
	else
		printf("%s,%d,getCell out of boundary",__FUNCTION__,__LINE__);
	return status;
}

void Map::printMap(const Vec2i curr, const Vec2i target) const {
	ostringstream outString;
	outString.str("");
	outString << '\t' << '\t';
	for (auto i = x_min; i <= x_max; i++) {
		if (abs(i) % 10 == 0) {
			outString << std::abs(i/10);
		} else {
			outString << ' ';
		}
	}
	printf("%s\n",outString.str().c_str());

	outString.str("");
	outString << '\t' << '\t';
	for (auto i = x_min; i <= x_max; i++) {
		outString << abs(i) % 10;
	}
	printf("%s\n",outString.str().c_str());

	outString.str("");
	for (auto j = y_max; j >= y_min; j--) {
		outString.width(4);
		outString << j;
		outString << '\t';
		for (auto k = x_min; k <= x_max; k++) {
			auto status = getCell(j, k);
			if (k == curr.x && j == curr.y)
				outString << 'x';
			else if (k == target.x && j == target.y)
				outString << 'e';
			else
				outString << status;
		}
		printf("%s\n",outString.str().c_str());
		outString.str("");
	}
}
