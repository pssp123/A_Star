//
// Created by pierre on 18-6-4.
//

#ifndef A_START_PATHALGORITHM_HPP
#define A_START_PATHALGORITHM_HPP


#include "Vec2.hpp"
#include "Map.hpp"

class PathAlgorithm {
public:
	static Path getShortPath(const Map& map);
	static Path reconstructPath(const Vec2Set& current);
	static void getNeighbors(const Vec2Set& current,Vec2Set neighbors[]);
	static std::list<Vec2Set>::iterator findTheBestF(PathSet& path);
	static int dist_between(const Vec2Set& x, const Vec2Set& y);
	static int calculateG(const Vec2i& start,const Vec2Set& node);
private:
	static Vec2Set deviation[8];
};


#endif //A_START_PATHALGORITHM_HPP
