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
};


#endif //A_START_PATHALGORITHM_HPP
