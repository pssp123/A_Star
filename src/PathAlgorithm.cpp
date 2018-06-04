//
// Created by pierre on 18-6-4.
//

#include "PathAlgorithm.hpp"

#include <algorithm>
#include <Generator.hpp>


Path PathAlgorithm::getShortPath(const Map& map) {
	PathSet closedSet;
	PathSet openSet;
	int h = Generator::Instance()->heuristic(map.getCurrent(),map.getTarget());
	openSet.emplace_back(map.getCurrent().x_,map.getCurrent().y_,h,0,h);

	while(!openSet.empty()){
		auto current = std::max_element(openSet.begin(),openSet.end());
		if(*current == map.getTarget())
			return reconstructPath(*current);
	}
}

//todo
Path PathAlgorithm::reconstructPath(const Vec2Set& current){

}
