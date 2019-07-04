#pragma once

#include "Vector.hpp"

#if __has_include("SDL2/SDL.h")
#include "SDL2/SDL.h"
#ifndef _SDL_DEFINED
#define _SDL_DEFINED 1
#endif
#endif

class Rect
{
private:
	Vector2 m_bounds[2];
public:
	Rect();
	Rect(const Vector2 bounds[2]);
	Rect(const std::vector<Vector2> bounds);
	Rect(const Vector2& v0, const Vector2& v1);

	~Rect(){};

	void sort();

	inline Vector2& v0(){return this->m_bounds[0];}
	inline Vector2& v1(){return this->m_bounds[1];}

	inline Vector2& pos(){return v0();};
	inline Vector2 size(){return v1() - v0();};

	inline double width(){return this->m_bounds[1][0] - this->m_bounds[0][0];}
	inline double height(){return this->m_bounds[1][1] - this->m_bounds[0][1];}

	Rect scale(double amount) const;

	Rect move(const Vector2& amount);
	bool is_inside(const Vector2& point);

	void print() const;
};

class Recti
{
private:
	Point2 m_bounds[2];
public:
	Recti();
	Recti(const Point2 bounds[2]);
	Recti(const std::vector<Point2> bounds);
	Recti(const Point2& v0, const Point2& v1);
	Recti(const Point2& size);
	Recti(const int x0, const int y0, const int x1, const int y1);

	~Recti(){};

	void sort();

	inline Point2& p0(){return this->m_bounds[0];}
	inline Point2& p1(){return this->m_bounds[1];}

	inline Point2 p0() const {return this->m_bounds[0];}
	inline Point2 p1() const {return this->m_bounds[1];}

	inline Point2& pos(){return p0();};
	inline Point2 pos() const {return p0();};

	inline Point2 size() const {return p1() - p0();};

	inline int width() const {return this->m_bounds[1][0] - this->m_bounds[0][0];}
	inline int height() const {return this->m_bounds[1][1] - this->m_bounds[0][1];}

	SDL_Rect to_SDL() const;

	Recti scale(int amount) const;

	Recti move(const Point2& amount);
	bool is_inside(const Point2& point);

	void print() const;

	inline Recti operator*(const Point2& point)
	{	Recti new_rect(this->p0()*point, this->p1()*point);
		return new_rect; }
};