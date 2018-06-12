//
// Created by pierre on 18-5-2.
//
#ifndef A_START_VEC2I_HPP
#define A_START_VEC2I_HPP

#include <queue>
#include <list>
#include <algorithm>
#include <cfloat>

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
	bool operator==(const Vec2<T>& r) const{
		return this->x_ == r.x_ && this->y_ == r.y_;
	}
};

class Vec2Set : public Vec2<int16_t>{
public:
	Vec2Set(){}
	Vec2Set(int _x, int _y){
		x_ = _x;
		y_ = _y;
	}
	Vec2Set(int _x, int _y, int _f, int _g, int _h){
		x_ = _x;
		y_ = _y;
		f_ = _f;
		g_ = _g;
		h_ = _h;
	}
	bool operator<(const Vec2Set& r) const{
		return this->f_ > r.f_;
	}
	Vec2Set operator+(const Vec2Set& r) const{
		return Vec2Set{this->x_ + r.x_, this->y_ + r.y_};
	}
	double f_{};
	int g_{};
	double h_{};
};

class PathSet : public std::list<Vec2Set>{
public:
	bool isContain(const Vec2Set& p){
		return std::any_of(this->begin(),this->end(),[&](const Vec2Set& it){
			return it == p;
		});
	}
	PathSet::iterator find(const Vec2Set& node){
		return std::find_if(this->begin(),this->end(),[&](Vec2Set& it){
			return it == node;
		});
	}
	Vec2Set findTheBestF() {
		double score = DBL_MAX;
		Vec2Set ret;
		for (auto &p : *this) {
			if (p.f_ < score) {
				score = p.f_;
				ret = p;
			}
		}
		return ret;
	}
};

#endif
