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

#include "Utility.hpp"

//POLYGON MEMBER FUNCTIONS:

template<class T>
Polygon<T>::Polygon()
{}

template<class T>
Polygon<T>::~Polygon()
{}

template<class T>
Polygon<T>::Polygon(const std::vector<T>& contents)
{
	this->set(contents);
}

template<class T>
void Polygon<T>::add_vertex(const T& vertex)
{
	this->m_vertexes.push_back(vertex);
	this->m_is_convex = this->is_convex();
}

template<class T>	
void Polygon<T>::add_vertex(const std::vector<T> vertexes)
{
	this->m_vertexes.insert(this->m_vertexes.end(), vertexes.begin(), vertexes.end());	
	this->m_is_convex = this->is_convex();
}

template<class T>
void Polygon<T>::insert_vertex(int position, const T& vertex)
{
	this->m_vertexes.insert(this->m_vertexes.begin() + position, vertex);
	this->m_is_convex = this->is_convex();
}

template<class T>
void Polygon<T>::remove_vertex()
{
	this->m_vertexes.erase(this->m_vertexes.end());
	this->m_is_convex = this->is_convex();
}

template<class T>
void Polygon<T>::remove_vertex(int position)
{
	if(position >= 0) 	this->m_vertexes.erase(this->m_vertexes.begin() + position);
	else 				this->m_vertexes.erase(this->m_vertexes.end() + position);

	this->m_is_convex = this->is_convex();
}

template<class T>
void Polygon<T>::set(const std::vector<T>& vertexes)
{
	this->m_vertexes.clear();
	copy(vertexes.begin(), vertexes.end(), this->m_vertexes.begin());
	this->m_is_convex = this->is_convex();
}

//Checks if the polygon is convex, concave or complex,
//returns 1 if convex, 0 if concave, -1 if complex
template<>
inline int Polygon<Vector2>::is_convex()
{
	double total_angle = 0.0f;
	double current_angle = 0.0f;

	Vector2 v0 = this->m_vertexes[0] - this->m_vertexes.back();
	Vector2 v1 = this->m_vertexes[1] - this->m_vertexes[0];

	for(int i = 2; i < this->m_vertexes.size(); i ++)
	{
		current_angle = v0.angle(v1);

		if(total_angle != 0.0f)
		{
			if(sign(current_angle) != sign(total_angle))
				return 0;
		}

		total_angle += current_angle;

		v0 = this->m_vertexes[i-1] - this->m_vertexes[i-2];
		v1 = this->m_vertexes[i]   - this->m_vertexes[i-1];
	}

	double number_of_turns = current_angle / (2 * PI);

	if(number_of_turns < 0.) number_of_turns *= -1.;

	if(number_of_turns <= 1. + std::numeric_limits<double>::epsilon() && number_of_turns >= 1. - std::numeric_limits<double>::epsilon())
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

template<>
inline int Polygon<Vector3>::is_convex() {}

/*
template<class T>
bool Polygon<T>::is_inside(const Vector2& vertex)
{
}
*/
template<class T>
void Polygon<T>::print()
{
	for(int i = 0; i < this->m_vertexes.size(); i++)
	{
		this->m_vertexes[i].print();
	}
}

//bool is_inside(const Vector3& vertex);

//-----------------------------------------------