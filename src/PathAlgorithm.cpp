//
// Created by pierre on 18-6-4.
//

#include "Map.hpp"
#include "Vec2.hpp"
#include "PathAlgorithm.hpp"
Path PathAlgorithm::getShortPath(const Map& map) {
	Path closedSet;
	Path openSet;
	openSet.push_back(map.getCurrent());
}
