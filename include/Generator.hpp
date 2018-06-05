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
	Path getShortPath(const Map& map);
};

#endif //A_START_GENERATOR_HPP
