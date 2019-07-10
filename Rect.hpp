#pragma once
/*  
	Copyright Affonso Amendola 2019

	Fofonso's Standard Library

	This is part of my standard library of functions and stuff.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/

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

	//Same as m_bound[0] and m_bound[1]
	inline Vector2& v0(){return this->m_bounds[0];}
	inline Vector2& v1(){return this->m_bounds[1];}

	//Returns position of upper left corner, that is, same as m_bounds[0]
	inline Vector2& pos(){return this->m_bounds[0];};
	//Returns a size vector, of the rect.
	inline Vector2 size(){return this->m_bounds[1] - this->m_bounds[0];};

	//Returns the width of the rect.
	inline double width(){return this->m_bounds[1][0] - this->m_bounds[0][0];}
	//Returns the height of the rect.
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

	//Same as m_bound[0] and m_bound[1]
	inline Point2& p0(){return this->m_bounds[0];}
	inline Point2& p1(){return this->m_bounds[1];}
	//Const version, returns a copy of bounds[0or1], not a reference to it.
	inline Point2 p0() const {return this->m_bounds[0];}
	inline Point2 p1() const {return this->m_bounds[1];}

	//Returns position of upper left corner, that is, same as m_bounds[0]
	inline Point2& pos(){return this->m_bounds[0];};
	//Const version, returns a copy of bounds[0or1], not a reference to it.
	inline Point2 pos() const {return this->m_bounds[0];};

	//Returns a size vector, of the rect.
	inline Point2 size() const {return p1() - p0();};

	//Returns the width of the rect.
	inline int width() const {return this->m_bounds[1][0] - this->m_bounds[0][0];}
	//Returns the height of the rect.
	inline int height() const {return this->m_bounds[1][1] - this->m_bounds[0][1];}

	SDL_Rect to_SDL() const;

	Recti scale(int amount) const;

	Recti move(const Point2& amount);
	bool is_inside(const Point2& point);

	void print() const;

	//Multiplies both bounds by a Point.
	inline Recti operator*(const Point2& point)
	{	Recti new_rect(this->p0()*point, this->p1()*point);
		return new_rect; }
};