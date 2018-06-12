//
// Created by pierre on 18-6-4.
//

#include "PathAlgorithm.hpp"

#include <algorithm>
#include <Generator.hpp>
#include <cfloat>
#include <map>
#include <zconf.h>

Path PathAlgorithm::getShortPath(const Map& map) {
	PathSet closedSet;
	PathSet openSet;
	std::multimap<Vec2Set,Vec2Set> cameFrom;
	cameFrom.insert({map.getCurrent(),map.getCurrent()});
	int h = heuristic(map.getCurrent(), map.getTarget());
	openSet.push_back(Vec2Set{map.getCurrent().x_, map.getCurrent().y_, h, 0, h});

	while (!openSet.empty()) {
		auto current = findTheBestF(openSet);
		if (current == map.getTarget())
			return reconstructPath(cameFrom,current,map);
		closedSet.push_back(current);
		openSet.erase(std::find_if(openSet.begin(),openSet.end(),[&](const Vec2Set& node){
			return node == current;
		}));
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
			auto func = std::find_if(openSet.begin(),openSet.end(),[&](Vec2Set node){
				return node == neibor;
			});
			//todo
			func->g_ = tentative_g_score;
			func->h_ = heuristic(neibor, map.getTarget());
			func->f_ = func->g_ + func->h_;
//			for(const auto& it : openSet)
//				printf("it(%d,%d), father(%d,%d), f(%lf), g(%d), h(%lf)\n",it.x_,it.y_,current.x_,current.y_,it.f_,it.g_,it.h_);
//			printf("\n");
		}
	}
	return Path{};
}

Path PathAlgorithm::reconstructPath(std::multimap<Vec2Set,Vec2Set>& cameFrom, Vec2Set current, const Map& map){
	Path path{};
//	printf("Start: size(%d) current(%d,%d)\n", static_cast<int>(cameFrom.size()),current.x_,current.y_);
	auto fun_any_of = [&](const std::multimap<Vec2Set,Vec2Set>::value_type& it){
		return it.first == current;
	};
	while(std::any_of(cameFrom.begin(),cameFrom.end(),fun_any_of) && !(current == map.getCurrent())){
		auto it = std::find_if(cameFrom.begin(),cameFrom.end(),fun_any_of);
		path.push_back(it->first);
//		printf("(%d,%d)\n",it->second.x_,it->second.y_);
		current = it->second;
	}
//	for(const auto& p : cameFrom)
//		printf("(%d,%d)\n",p.first.x_,p.first.y_);
//	for(const auto& p : path)
//		printf("(%d,%d)\n",p.x_,p.y_);
	return path;
}

void PathAlgorithm::getNeighbors(Vec2Set& current, const Map& map, Vec2Set neighbors[]) {
	for(int i = 0; i < 8; i++)
		neighbors[i] = current + deviation[i];
}

int PathAlgorithm::dist_between(const Vec2Set &x, const Vec2Set &y){
	return abs(x.x_ + x.y_ - y.x_ - y.y_) == 1 ? 10 : 14;
}

Vec2Set PathAlgorithm::findTheBestF(PathSet &path) {
/*	for(const auto& p : path){
		if (p.p_cameFrom_ != nullptr)
			printf("findTheBest:(%d,%d) (%d,%d)\n", p.x_, p.y_, p.p_cameFrom_->x_, p.p_cameFrom_->y_);
	}*/
	double score = DBL_MAX;
	Vec2Set ret;
	for(auto& p : path){
//		if (p.p_cameFrom_ != nullptr)
//			printf("22222findTheBest:(%d,%d) (%d,%d)\n", p.x_, p.y_, p.p_cameFrom_->x_, p.p_cameFrom_->y_);
		if(p.f_ < score){
			score = p.f_;
			ret = p;
		}
//		if (p.p_cameFrom_ != nullptr)
//			printf("22222findTheBest:(%d,%d) (%d,%d)\n\n", p.x_, p.y_, p.p_cameFrom_->x_, p.p_cameFrom_->y_);
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
	return 15 * (abs(start.x_ - target.x_) + abs(start.y_ - target.y_));
}
