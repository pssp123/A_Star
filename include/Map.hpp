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
	Map(){};
	Map(const Vec2Set& _current, const Vec2Set& _target){
		current_ = _current;
		target_ = _target;
	}

	void setCell(int16_t x, int16_t y, CellState status);
	CellState getCell(const int16_t& x, const int16_t& y) const;
	void printMap(const Path& path) const;
	void clearMap();
	bool isNotAccessible(const Vec2Set &node)const;
	Vec2Set getCurrent() const{
		return current_;
	}
	Vec2Set getTarget() const{
		return target_;
	}

private:
	Vec2Set current_{};
	Vec2Set target_{};
	int16_t xMin_{};
	int16_t xMax_{};
	int16_t yMin_{};
	int16_t yMax_{};
	CellState cleanMap_[MAP_SIZE][MAP_SIZE]{};
};
#endif //A_START_MAP_HPP
