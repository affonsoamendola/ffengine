/* 	
	Copyright Affonso Amendola 2019

	Fofonso's Vector, version 2.1

	This is part of my standard usage library, I use this in many of my things, it's pretty kewl.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/

#pragma once

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