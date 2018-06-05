//
// Created by pierre on 18-6-4.
//

#include "PathAlgorithm.hpp"

#include <algorithm>
#include <Generator.hpp>
#include <cfloat>
#include <zconf.h>

Path  PathAlgorithm::path{};
Vec2Set PathAlgorithm::deviation[8] = {Vec2Set{-1,1}, Vec2Set{0,1},   Vec2Set{1,1},
																			 Vec2Set{-1,0},                 Vec2Set{1,0},
																			 Vec2Set{-1,-1}, Vec2Set{0,-1}, Vec2Set{1,-1}};
Path PathAlgorithm::getShortPath(const Map& map) {
	bool tentative_is_better{false};
	PathSet closedSet;
	PathSet openSet;
	int h = heuristic(map.getCurrent(), map.getTarget());
	printf("h:%d\n",h);
	openSet.push_back(Vec2Set{map.getCurrent().x_, map.getCurrent().y_, h, 0, h});

	while (!openSet.empty()) {
		auto current = findTheBestF(openSet);
		printf("x:%d,y:%d\n",current.x_,current.y_);
		if (current == map.getTarget())
			return reconstructPath(current);
		closedSet.push_back(current);
		openSet.erase(std::find_if(openSet.begin(),openSet.end(),[&](const Vec2Set& node){
			return node == current;
		}));
		Vec2Set neighbors[8];
		getNeighbors(current, map,neighbors);

		for (auto &neibor : neighbors) {
			if (closedSet.isContain(neibor))
				continue;
			double tentative_g_score = current.g_ + dist_between(current,neibor);
			if(!openSet.isContain(neibor)) {
//				openSet.push_back(neibor);
				tentative_is_better = true;
			}else if(neibor.g_ < tentative_g_score){
				tentative_is_better = true;
			}else{
				tentative_is_better = false;
			}

			if(tentative_is_better){
				neibor.p_cameFrom_ = &current;
				neibor.g_ = tentative_g_score;
				neibor.h_ = heuristic(neibor,map.getTarget());
				neibor.f_ = neibor.g_ + neibor.h_;
				openSet.push_back(neibor);
//				printf("neibor.x:%d, neibor.y:%d, f:%lf, g:%d, h:%lf\n",neibor.x_,neibor.y_,neibor.f_,neibor.g_,neibor.h_);
			}
		}
		for(const auto& p : openSet)
			printf("openSet.x:%d,openset.y:%d, f:%lf, g:%d, h:%lf\n,",p.x_,p.y_,p.f_,p.g_,p.h_);
		usleep(1000000);
	}
	return Path{};
}

Path PathAlgorithm::reconstructPath(const Vec2Set& current){
	printf("3333\n");
	path.push_back(current);
	if(current.p_cameFrom_ != nullptr)
		reconstructPath(*current.p_cameFrom_);
	else
		return path;
}

void PathAlgorithm::getNeighbors(const Vec2Set& current, const Map& map, Vec2Set neighbors[]) {
	for(int i = 0; i < 8; i++)
	{
		neighbors[i] = current + deviation[i];
		neighbors[i].g_ = calculateG(map.getCurrent(),neighbors[i]);
	}
}

int PathAlgorithm::dist_between(const Vec2Set &x, const Vec2Set &y){
	return abs(x.x_ + x.y_ - y.x_ - y.y_) == 1 ? 10 : 14;
}

Vec2Set PathAlgorithm::findTheBestF(PathSet &path) {
	double score = DBL_MAX;
//	std::list<Vec2Set>::iterator ret;
	Vec2Set ret;
	for(const Vec2Set& p : path){
		if(p.f_ < score){
			score = p.f_;
			ret = p;
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
		dis += abs(delt_x - delt_y) * 10;
	}
	return dis;
}

int PathAlgorithm::heuristic(const Vec2i& start, const Vec2i& target){
	return static_cast<int>(std::sqrt(std::pow(target.x_ - start.x_, 2) + std::pow(target.y_- start.y_, 2)));
}
