//
// Created by pierre on 18-6-4.
//

#ifndef A_START_PATHALGORITHM_HPP
#define A_START_PATHALGORITHM_HPP


#include "Vec2.hpp"
#include "Map.hpp"

class PathAlgorithm {
public:
	PathSet getShortPath(const Map& map);
	PathSet reconstructPath(std::multimap<Vec2Set,Vec2Set>& cameFrom,Vec2Set current,const Map& map);
	void getNeighbors(Vec2Set& current, const Map& map, Vec2Set neighbors[]);
	int dist_between(const Vec2Set& x, const Vec2Set& y);
	int calculateG(const Vec2Set& start,const Vec2Set& node);
	int heuristic(const Vec2Set& start, const Vec2Set& target);
private:
	Vec2Set deviation[8] = {Vec2Set{-1,1}, Vec2Set{0,1},   Vec2Set{1,1},
																				 Vec2Set{-1,0},                 Vec2Set{1,0},
																				 Vec2Set{-1,-1}, Vec2Set{0,-1}, Vec2Set{1,-1}};
};


#endif //A_START_PATHALGORITHM_HPP
