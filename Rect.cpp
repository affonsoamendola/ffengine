/*  
	Copyright Affonso Amendola 2019

	Fofonso's Standard Library

	This is part of my standard library of functions and stuff.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/
/*
	OKAY...
	SO...

	In the other files (The ones using templates, Poly.hpp and Vector.hpp), I explained why I dont like them,
	but this is the other way of doing it, which MASSIVELY violates the Dont Repeat Yourself principles.
	I really dont like writing like this, makes me feel like a bad programmer (Which I guess everyone except
	Saint Carmack or Saint Abrash are), but this is how I decided to do this, since there would only be
	two variations of Rect, a Vector one and a Point one.
*/

#include "Rect.hpp"

//DIFFERENCES BETWEEN RECT AND RECTI
//Rects are simply two points in space.
//
//RECT class objects are objects where these two points are two Vector2's, that is four Doubles.
//RECTI class objects are objects where these two points are two Point2's, that is four Ints.

//RECT CLASS MEMBER FUNCTIONS:

//Create Rect
Rect::	Rect()
{
	this->m_bounds[0] = {0., 0.};
	this->m_bounds[1] = {0., 0.};
}

Rect::	Rect(const Vector2 bounds[2])
{
	this->m_bounds[0] = bounds[0];
	this->m_bounds[1] = bounds[1];
	this->sort();
}

Rect::	Rect(const std::vector<Vector2> bounds)
{
	this->m_bounds[0] = bounds[0];
	this->m_bounds[1] = bounds[1];
	this->sort();
}

Rect::	Rect(const Vector2& v0, const Vector2& v1)
{
	this->m_bounds[0] = v0;
	this->m_bounds[1] = v1;
	this->sort();
}

//Makes the top left corner bounds[0] and the lower right corner bounds[1]
void Rect::sort()
{
	if(this->m_bounds[0][0] > this->m_bounds[1][0])
	{
		std::swap(m_bounds[0][0], m_bounds[1][0]);
	}

	if(this->m_bounds[0][1] > this->m_bounds[1][1])
	{
		std::swap(m_bounds[0][1], m_bounds[1][1]);
	}
}


//Scale rect (While keeping top left position constant.)
Rect Rect::scale(double amount) const
{
	Rect new_rect(this->m_bounds);

	Vector2 new_corner;

	new_corner = new_rect.m_bounds[0];

	new_corner[0] += new_rect.width() * amount;
	new_corner[1] += new_rect.height() * amount;

	new_rect.m_bounds[1] = new_corner;

	return new_rect;
}

//Move rect v amount
Rect Rect::move(const Vector2& v)
{
	Rect new_rect(this->m_bounds);

	new_rect.m_bounds[0] += v;
	new_rect.m_bounds[1] += v;

	return new_rect;
}

//Check if point is inside rect.
bool Rect::is_inside(const Vector2& point)
{
	if(	point[0] >= this->m_bounds[0][0] && point[0] <= this->m_bounds[1][0] &&
		point[1] >= this->m_bounds[0][1] && point[0] <= this->m_bounds[1][1])
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Print the rect.
void Rect::print() const
{
	this->m_bounds[0].print();
	this->m_bounds[1].print();
}

//---------------------------------------

//RECTI CLASS MEMBER FUNCTIONS:
//Creates Recti
Recti::	Recti() 
{
	this->m_bounds[0] = {0, 0};
	this->m_bounds[1] = {0, 0};
}

Recti::	Recti(const Point2 bounds[2])
{
	this->m_bounds[0] = bounds[0];
	this->m_bounds[1] = bounds[1];
}

Recti::	Recti(const std::vector<Point2> bounds)
{
	this->m_bounds[0] = bounds[0];
	this->m_bounds[1] = bounds[1];
}

Recti::	Recti(const Point2& v0, const Point2& v1)
{
	this->m_bounds[0] = v0;
	this->m_bounds[1] = v1;
}

Recti::	Recti(const Point2& size)
{
	this->m_bounds[0] = Point2(0, 0);
	this->m_bounds[1] = size;
}

Recti:: Recti(const int x0, const int y0, const int x1, const int y1)
{
	this->m_bounds[0] = Point2(x0, y0);
	this->m_bounds[1] = Point2(x1, y1);
}


//Makes the top left corner bounds[0] and the lower right corner bounds[1]
void Recti::sort()
{
	if(this->m_bounds[0][0] > this->m_bounds[1][0])
	{
		std::swap(m_bounds[0][0], m_bounds[1][0]);
	}

	if(this->m_bounds[0][1] > this->m_bounds[1][1])
	{
		std::swap(m_bounds[0][1], m_bounds[1][1]);
	}
}

//Scale rect (While keeping top left position constant.)
Recti Recti::scale(int amount) const
{
	Recti new_rect(this->m_bounds);

	Point2 new_corner;

	new_corner = new_rect.m_bounds[0];

	new_corner[0] += new_rect.width() * amount;
	new_corner[1] += new_rect.height() * amount;

	new_rect.m_bounds[1] = new_corner;

	return new_rect;
}

//Move rect v amount
Recti Recti::move(const Point2& v)
{
	Recti new_rect(this->m_bounds);

	new_rect.m_bounds[0] += v;
	new_rect.m_bounds[1] += v;

	return new_rect;
}

//Check if point is inside rect
bool Recti::is_inside(const Point2& point)
{
	if(	point[0] >= this->m_bounds[0][0] && point[0] <= this->m_bounds[1][0] &&
		point[1] >= this->m_bounds[0][1] && point[0] <= this->m_bounds[1][1])
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Converts rect to SDL_rect
SDL_Rect Recti::to_SDL() const
{
	SDL_Rect new_rect;

	new_rect.x = this->m_bounds[0][0];
	new_rect.y = this->m_bounds[0][1];
	new_rect.w = this->width();
	new_rect.h = this->height();

	return new_rect;
}

//Print Rect
void Recti::print() const
{
	this->m_bounds[0].print();
	this->m_bounds[1].print();
}

//-----------------------------