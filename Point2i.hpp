#pragma once
/*  
	Copyright Affonso Amendola 2023

	Foffonso's Standard Library

	This is part of my standard library of functions and stuff.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/

/*
	I still hate the C++ template stuff, just takes bloody ages to compile
*/

#define _FF_POINT2I_DEF

#include <vector>
#include <cmath>
#include <iostream>

class Point2i
{
public:
	std::vector<int> values;

	Point2i();
	~Point2i();

	Point2i(int x, int y);
	
	Point2i(std::vector<int> contents);
	Point2i(std::initializer_list<int> contents);

	//Access Operations
	inline int& operator[](int i);
	inline int operator[](int i) const;

	//Unary Operations
	inline Point2i operator-();

	//Operations with other vectors;
	inline Point2i& operator+=(const Point2i& v);
	inline Point2i& operator-=(const Point2i& v);

	inline Point2i& operator*=(const Point2i& v);
	inline Point2i& operator/=(const Point2i& v);

	//Operations with T types
	inline Point2i& operator+=(const int& s);
	inline Point2i& operator-=(const int& s);

	inline Point2i& operator*=(const double& s);
	inline Point2i& operator/=(const double& s);

	//inline Point2i& rotate(double ang_rad);

	inline void print() const;
};

//Non-member functions
//Operations between two vectors
inline Point2i operator+(const Point2i& v_a, const Point2i& v_b);
inline Point2i operator-(const Point2i& v_a, const Point2i& v_b);
inline Point2i operator*(const Point2i& v_a, const Point2i& v_b);
inline Point2i operator/(const Point2i& v_a, const Point2i& v_b);

//Operations between a vector and a scalar
inline Point2i operator+(const Point2i& v_a, const int& b);
inline Point2i operator+(const int& a, const Point2i& v_b);

inline Point2i operator-(const Point2i& v_a, const int& b);
inline Point2i operator-(const int& a, const Point2i& v_b);

inline Point2i operator*(const Point2i& v_a, const int& b);
inline Point2i operator*(const int& a, const Point2i& v_b);

inline Point2i operator/(const Point2i& v_a, const int& b);
inline Point2i operator/(const int& a, const Point2i& v_b);
