//
// Created by pierre on 18-5-2.
//
#include <map>
#include "Vec2.hpp"
#include "../config/config.hpp"
#include <memory>

#ifndef A_START_MAP_HPP
#define A_START_MAP_HPP
enum CellState{
	UNCLEANABLE = 0,
	CLEANABLE,
	OBSTACLE,
};
typedef std::pair<CellState,Vec2i> Cell;
class Map{
public:

	void setCell(int16_t x, int16_t y, CellState status);
	CellState getCell(int16_t x, int16_t y) const;
	void printMap(const Vec2i curr, const Vec2i target) const;
	void clearMap();
	CellState cleanMap_[MAP_SIZE][MAP_SIZE];
	int16_t x_min, x_max, y_min, y_max;
private:
};
#endif //A_START_MAP_HPP
