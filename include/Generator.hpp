//
// Created by pierre on 18-5-3.
//
#ifndef A_START_GENERATOR_HPP
#define A_START_GENERATOR_HPP

#include "Map.hpp"

class Generator{
public:
	static Generator* Instance(){
		static Generator instance;
		return &instance;
	}
	void generataMap(Map& map);
	RBT getShortPath(const Map& map);
};

#endif //A_START_GENERATOR_HPP
