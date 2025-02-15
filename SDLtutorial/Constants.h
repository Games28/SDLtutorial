#ifndef CONSTANTS_H
#define CONSTANTS_H
//#include <cmath>
#include <iostream>
#include <string>
#include <SDL.h>


const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

enum CollisionType
{
	NO_COLLISION,
	PLAYER_ENEMY_COLLISION,
	PLAYER_PROJECTILE_COLLISION,
	ENEMY_PROJECTILE_COLLISION,
	PLAYER_VEGATATION_COLLIDOR,
	PLAYER_LEVEL_COMPLETE_COLLISION
};

enum LayerType {
	TILEMAP_LAYER = 0,
	VEGETATION_LAYER = 1,
	ENEMY_LAYER = 2,
	OBSTACLE_LAYER = 3,
	PLAYER_LAYER = 4,
	PROJECTILE_LAYER = 5,
	UI_LAYER = 6
};

const unsigned int NUM_LAYERS = 7;

const SDL_Color WHITE_COLOR = { 255,255,255,255 };
const SDL_Color GREEN_COLOR = { 0,255,0,255 };

//vect2d

template <class T>
struct v2d_generic
{
	T x = 0;
	T y = 0;
	v2d_generic() : x(0), y(0) {}
	v2d_generic(T _x, T _y) : x(_x), y(_y) {}
	v2d_generic(const v2d_generic& v) : x(v.x), y(v.y) {}
	v2d_generic& operator=(const v2d_generic& v) = default;
	T mag() const { return T(std::sqrt(x * x + y * y)); }
	T mag2() const { return x * x + y * y; }
	v2d_generic  norm() const { T r = 1 / mag(); return v2d_generic(x * r, y * r); }
	v2d_generic  perp() const { return v2d_generic(-y, x); }
	v2d_generic  floor() const { return v2d_generic(std::floor(x), std::floor(y)); }
	v2d_generic  ceil() const { return v2d_generic(std::ceil(x), std::ceil(y)); }
	v2d_generic  max(const v2d_generic& v) const { return v2d_generic(std::max(x, v.x), std::max(y, v.y)); }
	v2d_generic  min(const v2d_generic& v) const { return v2d_generic(std::min(x, v.x), std::min(y, v.y)); }
	v2d_generic  cart() { return { std::cos(y) * x, std::sin(y) * x }; }
	v2d_generic  polar() { return { mag(), std::atan2(y, x) }; }
	T dot(const v2d_generic& rhs) const { return this->x * rhs.x + this->y * rhs.y; }
	T cross(const v2d_generic& rhs) const { return this->x * rhs.y - this->y * rhs.x; }
	v2d_generic  operator +  (const v2d_generic& rhs) const { return v2d_generic(this->x + rhs.x, this->y + rhs.y); }
	v2d_generic  operator -  (const v2d_generic& rhs) const { return v2d_generic(this->x - rhs.x, this->y - rhs.y); }
	v2d_generic  operator *  (const T& rhs)           const { return v2d_generic(this->x * rhs, this->y * rhs); }
	v2d_generic  operator *  (const v2d_generic& rhs) const { return v2d_generic(this->x * rhs.x, this->y * rhs.y); }
	v2d_generic  operator /  (const T& rhs)           const { return v2d_generic(this->x / rhs, this->y / rhs); }
	v2d_generic  operator /  (const v2d_generic& rhs) const { return v2d_generic(this->x / rhs.x, this->y / rhs.y); }
	v2d_generic& operator += (const v2d_generic& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
	v2d_generic& operator -= (const v2d_generic& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
	v2d_generic& operator *= (const T& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
	v2d_generic& operator /= (const T& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
	v2d_generic& operator *= (const v2d_generic& rhs) { this->x *= rhs.x; this->y *= rhs.y; return *this; }
	v2d_generic& operator /= (const v2d_generic& rhs) { this->x /= rhs.x; this->y /= rhs.y; return *this; }
	v2d_generic  operator +  () const { return { +x, +y }; }
	v2d_generic  operator -  () const { return { -x, -y }; }
	bool operator == (const v2d_generic& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
	bool operator != (const v2d_generic& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }
	const std::string str() const { return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }
	friend std::ostream& operator << (std::ostream& os, const v2d_generic& rhs) { os << rhs.str(); return os; }
	operator v2d_generic<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
	operator v2d_generic<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
	operator v2d_generic<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y) }; }
};

// Note: joshinils has some good suggestions here, but they are complicated to implement at this moment, 
// however they will appear in a future version of PGE
template<class T> inline v2d_generic<T> operator * (const float& lhs, const v2d_generic<T>& rhs)
{
	return v2d_generic<T>((T)(lhs * (float)rhs.x), (T)(lhs * (float)rhs.y));
}
template<class T> inline v2d_generic<T> operator * (const double& lhs, const v2d_generic<T>& rhs)
{
	return v2d_generic<T>((T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y));
}
template<class T> inline v2d_generic<T> operator * (const int& lhs, const v2d_generic<T>& rhs)
{
	return v2d_generic<T>((T)(lhs * (int)rhs.x), (T)(lhs * (int)rhs.y));
}
template<class T> inline v2d_generic<T> operator / (const float& lhs, const v2d_generic<T>& rhs)
{
	return v2d_generic<T>((T)(lhs / (float)rhs.x), (T)(lhs / (float)rhs.y));
}
template<class T> inline v2d_generic<T> operator / (const double& lhs, const v2d_generic<T>& rhs)
{
	return v2d_generic<T>((T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y));
}
template<class T> inline v2d_generic<T> operator / (const int& lhs, const v2d_generic<T>& rhs)
{
	return v2d_generic<T>((T)(lhs / (int)rhs.x), (T)(lhs / (int)rhs.y));
}

// To stop dandistine crying...
template<class T, class U> inline bool operator < (const v2d_generic<T>& lhs, const v2d_generic<U>& rhs)
{
	return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);
}
template<class T, class U> inline bool operator > (const v2d_generic<T>& lhs, const v2d_generic<U>& rhs)
{
	return lhs.y > rhs.y || (lhs.y == rhs.y && lhs.x > rhs.x);
}

typedef v2d_generic<int32_t> vi2d;
typedef v2d_generic<uint32_t> vu2d;
typedef v2d_generic<float> vf2d;
typedef v2d_generic<double> vd2d;

#endif