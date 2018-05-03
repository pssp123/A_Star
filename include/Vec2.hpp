//
// Created by pierre on 18-5-2.
//

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

typedef Vec2<int> Vec2i;
#endif //A_START_VEC2I_HPP
