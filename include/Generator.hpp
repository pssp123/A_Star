//
// Created by pierre on 18-5-3.
//
#include "Map.hpp"

#ifndef A_START_GENERATOR_HPP
#define A_START_GENERATOR_HPP
class Generator{
public:
	static Generator* Instance(){
		static Generator instance;
		return &instance;
	}
	void generataMap(Map& map);
	int heuristic(int16_t x, int16_t y, Vec2i& target);
	Path getShortPath(const Map& map);
};

#endif //A_START_GENERATOR_HPP
