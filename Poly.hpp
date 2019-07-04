#pragma once

#include <vector>
#include <limits>
#include <iostream>

#include "Constants.hpp"
#include "Vector.hpp"

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

