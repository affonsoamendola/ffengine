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

class Vector3f
{
public:
	std::vector<double> values;

	Vector3f();
	~Vector3f();

	Vector3f(double x, double y);
	Vector3f(double x, double y, double z);

	Vector3f(std::vector<double> contents);
	Vector3f(std::initializer_list<double> contents);

	//Access Operations
	inline double& operator[](int i);
	inline double operator[](int i) const;

	//Unary Operations
	inline Vector3f operator-();

	//Operations with other vectors;
	inline Vector3f& operator+=(const Vector3f& v);
	inline Vector3f& operator-=(const Vector3f& v);

	inline Vector3f& operator*=(const Vector3f& v);
	inline Vector3f& operator/=(const Vector3f& v);

	//Operations with T types
	inline Vector3f& operator+=(const double& s);
	inline Vector3f& operator-=(const double& s);

	inline Vector3f& operator*=(const double& s);
	inline Vector3f& operator/=(const double& s);

	//Standard Vector operations
	inline double cross(const Vector2f v) const;
	inline Vector3f cross(const Vector3f v) const;

	inline double dot(const Vector3f& v) const;
	inline double abs() const;

	inline double angle(const Vector3f& v) const; 

	inline Vector3f unit();
	//inline Vector3f& rotate(double ang_rad);

	inline void print() const;
};

//Non-member functions
//Operations between two vectors
inline Vector3f operator+(const Vector3f& v_a, const Vector3f& v_b);
inline Vector3f operator-(const Vector3f& v_a, const Vector3f& v_b);
inline Vector3f operator*(const Vector3f& v_a, const Vector3f& v_b);
inline Vector3f operator/(const Vector3f& v_a, const Vector3f& v_b);

//Operations between a vector and a scalar
inline Vector3f operator+(const Vector3f& v_a, const double& b);
inline Vector3f operator+(const double& a, const Vector3f& v_b);

inline Vector3f operator-(const Vector3f& v_a, const double& b);
inline Vector3f operator-(const double& a, const Vector3f& v_b);

inline Vector3f operator*(const Vector3f& v_a, const double& b);
inline Vector3f operator*(const double& a, const Vector3f& v_b);

inline Vector3f operator/(const Vector3f& v_a, const double& b);
inline Vector3f operator/(const double& a, const Vector3f& v_b);
