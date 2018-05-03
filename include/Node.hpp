//
// Created by pierre on 18-5-2.
//

#ifndef A_START_NODE_HPP
#define A_START_NODE_HPP

#include "Vec2.hpp"

class Node{
public:
	Node(){};
	Node(Vec2i _coor){
		coordinate = _coor;
	}
	Node(int _g, int _h, int _score){
		g = _g;
		h = _h;
		socre = _score;
	};
	Vec2i coordinate;
	Node* parent;
	int g;
	int h;
	int socre;
	bool operator>(const Node& right)const{
		return socre > right.socre;
	}
	bool operator<(const Node& right)const{
		return socre < right.socre;
	}
};
#endif //A_START_NODE_HPP
