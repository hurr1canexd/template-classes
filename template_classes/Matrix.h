#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "Fraction.h"

using namespace std;

template <typename T, unsigned int order>
class Matrix
{
public:
	Matrix();
	Matrix(T);
	~Matrix();
	friend istream& operator>> <T, order>(istream&, Matrix&);
	friend ostream& operator<< <T, order>(ostream&, const Matrix&);
	Matrix<T, order> operator+(const Matrix<T, order>&);
	Matrix<T, order> operator-(const Matrix<T, order>&);
	Matrix<T, order> operator*(const Matrix<T, order>&);
	Matrix<T, order> operator/(const Matrix<T, order>&);
	Matrix<T, order> operator*(int); // multiply by number
	bool operator==(int);
	bool operator!=(int);
	void transpose();
	T determinant();
	Matrix<T, order> inverse();

private:
	vector<vector<T>> matr;
};

template <typename T, unsigned int order>
Matrix<T, order>::Matrix()
{
	matr.resize(order); // allocate memory for the vectors (strings of the matrix)
	for (int i = 0; i < order; i++)
		matr[i].resize(order);
}

template<typename T, unsigned int order>
inline Matrix<T, order>::Matrix(T n)
{
	matr.resize(order); // allocate memory for the vectors (strings of the matrix)
	for (int i = 0; i < order; i++)
		matr[i].resize(order);

	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			matr[i][j] = n;
}

template <typename T, unsigned int order>
Matrix<T, order>::~Matrix()
{
}

template <typename T, unsigned int order>
istream& operator>>(istream& is, Matrix<T, order>& M)
{
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			is >> M.matr[i][j];
	return is;
}

template <typename T, unsigned int order>
ostream& operator<<(ostream& os, const Matrix<T, order>& M)
{
	for (int i = 0; i < order; i++)
	{
		cout << endl;
		for (int j = 0; j < order; j++)
			os << M.matr[i][j] << " "; // Сделоть бы форматированный вывод...........
	}
	cout << endl << endl;
	return os;
}

template <typename T, unsigned int order>
Matrix<T, order> Matrix<T, order>::operator+(const Matrix<T, order>& M)
{
	Matrix<T, order> obj; // don't call the resize, because the constructor is called
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			obj.matr[i][j] = this->matr[i][j] + M.matr[i][j];
	return obj;
}

template <typename T, unsigned int order>
Matrix<T, order> Matrix<T, order>::operator-(const Matrix<T, order>& M)
{
	Matrix<T, order> obj; // don't call the resize, because the constructor is called
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			obj.matr[i][j] = this->matr[i][j] - M.matr[i][j];
	return obj;
}

template <typename T, unsigned int order>
Matrix<T, order> Matrix<T, order>::operator*(const Matrix<T, order>& M)
{
	Matrix<T, order> obj;
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			for (int inner = 0; inner < order; inner++)
				obj.matr[i][j] += this->matr[i][inner] * M.matr[inner][j];
	return obj;
}

template <typename T, unsigned int order>
Matrix<T, order> Matrix<T, order>::operator/(const Matrix<T, order>& M)
{

}

template <typename T, unsigned int order>
void Matrix<T, order>::transpose()
{
	for (int i = 0; i < order; i++)
		for (int j = i; j < order; j++)
		{
			T tmp = this->matr[i][j];
			this->matr[i][j] = this->matr[j][i];
			this->matr[j][i] = tmp;
		}
}

template <typename T, unsigned int order>
Matrix<T, order> Matrix<T, order>::operator*(int alpha)
{
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			this->matr[i][j] *= alpha;
	return *this;
}

template<typename T, unsigned int order>
inline bool Matrix<T, order>::operator==(int n)
{
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
		{
			if (matr[i][j] != n)
				return false;
		}
	return true;
}

template<typename T, unsigned int order>
inline bool Matrix<T, order>::operator!=(int n)
{
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
		{
			if (matr[i][j] != n)
				return true;
		}

	return false;
}

template <typename T, unsigned int order>
T Matrix<T, order>::determinant()
{
	Matrix<T, order> obj = *this;
	T res = 1;
	for (int i = 0; i < order - 1; i++)
	{
		if (obj.matr[i][i] == 0)
			res = res * -1;
		int tmp = i;
		while (obj.matr[tmp][i] == 0 && tmp < order)
			tmp++;
		if (tmp == order)
		{
			res = 0;
			return res;
		}
		for (int j = 0; j < order; j++)
		{
			swap(obj.matr[tmp][j], obj.matr[i][j]);
		}
		for (int k = i + 1; k < order; k++)
		{
			T koef = obj.matr[k][i] / obj.matr[i][i];
			for (int j = i; j < order; j++)
				obj.matr[k][j] = obj.matr[k][j] - obj.matr[i][j] * koef;
		}
		res = res * obj.matr[i][i];
	}
	return res * obj.matr[order - 1][order - 1];
}

template <typename T, unsigned int order>
Matrix<T, order> Matrix<T, order>::inverse()
{
	if (this->determinant()==0)
		exit(-3);
	Matrix<T, order> res, obj = *this;
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
		{
			if (i == j)
				res.matr[i][j] = 1;
			else
				res.matr[i][j] = 0;
		}
	for (int i = 0; i < order - 1; i++)
	{
		int tmp = i;
		while (matr[tmp][i] == 0 && tmp < order)
			tmp++;
		for (int j = 0; j < order; j++)
		{
			T tmpMean = obj.matr[i][j];
			obj.matr[i][j] = obj.matr[tmp][j];
			obj.matr[tmp][j] = tmpMean;
			tmpMean = res.matr[i][j];
			res.matr[i][j] = res.matr[tmp][j];
			res.matr[tmp][j] = tmpMean;
		}
		for (int j = 0; j < order; j++)
		{
			obj.matr[i][j] = obj.matr[i][j] / obj.matr[i][i];
			res.matr[i][j] = res.matr[i][j] / obj.matr[i][i];
		}
		for (int k = i + 1; k < order; k++)
		{
			for (int j = 0; j < order; j++)
			{
				obj.matr[k][j] = obj.matr[k][j] - obj.matr[i][j] * obj.matr[k][i];;
				res.matr[k][j] = res.matr[k][j] - res.matr[i][j] * obj.matr[k][i];;
			}
		}
	}
	for (int j = 0; j < order; j++)
	{
		obj.matr[order - 1][j] = obj.matr[order - 1][j] / obj.matr[order - 1][order - 1];
		res.matr[order - 1][j] = res.matr[order - 1][j] / obj.matr[order - 1][order - 1];
	}
	for (int i = order - 1; i > 0; i--)
		for (int k = i - 1; k >= 0; k--)
			for (int j = 0; j < order; j++)
				res.matr[k][j] = res.matr[k][j] - res.matr[i][j] * obj.matr[k][i];
	return res;
}


//det1
/*Matrix<T, order> obj;
	T res = 1;
	for (int i = 0; i < order - 1; i++)
	{
		if (!obj.matr[i][i])
			res = res * -1;
		int tmp = i;
		while (obj.matr[tmp][i] == 0 && tmp < order)
			tmp++;
		if (tmp == order)
		{
			res = 0;
			return res;
		}
		for (int j = 0; j < order; j++)
		{
			T tmpMean = obj.matr[i][j];
			obj.matr[i][j] = obj.matr[tmp][j];
			obj.matr[tmp][j] = tmpMean;
		}
		for (int k = i + 1; k < order; k++)
		{
			T koef = obj.matr[k][i] / obj.matr[i][i];
			for (int j = i; j < order; j++)
				obj.matr[k][j] = obj.matr[k][j] - obj.matr[i][j] * koef;
		}
		res = res * obj.matr[i][i];
	}
	return res * obj.matr[order - 1][order - 1];*/


//det2
/*Matrix<T, order> obj;
	T res = 1;
	int k = 0;
	for (int i = 0; i < order - 2; i++)
	{
		if (obj.matr[i][i] = 0)
			res = res * (-1);
		int tmp = i;
		while ((obj.matr[tmp][i] == 0) && (tmp <= order - 1)) //and
			tmp++;
		if (tmp > order - 1)
		{
			res = 0;
			break;
		}
		for (int j = 0; j < order - 1; j++)
		{
			T tmp1 = obj.matr[i][j];
			obj.matr[i][j] = obj.matr[tmp][j];
			obj.matr[tmp][j] = tmp1;
		}
		for (int k = i + 1; i < order - 1; i++)
		{
			T cur = obj.matr[k][i] / obj.matr[i][i];
			for (int j = i; j < order - 1; j++)
			{
				obj.matr[k][j] = obj.matr[k][j] - obj.matr[i][j] * cur;
			}
		}
		res = res * obj.matr[i][i];
	}
	return res * obj.matr[order - 1][order - 1];*/


//det3
/*	Matrix<T, order> obj;
	T res = 1;
	const double EPS = 1E-9;
	for (int i = 0; i < order; ++i)
	{
		int k = i;
	for (int j = i + 1; j < order; ++j)
		if (abs(obj.matr[j][i]) > abs(obj.matr[k][i]))
			k = j;
	if (abs(obj.matr[k][i]) < EPS)
	{
		res = 0;
		break;
	}
	swap(obj.matr[i], obj.matr[k]);
	if (i != k)
		res = -res; res *= obj.matr[i][i];
	for (int j = i + 1; j <= order; ++j) 
		obj.matr[i][j] /= obj.matr[i][i];
	for (int j = 0; j < order; ++j)
		if (j != i && abs(obj.matr[j][i]) > EPS)
			for (int k = i + 1; k < order; ++k)
				obj.matr[j][k] -= obj.matr[i][k] * obj.matr[j][i];
	}
	return res;*/