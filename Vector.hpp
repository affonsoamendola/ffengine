#pragma once
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

	I fucking hate Templates, they go completely against the doctrine of separating declarations from definitions
	But they are useful when adhering to the DRY principles, So I use the tecnique of purposefully separating them
	on sort of a hacky way, but this works for me, the actual implementation of the functions are in the .impl.hpp
	file, I did use them for a few classes in my standard library that in retrospect didn't NEED to be templates
	(Like Poly.hpp, and arguably Vector.hpp).

	Also the syntax looks horrible
	Shame on you C++ commitee, shame on you.
	(I know you guys tried your best, just messing with you, dont worry <3 )
	(Still hate templates tho)
*/

#define _FF_VECTOR_DEF

#include <vector>
#include <cmath>
#include <iostream>

template<typename T, int vector_dimension>
class Vector
{
public:
	std::vector<T> m_values;

	Vector();
	~Vector();

	Vector(T x, T y);
	Vector(T x, T y, T z);

	Vector(std::vector<T> contents);
	Vector(std::initializer_list<T> contents);

	//Access Operations
	inline T& operator[](int i);
	inline T operator[](int i) const;

	//Unary Operations
	inline Vector<T, vector_dimension> operator-();

	//Operations with other vectors;
	inline Vector<T, vector_dimension>& operator+=(const Vector<T, vector_dimension>& v);
	inline Vector<T, vector_dimension>& operator-=(const Vector<T, vector_dimension>& v);

	inline Vector<T, vector_dimension>& operator*=(const Vector<T, vector_dimension>& v);
	inline Vector<T, vector_dimension>& operator/=(const Vector<T, vector_dimension>& v);

	//Operations with T types
	inline Vector<T, vector_dimension>& operator+=(const T& s);
	inline Vector<T, vector_dimension>& operator-=(const T& s);

	inline Vector<T, vector_dimension>& operator*=(const T& s);
	inline Vector<T, vector_dimension>& operator/=(const T& s);

	//Standard Vector operations
	inline double cross(const Vector<double, 2>& v) const;
	inline Vector<double, 3> cross(const Vector<double, 3>& v) const;

	inline double dot(const Vector<T, vector_dimension>& v) const;
	inline double abs() const;

	inline double angle(const Vector<T, vector_dimension>& v) const; 

	inline Vector<T, vector_dimension> unit();
	//inline Vector<T, vector_dimension>& rotate(double ang_rad);

	inline void print() const;
};

//Non-member functions
//Operations between two vectors
template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator+(const Vector<T, vector_dimension>& v_a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator-(const Vector<T, vector_dimension>& v_a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator*(const Vector<T, vector_dimension>& v_a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator/(const Vector<T, vector_dimension>& v_a, const Vector<T, vector_dimension>& v_b);


//Operations between a vector and a scalar
template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator+(const Vector<T, vector_dimension>& v_a, const T& b);
template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator+(const T& a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator-(const Vector<T, vector_dimension>& v_a, const T& b);
template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator-(const T& a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator*(const Vector<T, vector_dimension>& v_a, const T& b);
template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator*(const T& a, const Vector<T, vector_dimension>& v_b);

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator/(const Vector<T, vector_dimension>& v_a, const T& b);
template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator/(const T& a, const Vector<T, vector_dimension>& v_b);

typedef Vector<double, 2> Vector2;
typedef Vector<double, 3> Vector3;
typedef Vector<int, 2> Point2;

#include "Vector.impl.hpp"