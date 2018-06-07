//
// Created by pierre on 18-6-4.
//

#include "PathAlgorithm.hpp"

#include <algorithm>
#include <Generator.hpp>
#include <cfloat>
#include <zconf.h>

Path PathAlgorithm::getShortPath(const Map& map) {
	PathSet closedSet;
	PathSet openSet;
	int h = heuristic(map.getCurrent(), map.getTarget());
	printf("h:%d\n",h);
	openSet.push_back(Vec2Set{map.getCurrent().x_, map.getCurrent().y_, h, 0, h});

	while (!openSet.empty()) {
		auto current = findTheBestF(openSet);
//		printf("p(%d,%d), f:%lf, g:%d, h:%lf\n",current.x_,current.y_,current.f_,current.g_,current.h_);
		if (current == map.getTarget()) {
/*			Path p;
			while(current.p_cameFrom_ != nullptr){
				printf("(%d,%d)\n",current.x_,current.y_);
				p.push_back(*current.p_cameFrom_);
				current = *current.p_cameFrom_;
			}*/
/*			for (auto &func:closedSet)
				if (func.p_cameFrom_ != nullptr)
					printf("(%d,%d),(%d,%d)\n", func.x_, func.y_, func.p_cameFrom_->x_, func.p_cameFrom_->y_);
			printf("\n\n");*/
//			printf("(%d,%d),(%d,%d)\n",current.x_,current.y_,current.p_cameFrom_->x_,current.p_cameFrom_->y_);
			return Path{};
		}
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
				openSet.push_back(neibor);
			int tentative_g_score = current.g_ + dist_between(current, neibor);
			if (tentative_g_score > neibor.g_)
			{
//				printf("x:%d, y:%d,current.g_:%d, dis_between:%d, tentative_G_socre:%d, neibor.g:%d\n",neibor.x_,neibor.y_,current.g_,dist_between(current, neibor),tentative_g_score,neibor.g_);
				continue;
			}
			auto func = std::find_if(openSet.begin(),openSet.end(),[&](Vec2Set node){
				return node == neibor;
			});
			func->p_cameFrom_ = &closedSet.back();
			func->g_ = tentative_g_score;
			func->h_ = heuristic(neibor, map.getTarget());
			func->f_ = func->g_ + func->h_;

//			printf("(%d,%d),(%d,%d)\n",func->x_,func->y_,func->p_cameFrom_->x_,func->p_cameFrom_->y_);
//			printf("neibor.x:%d, neibor.y:%d, f:%lf, g:%d, h:%lf\n",neibor.x_,neibor.y_,neibor.f_,neibor.g_,neibor.h_);
//			usleep(1000000);
		}
//		printf("finished\n");
//		for(const auto& p : openSet)
//			printf("openSet.x:%d,openset.y:%d, f:%lf, g:%d, h:%lf\n",p.x_,p.y_,p.f_,p.g_,p.h_);
	}
	return Path{};
}

Path PathAlgorithm::reconstructPath(const Vec2Set& current){
	path.push_back(current);
	if(current.p_cameFrom_ != nullptr) reconstructPath(*current.p_cameFrom_);
	return path;
}

void PathAlgorithm::getNeighbors(Vec2Set& current, const Map& map, Vec2Set neighbors[]) {
	for(int i = 0; i < 8; i++)
	{
		neighbors[i] = current + deviation[i];
		neighbors[i].p_cameFrom_ = &current;
//		printf("(%d,%d), (%d,%d)\n",neighbors[i].x_,neighbors[i].y_,neighbors[i].p_cameFrom_->x_,neighbors[i].p_cameFrom_->y_);
		neighbors[i].g_ = calculateG(map.getCurrent(),neighbors[i]);
		neighbors[i].h_ = heuristic(neighbors[i],map.getTarget());
		neighbors[i].f_ = neighbors[i].g_ + neighbors[i].h_;
	}
//	printf("\n\n");
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
	return 15 * (abs(start.x_ - target.x_) + abs(start.y_ - target.y_));
}
