//
// Created by pierre on 18-6-4.
//

#include "PathAlgorithm.hpp"

#include <cfloat>
#include <algorithm>
#include <zconf.h>

RBT PathAlgorithm::getShortPath(const Map& map) {
	RBT closedSet, openSet;
	std::multimap<Node,Node> cameFrom;
	cameFrom.insert({map.getCurrent(),map.getCurrent()});
	int h = heuristic(map.getCurrent(), map.getTarget());
	openSet.insert(Node{map.getCurrent().x_, map.getCurrent().y_, h, 0, h});

	while (!openSet.isEmpty()) {
		auto current = openSet.getSmallestChild();
		if (current == map.getTarget())
			return reconstructPath(cameFrom,current,map);

		closedSet.insert(current);
		openSet.deleteSmallestChild();

		Node neighbors[8];
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
				openSet.insert(neibor);
			}
			int tentative_g_score = current.g_ + dist_between(current, neibor);
			if (tentative_g_score > neibor.g_)
				continue;
			auto it = openSet.find(neibor);
			it->g_ = tentative_g_score;
			it->f_ = it->g_ + it->h_;
		}
	}
	return RBT{};
}

RBT PathAlgorithm::reconstructPath(std::multimap<Node,Node>& cameFrom, Node current, const Map& map){
	RBT path{};
	auto fun_any_of = [&](const std::multimap<Node,Node>::value_type& it){
		return it.first == current;
	};
	while(std::any_of(cameFrom.begin(),cameFrom.end(),fun_any_of) && !(current == map.getCurrent())){
		auto it = std::find_if(cameFrom.begin(),cameFrom.end(),fun_any_of);
		path.insert(it->first);
		current = it->second;
	}
	return path;
}

void PathAlgorithm::getNeighbors(Node& current, const Map& map, Node neighbors[]) {
	for(int i = 0; i < 8; i++)
		neighbors[i] = current + deviation[i];
}

int PathAlgorithm::dist_between(const Node x, const Node &y){
	return abs(x.x_ + x.y_ - y.x_ - y.y_) == 1 ? 10 : 14;
}

int PathAlgorithm::calculateG(const Node &start,const Node& node) {
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

int PathAlgorithm::heuristic(const Node& start, const Node& target){
	return 15 * (abs(start.x_ - target.x_) + abs(start.y_ - target.y_));
}
