/*
 * Developed by Vahid Noormofidi
 *
 * Copyright (c) 2016 GitHub, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <iostream>

template<typename T, int D>
class Vector
{
private:
	T _element[D];

public:

	inline T& x() { return operator[](0); }
	inline T& y() { return operator[](1); }
	inline T& z() { return operator[](2); }
	inline T& w() { return operator[](3); }
	inline const T x() const { return operator[](0); }
	inline const T y() const { return operator[](1); }
	inline const T z() const { return operator[](2); }
	inline const T w() const { return operator[](3); }

	T Length()	{ return D; }
	T size()	{ return D; }

	/// Constructors
	Vector()				{	zero();		}
	Vector(const Vector& v)	{	*this = v;	}
	
	Vector(T a)
	{
		for (int i = 0; i < D; ++i) _element[i] = a;
	}

	Vector(T a1, T a2)
	{
		assert(D >= 2);
		_element[0] = a1; _element[1] = a2;
		for (int i = 2; i < D; ++i)
			_element[i] = a2;
	}

	Vector(T a1, T a2, T a3)
	{
		assert(D >= 3);
		_element[0] = a1; _element[1] = a2; _element[2] = a3;
		for (int i = 3; i < D; ++i)
			_element[i] = a3;
	}

	Vector(T a1, T a2, T a3, T a4)
	{
		assert(D >= 4);
		_element[0] = a1; _element[1] = a2; _element[2] = a3; _element[3] = a4;
		for (int i = 4; i < D; ++i)
			_element[i] = a4;
	}
	
	~Vector(void)
	{}
	
	/// Major functions!
	void zero()
	{
		for (int i = 0; i < D; ++i) _element[i] = 0;
	}

	void one()
	{
		for (int i = 0; i < D; ++i) _element[i] = 1;
	}

	T& operator() (int i) 
	{ 
		assert(i>=0 && i<D);
		return _element[i];
	}

	const T operator() (int i) const
	{ 
		assert(i>=0 && i<D);
		return _element[i];
	}

	T& operator[] (int i) 
	{ 
		assert(i>=0 && i<D);
		return _element[i];
	}

	const T operator[] (int i) const
	{ 
		assert(i>=0 && i<D);
		return _element[i];
	}

	T getElement(int i)	const	{ return _element[i]; }
	void setElement(T e, int i) { _element[i] = e; }
	
	void setVector(T val)
	{
		for (int i = 0; i < D; ++i) _element[i] = val;
	}

	void homogenize()
	{
		for (int i = 0; i < D; ++i)
			_element[i] /= _element[D];
	}

	T normInf() const
	{
		T tmp = 0;
		for (int i = 0; i < D; ++i)
			if (_element[i] > tmp)
				tmp = _element[i];
		return tmp;
	}

	T norm1() const
	{
		T tmp = 0;
		for (int i = 0; i < D; ++i)
			tmp += _element[i];
		return tmp;
	}

	T norm2() const
	{
		T tmp = 0;
		for (int i = 0; i < D; ++i)
			tmp += _element[i]*_element[i];
		return tmp;
	}

	T norm() const
	{
		return sqrt( norm2() );
	}

	T normalize()
	{
		T tmp = norm();
		(*this) *= T(1.0)/tmp;
		return tmp;	
	}

	Vector abs() const
	{
		Vector tmp;
		for(int i = 0; i < D; ++i) 
			tmp[i] = abs(_element[i]);
		return tmp;
	}

	T dot(const Vector& v) const
	{
		T tmp = 0;
		for (int i = 0; i < D; ++i)
			tmp += _element[i] * v(i);
		return tmp;
	}

	static T DOT(Vector& v1, Vector& v2)
	{
		T tmp = 0;
		for (int i = 0; i < D; ++i)
			tmp += v1(i) * v2(i);
		return tmp;
	}

	Vector cross(const Vector& v) const
	{
		assert(D==3);
		return Vector<T,D>( 
					(_element[1] * v(2)) - (_element[2] * v(1)),
					(_element[2] * v(0)) - (_element[0] * v(2)),
					(_element[0] * v(1)) - (_element[1] * v(0))
				);
	}	

	static Vector CROSS(Vector& v1, Vector& v2)
	{
		assert(D==3);
		return Vector<T,D>( 
					(v1[1] * v2(2)) - (v1[2] * v2(1)),
					(v1[2] * v2(0)) - (v1[0] * v2(2)),
					(v1[0] * v2(1)) - (v1[1] * v2(0))
				);
	}

	Vector& operator= (const T& t)
	{
		for (int i = 0; i < D; ++i)
			_element[i] = t;
		return *this;
	}
	
	Vector& operator= (const Vector& v)
	{
		for (int i = 0; i < D; ++i)
			_element[i] = v(i);
		return *this;
	}

	Vector operator+ (const Vector& v) const
	{
		Vector tmp;
		for(int i = 0; i < D; ++i) 
			tmp[i] = _element[i] + v(i);
		return tmp;
	}

	Vector operator- (const Vector& v) const
	{
		Vector tmp;
		for(int i = 0; i < D; ++i) 
			tmp[i] = _element[i] - v(i);
		return tmp;
	}

	Vector operator- () const
	{
		Vector tmp;
		for(int i = 0; i < D; ++i) 
			tmp[i] = - _element[i];
		return tmp;
	}

	Vector operator* (const T& t) const
	{
		Vector tmp;
		for(int i = 0; i < D; ++i) 
			tmp[i] = _element[i] * t;
		return tmp;
	}

	Vector operator* (const Vector& v) const
	{
		Vector tmp;
		for(int i = 0; i < D; ++i) 
			tmp[i] = _element[i] * v(i);
		return tmp;
	}

	Vector operator/ (const T& t) const
	{
		Vector tmp;
		for(int i = 0; i < D; ++i) 
			tmp[i] = _element[i] / t;
		return tmp;
	}

	Vector operator/ (const Vector& v) const
	{
		Vector tmp;
		for(int i = 0; i < D; ++i) 
			tmp[i] = _element[i] / v(i);
		return tmp;
	}

	Vector& operator*= (const T& t)
	{
		for(int i = 0; i < D; ++i) 
			_element[i] *= t;
		return *this;
	}

	Vector& operator*= (const Vector& v)
	{
		for(int i = 0; i < D; ++i) 
			_element[i] *= v(i);
		return *this;
	}

	Vector& operator/= (const T& t)
	{
		for(int i = 0; i < D; ++i) 
			_element[i] /= t;
		return *this;
	}

	Vector& operator/= (const Vector& v)
	{
		for(int i = 0; i < D; ++i) 
			_element[i] /= v(i);
		return *this;
	}

	Vector& operator+= (const T& t)
	{
		for(int i = 0; i < D; ++i) 
			_element[i] += t;
		return *this;
	}

	Vector& operator+= (const Vector& v)
	{
		for(int i = 0; i < D; ++i) 
			_element[i] += v(i);
		return *this;
	}

	Vector& operator-= (const T& t)
	{
		for(int i = 0; i < D; ++i) 
			_element[i] -= t;
		return *this;
	}

	Vector& operator-= (const Vector& v)
	{
		for(int i = 0; i < D; ++i) 
			_element[i] -= v(i);
		return *this;
	}

	bool operator== (Vector& v) const
	{
		for(int i = 0; i < D; ++i)
			if(_element[i] != v[i]) return false;
      
		return true;
	}

	bool operator> (const T& t) const
	{
		for(int i = 0; i < D; ++i)
			if(_element[i] <= t) return false;
      
		return true;
	}

	bool operator< (const T& t) const
	{
		for(int i = 0; i < D; ++i)
			if(_element[i] >= t) return false;
      
		return true;
	}

	bool operator!= (const Vector &v) const
	{
		return !(operator==(v)); 
	}

};

template<typename T, int D>
static std::ostream& operator<< (std::ostream& os, Vector<T,D>& v)
{
	for (int i = 0; i < D; ++i)
		os  << v(i) << " ";

	return os;
}

template<typename T, int D>
static std::istream& operator>> (std::istream& is, Vector<T,D>& v)
{
	for (int i = 0; i < D; ++i)
		is  >> v(i);

	return is;
}

///////////////////////////////////////////////////////////////////////////////
typedef Vector<float, 1> Vector1f;
typedef Vector<float, 2> Vector2f;
typedef Vector<float, 3> Vector3f;
typedef Vector<float, 4> Vector4f;

typedef Vector<int, 1> Vector1i;
typedef Vector<int, 2> Vector2i;
typedef Vector<int, 3> Vector3i;
typedef Vector<int, 4> Vector4i;

#endif

