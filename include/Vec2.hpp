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
		x_ = _x;
		y_ = _y;
	}
	T x_;
	T y_;
	bool operator==(const Vec2& r) const{
		return this->x_ == r.x_ && this->y_ == r.y_;
	}
};

typedef Vec2<int> Vec2i;
typedef std::vector<Vec2i> Path;

class Vec2Set: public Vec2i{
public:
	Vec2Set(){}
	Vec2Set(int _x, int _y, int _f, int _g, int _h){
		x_ = _x;
		y_ = _y;
		f_ = _f;
		g_ = _g;
		h_ = _h;
	}
	bool operator<(const Vec2Set& r) const{
		return this->f_ < r.f_;
	}
	int f_{};
	int g_{};
	int h_{};
	Vec2Set* cameFrom{nullptr};
};

typedef std::vector<Vec2Set> PathSet;

#endif //A_START_VEC2I_HPP
