//
// Created by pierre on 18-6-4.
//

#include "PathAlgorithm.hpp"

#include <cfloat>

PathSet PathAlgorithm::getShortPath(const Map& map) {
	PathSet closedSet, openSet;
	std::multimap<Vec2Set,Vec2Set> cameFrom;
	cameFrom.insert({map.getCurrent(),map.getCurrent()});
	int h = heuristic(map.getCurrent(), map.getTarget());
	openSet.push_back(Vec2Set{map.getCurrent().x_, map.getCurrent().y_, h, 0, h});

	while (!openSet.empty()) {
		auto current = openSet.findTheBestF();
		if (current == map.getTarget())
			return reconstructPath(cameFrom,current,map);

		closedSet.push_back(current);
		openSet.erase(openSet.find(current));

		Vec2Set neighbors[8];
		getNeighbors(current, map,neighbors);

		for (auto &neibor : neighbors) {
			if (closedSet.isContain(neibor) || map.isNotAccessible(neibor))
				continue;
			if (!openSet.isContain(neibor))
			{
				neibor.g_ = calculateG(neibor,map.getCurrent());
				neibor.h_ = heuristic(neibor,map.getTarget());
				neibor.f_ = neibor.g_ + neibor.h_;
				cameFrom.insert({neibor,current});
				openSet.push_back(neibor);
			}
			int tentative_g_score = current.g_ + dist_between(current, neibor);
			if (tentative_g_score > neibor.g_)
				continue;
			auto it = openSet.find(neibor);
			it->g_ = tentative_g_score;
			it->f_ = it->g_ + it->h_;
		}
	}
	return PathSet{};
}

PathSet PathAlgorithm::reconstructPath(std::multimap<Vec2Set,Vec2Set>& cameFrom, Vec2Set current, const Map& map){
	PathSet path{};
	auto fun_any_of = [&](const std::multimap<Vec2Set,Vec2Set>::value_type& it){
		return it.first == current;
	};
	while(std::any_of(cameFrom.begin(),cameFrom.end(),fun_any_of) && !(current == map.getCurrent())){
		auto it = std::find_if(cameFrom.begin(),cameFrom.end(),fun_any_of);
		path.push_back(it->first);
		current = it->second;
	}
	return path;
}

void PathAlgorithm::getNeighbors(Vec2Set& current, const Map& map, Vec2Set neighbors[]) {
	for(int i = 0; i < 8; i++)
		neighbors[i] = current + deviation[i];
}

int PathAlgorithm::dist_between(const Vec2Set &x, const Vec2Set &y){
	return abs(x.x_ + x.y_ - y.x_ - y.y_) == 1 ? 10 : 14;
}

int PathAlgorithm::calculateG(const Vec2Set &start,const Vec2Set& node) {
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
		dis += abs(delt_x - delt_y) * 10;
	}
	return dis;
}

int PathAlgorithm::heuristic(const Vec2Set& start, const Vec2Set& target){
	return 15 * (abs(start.x_ - target.x_) + abs(start.y_ - target.y_));
}
