//
// Created by pierre on 18-5-2.
//
#include <vector>

#ifndef A_START_VEC2I_HPP
#define A_START_VEC2I_HPP
template <typename T>
class Vec2{
public:
	Vec2(){};
	Vec2(T _x, T _y){
		x = _x;
		y = _y;
	}
	T x;
	T y;
	bool operator==(const Vec2& r) const{
		return this->x == r.x && this->y == r.y;
	}
};

class PathSet

typedef Vec2<int> Vec2i;
typedef std::vector<Vec2<int>> Path;
#endif //A_START_VEC2I_HPP
