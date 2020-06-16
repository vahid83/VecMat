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

#ifndef MATRIX_H_
#define MATRIX_H_

#include "Vector.h"

#include <iostream>
#include <complex>

template<typename T, int DX, int DY = DX>
class Matrix
{
private:
	T _element[DX][DY];

public:

	inline static int dimX() { return DX; }
	inline static int dimY() { return DY; }

	inline T& operator()(int x, int y)				{ return _element[x][y]; }
	inline T& elem(int x, int y)					{ return _element[x][y]; }
	inline const T  operator()(int x, int y) const	{ return _element[x][y]; }
	inline const T  elem(int x, int y) const		{ return _element[x][y]; }

	/// Constructors!
	Matrix()					{ zero();	 }
	Matrix( const Matrix& m )	{ *this = m; }
	Matrix( const T t )
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				_element[i][j] = t;
	}

	~Matrix(void)
	{}

	/// Major functions!
	void zero()
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) = 0.;
	}
	
	void one()
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) = 1.;
	}

	void identity()
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) = (i == j) ? 1. : 0.;
	}
	
	Matrix& operator= ( const Matrix& m )
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) = m(i,j);

		return *this;
	}

	Matrix& operator= ( const T& t )
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) = t;

		return *this;
	}

	Matrix& operator+= ( const Matrix& m )
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) += m(i,j);

		return *this;
	}

	Matrix& operator+= ( const T& t )
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) += t;

		return *this;
	}

	Matrix& operator-= ( const Matrix& m )
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) -= m(i,j);

		return *this;
	}

	Matrix& operator-= ( const T& t )
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) -= t;

		return *this;
	}

	Matrix& operator*= ( const Matrix& m )
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) *= m(i,j);

		return *this;
	}

	Matrix& operator*= ( const T& t )
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) *= t;

		return *this;
	}

	Matrix& operator/= ( const Matrix& m )
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) /= m(i,j);

		return *this;
	}

	Matrix& operator/= ( const T& t )
	{
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				elem(i,j) /= t;

		return *this;
	}

	Matrix operator+ ( const Matrix& m ) const
	{
		Matrix<T, DX, DY> mat;
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				mat(i,j) = elem(i,j) + m(i,j);

		return mat;
	}

	Matrix operator+ ( const T& t ) const
	{
		Matrix<T, DX, DY> mat;
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				mat(i,j) = elem(i,j) + t;

		return mat;
	}

	Matrix operator- ( const Matrix& m ) const
	{
		Matrix<T, DX, DY> mat;
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				mat(i,j) = elem(i,j) - m(i,j);

		return mat;
	}

	Matrix operator- ( const T& t ) const
	{
		Matrix<T, DX, DY> mat;
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				mat(i,j) = elem(i,j) - t;

		return mat;
	}

	Matrix operator- () const
	{
		Matrix<T, DX, DY> mat;
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				mat(i,j) = -elem(i,j);

		return mat;
	}

	Matrix operator* ( const T& t ) const
	{
		Matrix<T, DX, DY> mat;
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				mat(i,j) = elem(i,j) * t;

		return mat;
	}

	Matrix operator/ ( const T& t ) const
	{
		Matrix<T, DX, DY> mat;
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				mat(i,j) = elem(i,j) / t;

		return mat;
	}

	Matrix<T, DY, DX> trp() const
	{
		Matrix<T,DY,DX> tm;
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				tm(j, i) = _element[i][j];

		return tm;
	}

	Vector<T, DY> row(int r) const
	{
		Vector<T, DY> v;
		for (int j = 0; j < DY; j++)
			v(j) = _element[r][j];

		return v;
	}

	Vector<T, DX> col(int c) const
	{
		Vector<T, DX> v;
		for (int i = 0; i < DX; i++)
			v(i) = _element[i][c];

		return v;
	}

	T trc() const
	{
		assert(DX==DY);

		T tmp = 0;
		for (int j = 0; j < DY; j++)
			tmp += _element[j][j];

		return tmp;
	}

	Vector<T, DY> diag() const
	{
		assert(DX==DY);

		Vector<T, DY> v;
		for (int i = 0; i < DX; i++)
			v(i) = _element[i][i];

		return v;
	}
	
	Vector<T, DY> operator* ( const Vector<T, DY>& v ) const
	{
		Vector<T, DY> vec;
		for (int i = 0; i < DX; i++)
			vec[i] = v.dot( row(i) );

		return vec;
	}
/*
	Matrix operator* ( const Matrix& m ) const
	{
		Matrix<T, dimX(), m::dimY()> mat;
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				mat(i, j) = Vector::DOT( row(i), m.col(j) );

		return mat;
	}

	Matrix& operator*= ( const Matrix& m ) const
	{
		Matrix<T, dimX(), m::dimY()> tmp;
		for (int i = 0; i < DX; i++)
			for (int j = 0; j < DY; j++)
				tmp(i, j) = Vector::DOT( row(i), m.col(j) );

		*this = tmp;
		return *this;
	}
*/
	bool operator== ( const Matrix& m ) const
	{
		for (int i = 0; i < DX; ++i)
			for (int j = 0; j < DY; ++j)
				if(_element[i][j] != m(i,j)) return false;

		return true;
	}

	bool operator!= ( const Matrix& m ) const
	{
		return !(operator==(m)); 
	}

	Matrix cnj() const
	{
		Matrix<T, DX, DY> mat;
		for (int i = 0; i < DX; ++i)
			for (int j = 0; j < DY; ++j)
				mat(i,j) = std::conj(_element[i][j]);

		return mat;//mat.trp();
	}

	void translate( float x, float y ) {};
	void rotation( float angle ) {};
	void scale( float sx, float sy ) {};
	void shearX( float x ) {};
	void shearY( float y ) {};

	
};

template<class T, int XD, int YD>
std::ostream& operator<<(std::ostream &os, const Matrix<T, XD, YD> &m)
{
	for(int x = 0; x < XD; x++)
	{
		for(int y = 0; y < YD; y++)  
		{
			os << m(x,y) << " ";
		}
		os << "\n";
	}
	return os;
}

template<class T, int XD, int YD>
std::istream& operator>>(std::istream &is, Matrix<T, XD, YD> &m)
{
	for(int x = 0; x < XD; x++)
		for(int y = 0; y < YD; y++)  
			is >> m(x,y);
	return is;
}

#endif
