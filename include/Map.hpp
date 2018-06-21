//
// Created by pierre on 18-5-2.
//
#ifndef A_START_MAP_HPP
#define A_START_MAP_HPP

#include <memory>
#include <map>
#include "Vec2.hpp"
#include "../config/config.hpp"

enum CellState{
	UNCLEANABLE = 0,
	START,
	TARGET,
	CLEANABLE,
	OBSTACLE,
};
class Map{
public:
	Map(){};
	Map(const Node& _current, const Node& _target){
		current_ = _current;
		target_ = _target;
	}

	void setCell(int16_t x, int16_t y, CellState status);
	CellState getCell(const int16_t& x, const int16_t& y) const;
	void printMap(RBT& path) const;
	void clearMap();
	bool isNotAccessible(const Node &node)const;
	Node getCurrent() const{
		return current_;
	}
	Node getTarget() const{
		return target_;
	}

private:
	Node current_{};
	Node target_{};
	int16_t xMin_{};
	int16_t xMax_{};
	int16_t yMin_{};
	int16_t yMax_{};
	CellState cleanMap_[MAP_SIZE][MAP_SIZE]{};
};
#endif //A_START_MAP_HPP
