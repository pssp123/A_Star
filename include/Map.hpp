//
// Created by pierre on 18-5-2.
//
#include <memory>
#include <map>
#include "Vec2.hpp"
#include "../config/config.hpp"

#ifndef A_START_MAP_HPP
#define A_START_MAP_HPP
enum CellState{
	UNCLEANABLE = 0,
	START,
	TARGET,
	CLEANABLE,
	OBSTACLE,
};
typedef std::pair<CellState,Vec2i> Cell;
class Map{
public:
	Map(const Vec2i& _current, const Vec2i& _target){
		current_ = _current;
		target_ = _target;
	}

	void setCell(int16_t x, int16_t y, CellState status);
	CellState getCell(int16_t x, int16_t y) const;
	void printMap() const;
	void clearMap();
	Vec2i getCurrent() const{
		return current_;
	}
	Vec2i getTarget() const{
		return target_;
	}

private:
	Vec2i current_{};
	Vec2i target_{};
	int16_t xMin_{};
	int16_t xMax_{};
	int16_t yMin_{};
	int16_t yMax_{};
	CellState cleanMap_[MAP_SIZE][MAP_SIZE];
};
#endif //A_START_MAP_HPP
