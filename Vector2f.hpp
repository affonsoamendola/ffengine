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

#define _FF_VECTOR_DEF

#include <vector>
#include <cmath>
#include <iostream>

class Vector2f
{
public:
	std::vector<double> values;

	Vector2f();
	~Vector2f();

	Vector2f(double x, double y);

	Vector2f(std::vector<double> contents);
	Vector2f(std::initializer_list<double> contents);

	//Access Operations
	inline double& operator[](int i);
	inline double operator[](int i) const;

	//Unary Operations
	inline Vector2f operator-();

	//Operations with other vectors;
	inline Vector2f& operator+=(const Vector2f& v);
	inline Vector2f& operator-=(const Vector2f& v);

	inline Vector2f& operator*=(const Vector2f& v);
	inline Vector2f& operator/=(const Vector2f& v);

	//Operations with T types
	inline Vector2f& operator+=(const double& s);
	inline Vector2f& operator-=(const double& s);

	inline Vector2f& operator*=(const double& s);
	inline Vector2f& operator/=(const double& s);

	//Standard Vector operations
	inline double cross(const Vector2f v) const;

	inline double dot(const Vector2f& v) const;
	inline double abs() const;

	inline double angle(const Vector2f& v) const; 

	inline Vector2f unit();
	//inline Vector2f& rotate(double ang_rad);

	inline void print() const;
};

//Non-member functions
//Operations between two vectors
inline Vector2f operator+(const Vector2f& v_a, const Vector2f& v_b);
inline Vector2f operator-(const Vector2f& v_a, const Vector2f& v_b);
inline Vector2f operator*(const Vector2f& v_a, const Vector2f& v_b);
inline Vector2f operator/(const Vector2f& v_a, const Vector2f& v_b);


//Operations between a vector and a scalar
inline Vector2f operator+(const Vector2f& v_a, const double& b);
inline Vector2f operator+(const double& a, const Vector2f& v_b);

inline Vector2f operator-(const Vector2f& v_a, const double& b);
inline Vector2f operator-(const double& a, const Vector2f& v_b);

inline Vector2f operator*(const Vector2f& v_a, const double& b);
inline Vector2f operator*(const double& a, const Vector2f& v_b);

inline Vector2f operator/(const Vector2f& v_a, const double& b);
inline Vector2f operator/(const double& a, const Vector2f& v_b);
