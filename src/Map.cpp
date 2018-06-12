//
// Created by pierre on 18-5-3.
//
#include <Map.hpp>

#include "gtest/gtest.h"
using namespace std;
void Map::setCell(int16_t x, int16_t y, CellState status) {
	if(x < xMin_)
		xMin_ = x;
	else if(x > xMax_)
		xMax_ = x;
	if(y < yMin_)
		yMin_ = y;
	else if(y > yMax_)
		yMax_ = y;

	int16_t row = static_cast<int16_t>(MAP_SIZE / 2 + x);
	int16_t column = static_cast<int16_t>(MAP_SIZE / 2 - y);
	if(row > 0 && row < MAP_SIZE && column > 0 && column < MAP_SIZE)
		cleanMap_[row][column] = status;
	else
		printf("%s,%d,setCell out of boundary",__FUNCTION__,__LINE__);
}

CellState Map::getCell(const int16_t& x, const int16_t& y) const{
	CellState  status;
	auto row = static_cast<int16_t>(MAP_SIZE / 2 + x);
	auto column = static_cast<int16_t>(MAP_SIZE / 2 - y);
	if(row > 0 && row < MAP_SIZE && column > 0 && column < MAP_SIZE)
		status = cleanMap_[row][column];
	else
		printf("%s,%d,getCell out of boundary",__FUNCTION__,__LINE__);
	return status;
}

void Map::printMap(const PathSet& path) const {
	ostringstream outString;
	outString.str("");
	outString << '\t' << '\t';
	for (auto i = xMin_; i <= xMax_; i++) {
		if ((int)abs(i) % 10 == 0) {
			outString << std::abs(i/10);
		} else {
			outString << ' ';
		}
	}
	printf("%s\n",outString.str().c_str());

	outString.str("");
	outString << '\t' << '\t';
	for (auto i = xMin_; i <= xMax_; i++) {
		outString << (int)abs(i) % 10;
	}
	printf("%s\n",outString.str().c_str());

	outString.str("");
	for (auto j = yMax_; j >= yMin_; j--) {
		outString.width(4);
		outString << j;
		outString << '\t';
		for (auto k = xMin_; k <= xMax_; k++) {
			auto status = getCell(k, j);
			if (status == START)
				outString << 'x';
			else if (status == TARGET)
				outString << 'e';
			else if(std::any_of(path.begin(),path.end(),[&](const Vec2Set& node){return node.x_ == k && node.y_ == j;})){
				outString << '>';
			}
			else
				outString << status;
		}
		printf("%s\n",outString.str().c_str());
		outString.str("");
	}
}

void Map::clearMap() {
	memset(cleanMap_,0,sizeof(cleanMap_));
}

bool Map::isNotAccessible(const Vec2Set &node)const {
	CellState status = getCell(node.x_, node.y_);
	return status == OBSTACLE;
}
