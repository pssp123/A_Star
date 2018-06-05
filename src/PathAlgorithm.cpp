//
// Created by pierre on 18-6-4.
//

#include "PathAlgorithm.hpp"

#include <algorithm>
#include <Generator.hpp>


Vec2Set PathAlgorithm::deviation[8] = {Vec2Set{-1,1}, Vec2Set{0,1},   Vec2Set{1,1},
																			 Vec2Set{-1,0},                 Vec2Set{1,0},
																			 Vec2Set{-1,-1}, Vec2Set{0,-1}, Vec2Set{1,-1}};
Path PathAlgorithm::getShortPath(const Map& map) {
	bool tentative_is_better{false};
	PathSet closedSet;
	PathSet openSet;
	int h = Generator::Instance()->heuristic(map.getCurrent(), map.getTarget());
	openSet.push_back(Vec2Set{map.getCurrent().x_, map.getCurrent().y_, h, 0, h});

	while (!openSet.empty()) {
		auto current = findTheBestF(openSet);
		if (*current == map.getTarget())
			return reconstructPath(*current);
		closedSet.push_back(*current);
		openSet.erase(current);
		Vec2Set neighbors[8];
		getNeighbors(*current, neighbors);
		for (const auto &neibor : neighbors) {
			if (closedSet.isContain(neibor))
				continue;
			double tentative_g_score = current->g_ + dist_between(*current,neibor);
			if(!openSet.isContain(neibor)) {
				openSet.push_back(neibor);
				tentative_is_better = true;
			}
		}
	}
}


//todo
Path PathAlgorithm::reconstructPath(const Vec2Set& current){

}

void PathAlgorithm::getNeighbors(const Vec2Set& current,Vec2Set neighbors[]) {
	for(int i = 0; i < 8; i++)
	{
		neighbors[i] = current + deviation[i];
	}
}

int PathAlgorithm::dist_between(const Vec2Set &x, const Vec2Set &y){
	return abs(x.x_ + x.y_ - y.x_ - y.y_) == 1 ? 10 : 14;
}

std::list<Vec2Set>::iterator PathAlgorithm::findTheBestF(PathSet &path) {
	int score = 0;
	std::list<Vec2Set>::iterator ret;
	for(auto ite = path.begin(); ite != path.end(); ite++){
		if(score < ite->f_)
		{
			score = ite->f_;
			ret = ite;
		}
	}
	return ret;
}

int PathAlgorithm::calculateG(const Vec2i &start,const Vec2Set& node) {
	int dis = 0;
	auto delt_x = abs(start.x_ - node.x_);
	auto delt_y = abs(start.y_ - node.y_);
	if(delt_x == delt_y){
		dis = delt_x * 14;
	} else if(delt_x == 0){
		dis = delt_y * 10;
	}else if(delt_y == 0){
		dis = delt_x * 10;
	}else{
		dis = delt_x < delt_y ? delt_x * 14 : delt_y * 14;
		dis += abs(delt_x - delt_y) *10;
	}
	return dis;
}


