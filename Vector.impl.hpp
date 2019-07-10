#pragma once
/*  
	Copyright Affonso Amendola 2019

	Fofonso's Standard Library

	This is part of my standard library of functions and stuff.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/
//VECTOR CLASS MEMBER FUNCTIONS:

//Constructors and destructor
template<typename T, int vector_dimension>
Vector<T, vector_dimension>::	Vector()
								:m_values(vector_dimension)
{}

template<typename T, int vector_dimension>
Vector<T, vector_dimension>::	~Vector()
{}

template<typename T, int vector_dimension>
Vector<T, vector_dimension>::	Vector(std::vector<T> contents)
								:m_values(contents)
{}

template<typename T, int vector_dimension>
Vector<T, vector_dimension>::	Vector(std::initializer_list<T> contents)
								:m_values(contents)
{}

template<typename T, int vector_dimension>
Vector<T, vector_dimension>::	Vector(T x, T y)
								:m_values()
{
	this->m_values.reserve(2);
	this->m_values.push_back(x);
	this->m_values.push_back(y);
}

template<typename T, int vector_dimension>
Vector<T, vector_dimension>::	Vector(T x, T y, T z)
								:m_values()
{
	this->m_values.reserve(3);
	this->m_values.push_back(x);
	this->m_values.push_back(y);
	this->m_values.push_back(z);
}

//Access Operations
template<typename T, int vector_dimension>
inline T& Vector<T, vector_dimension>::operator[](int i)
{
	return this->m_values.at(i);
}

template<typename T, int vector_dimension>
inline T Vector<T, vector_dimension>::operator[](int i) const
{
	return this->m_values.at(i);
}

//Unary Operations
template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> Vector<T, vector_dimension>::operator-()
{
	Vector<T, vector_dimension> temp;

	for(int i = 0; i < this->m_values.size(); i++)
	{
		temp[i] = -temp[i];
	}

	return temp;
}

//Operations with other vectors;
template<typename T, int vector_dimension>
inline Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator+=(const Vector<T, vector_dimension>& v)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] += v[i];
	}
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator-=(const Vector<T, vector_dimension>& v)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] -= v[i];
	}
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator*=(const Vector<T, vector_dimension>& v)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] *= v[i];
	}
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator/=(const Vector<T, vector_dimension>& v)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] /= v[i];
	}
}

//Operations with T types;
template<typename T, int vector_dimension>
inline Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator+=(const T& s)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] += s;
	}
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator-=(const T& s)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] -= s;
	}
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator*=(const T& s)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] *= s;
	}
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension>& Vector<T, vector_dimension>::operator/=(const T& s)
{
	for(int i = 0; i < this->m_values.size(); i++)
	{
		this->m_values[i] /= s;
	}
}

//Standard Vector operations
template<>
inline double Vector<double, 2>::cross(const Vector<double, 2>& v) const
{
	return (this->m_values[0] * v[1]) - (this->m_values[1] * v[0]);
}

template<>
inline Vector<double, 3> Vector<double, 3>::cross(const Vector<double, 3>& v) const
{
	Vector<double, 3> new_v;

	new_v[0] = (this->m_values[1]*v[2]) - (this->m_values[2]*v[1]);
	new_v[1] = (this->m_values[2]*v[0]) - (this->m_values[0]*v[2]);
	new_v[2] = (this->m_values[0]*v[1]) - (this->m_values[1]*v[0]);

	return new_v;
}


template<typename T, int vector_dimension>
inline double Vector<T, vector_dimension>::dot(const Vector<T, vector_dimension>& v) const
{
	double sum = 0.0f;

	for(int i = 0; i < this->m_values.size(); i++)
	{
		sum += this->m_values[i]*v[i];
	}

	return sum;
}

template<typename T, int vector_dimension>
inline double Vector<T, vector_dimension>::abs() const
{
	double sum = 0.0f;

	for(int i = 0; i < this->m_values.size(); i++)
	{
		sum += this->m_values[i] * this->m_values[i];
	}

	return sqrt(sum);
}

template<typename T, int vector_dimension>
inline double Vector<T, vector_dimension>::angle(const Vector<T, vector_dimension>& v) const
{
	return acos(this->dot(v) / (this->abs() * v.abs()));
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> Vector<T, vector_dimension>::unit()
{
	Vector<T, vector_dimension> new_v;

	new_v = *this / this->abs();

	return new_v;
}

/*
template<typename T, int vector_dimension>
Vector<T, vector_dimension>& Vector<T, vector_dimension>::rotate(double ang_rad)
{

}
*/

template<>
inline void Vector<double, 2>::print() const
{
	printf("%f %f\n", this->m_values[0], this->m_values[1]);
}

template<>
inline void Vector<double, 3>::print() const
{
	printf("%f %f %f\n", this->m_values[0], this->m_values[1], this->m_values[2]);
}

template<>
inline void Vector<int, 2>::print() const
{
	printf("%d %d\n", this->m_values[0], this->m_values[1]);
}

template<>
inline void Vector<int, 3>::print() const
{
	printf("%d %d %d\n", this->m_values[0], this->m_values[1], this->m_values[2]);
}

//------------------------------------------------------------------------------------

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator+(	const Vector<T, vector_dimension>& v_a, 
												const Vector<T, vector_dimension>& v_b)
{	
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] + v_b[i];
	}

	return new_v;
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator-(	const Vector<T, vector_dimension>& v_a, 
												const Vector<T, vector_dimension>& v_b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] - v_b[i];
	}

	return new_v;
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator*(	const Vector<T, vector_dimension>& v_a, 
												const Vector<T, vector_dimension>& v_b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] * v_b[i];
	}

	return new_v;
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator/(	const Vector<T, vector_dimension>& v_a, 
												const Vector<T, vector_dimension>& v_b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] / v_b[i];
	}

	return new_v;
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator+(	const Vector<T, vector_dimension>& v_a, 
												const T& b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] +b;
	}

	return new_v;
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator+(	const T& a, 
												const Vector<T, vector_dimension>& v_b)
{
	return v_b + a;
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator-(	const Vector<T, vector_dimension>& v_a, 
												const T& b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] - b;
	}

	return new_v;
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator-(	const T& a, 
												const Vector<T, vector_dimension>& v_b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = a - v_b[i];
	}

	return new_v;
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator*(	const Vector<T, vector_dimension>& v_a, 
												const T& b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] * b;
	}

	return new_v;
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator*(	const T& a, 
												const Vector<T, vector_dimension>& v_b)
{
	return v_b * a;
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator/(	const Vector<T, vector_dimension>& v_a, 
												const T& b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = v_a[i] / b;
	}

	return new_v;
}

template<typename T, int vector_dimension>
inline Vector<T, vector_dimension> operator/(	const T& a, 
												const Vector<T, vector_dimension>& v_b)
{
	Vector<T, vector_dimension> new_v;

	for(int i = 0; i < vector_dimension; i++)
	{
		new_v[i] = a / v_b[i];
	}

	return new_v;
}