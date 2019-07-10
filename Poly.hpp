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

#include <vector>
#include <limits>
#include <iostream>

#include "Constants.hpp"
#include "Vector.hpp"

//Declares Polygon classes
template <class T>
class Polygon
{
private:
	double m_largest_distance;
	bool m_is_convex;

public:
	std::vector<T> m_vertexes;

	Polygon();
	~Polygon();

	Polygon(const std::vector<T>& contents);

	void add_vertex(const T& vertex);
	void add_vertex(const std::vector<T> vertexes);

	void insert_vertex(int position, const T& vertex);

	void remove_vertex();
	void remove_vertex(int position);

	void set(const std::vector<T>& vertexes);

	int is_convex();

	bool is_inside(const Vector3& vertex);
	bool is_inside(const Vector2& vertex);

	void print();
};

#include "Poly.impl.hpp"

