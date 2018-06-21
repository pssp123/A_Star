//
// Created by pierre on 18-6-4.
//

#ifndef A_START_PATHALGORITHM_HPP
#define A_START_PATHALGORITHM_HPP


#include "Vec2.hpp"
#include "Map.hpp"

class PathAlgorithm {
public:
	RBT getShortPath(const Map& map);
	RBT reconstructPath(std::multimap<Node,Node>& cameFrom,Node current,const Map& map);
	void getNeighbors(Node& current, const Map& map, Node neighbors[]);
	int dist_between(const Node x, const Node& y);
	int calculateG(const Node& start,const Node& node);
	int heuristic(const Node& start, const Node& target);
private:
	Node deviation[8] = {Node{-1,1}, Node{0,1},   Node{1,1},
																				 Node{-1,0},                 Node{1,0},
																				 Node{-1,-1}, Node{0,-1}, Node{1,-1}};
};


#endif //A_START_PATHALGORITHM_HPP
