#pragma once

#include <vector>
#include <iterator>
#include <algorithm>
#include <map>
#include <cmath>
#include "Fraction.h"

using namespace std;
template <class T>
class Polynom
{
private:
	map<int, T> poly;
	void isZero();

public:
	Polynom();
	Polynom(int);
	Polynom(int, T);
	Polynom(const Polynom<T>&);
	~Polynom() = default;

	Polynom<T> operator+ (const Polynom<T>&) const;
	Polynom<T> operator- (const Polynom<T>&) const;
	Polynom<T> operator* (const Polynom<T>&) const;
	Polynom<T> operator* (const T) const;
	Polynom<T> operator/ (const Polynom<T>&) const;
	Polynom<T>& operator= (const Polynom<T>&);

	void add(int, const T&);	// перезапись элемента
	void addP(int, const T&);	// добавление к текущему
	Polynom<T> differentiation() const;
	T solve(T x) const;

	template<class U>
	friend Fraction<U> pow(const Fraction<U>&, int);

	template<class U>
	friend Polynom<U> pow(const Polynom<U>&, int);

	template<class T>
	friend Polynom<T> operator* (const T&, const Polynom<T>&);

	template<class U>
	friend ostream& operator<<(ostream&, const Polynom<U>&);

	template<class U>
	friend istream& operator>>(istream&, Polynom<U>&);
};

template<class T>
Polynom<T>::Polynom()
{
	poly.insert(pair<int, T>(0, T(0))); // кладёт степень и коэффициент в полином
}

template<class T>
Polynom<T>::Polynom(int degree)
{
	poly.insert(pair<int, T>(degree, T(0))); // то же, но степень введена
}

template<class T>
Polynom<T>::Polynom(int degree, T koef)
{
	poly.insert(pair<int, T>(degree, koef)); // то же, но всё введено
}

template<class T>
Polynom<T>::Polynom(const Polynom<T>& P)
{
	this->poly = P.poly;
}

template<class T>
inline Polynom<T> Polynom<T>::operator+(const Polynom<T>& P) const
{
	Polynom<T> newpoly;
	newpoly = *this;		//кладём первый полином

	for (auto iter = P.poly.begin(); iter != P.poly.end(); ++iter)
	{
		auto itfind = this->poly.find(iter->first);
		if (itfind != this->poly.end())		//ищем одинаковые степени
			newpoly.poly[iter->first] = iter->second + itfind->second;
		else
			newpoly.poly.insert(pair<int, T>(iter->first, iter->second));
	}

	newpoly.isZero();
	return newpoly;
}

template<class T>
Polynom<T> Polynom<T>::operator-(const Polynom<T>& P) const
{
	Polynom<T> newpoly;
	newpoly = *this;		//кладём первый полином

	for (auto iter = P.poly.begin(); iter != P.poly.end(); ++iter)
	{
		auto itfind = this->poly.find(iter->first);
		if (itfind != this->poly.end())		//ищем одинаковые степени
			newpoly.poly[iter->first] = itfind->second - iter->second;
		else
			newpoly.poly.insert(pair<int, T>(iter->first, iter->second * (-1)));
	}

	newpoly.isZero();
	return newpoly;
}

template<class T>
Polynom<T> Polynom<T>::operator* (const Polynom<T>& P) const
{
	Polynom<T> newpoly;

	for (auto iter = this->poly.begin(); iter != this->poly.end(); ++iter)
		for (auto iter2 = P.poly.begin(); iter2 != P.poly.end(); ++iter2)
		{
			newpoly.addP(iter->first + iter2->first, iter->second * iter2->second);
		}

	newpoly.isZero();
	return newpoly;
}

template<class T>
Polynom<T> Polynom<T>::operator*(const T num) const
{
	Polynom<T> newpoly(*this);

	for (auto iter = newpoly.poly.begin(); iter != newpoly.poly.end(); ++iter)
		newpoly.poly[iter->first] = iter->second * num;

	newpoly.isZero();
	return newpoly;
}

template<class T>
Polynom<T> operator*(const T &num, const Polynom<T> &P)
{
	Polynom<T> newpoly(P);

	for (auto iter = newpoly.poly.begin(); iter != newpoly.poly.end(); ++iter)
		newpoly.poly[iter->first] = num * iter->second;

	newpoly.isZero();
	return newpoly;
}


template<class T>
Polynom<T> Polynom<T>::operator/(const Polynom<T>& P) const
{
	if ((P.poly.size() == 1) && (P.poly.find(0)->second == 0))	//проверка, что второй полином не равен 0 (состоит из 0*x^0)
		exit(7);

	Polynom<T> temp(*this), res;

	auto itPol = P.poly.end();
	--itPol;	// последний элемент

	while (true)
	{
		if (temp.poly.empty())
			return res;

		auto itTemp = temp.poly.end();
		--itTemp;	// последний элемент 

		if (itTemp->first < itPol->first)	// знаменатель более высокого порядка
			return res;	// возвращаем 0 (в случае, если true сразу)
		else
		{
			for (auto iter = P.poly.begin(); iter != itPol; iter++)
			{
				T num;
				num = -1;

				temp.addP(iter->first + itTemp->first - itPol->first, num * iter->second * itTemp->second / itPol->second);
			}

			res.addP(itTemp->first - itPol->first, itTemp->second / itPol->second);
			temp.poly.erase(itTemp->first);
		}
	}
}


template<class T>
Polynom<T>& Polynom<T>::operator=(const Polynom<T> &P)
{
	this->poly = P.poly;

	return *this;
}

// добавляем новый или переписываем имеющийся
template<class T>
void Polynom<T>::add(int key, const T &num)
{
	auto itfind = this->poly.find(key);
	if (itfind != this->poly.end())
		this->poly[key] = num;
	else
		this->poly.insert(pair<int, T>(key, num));
	return;
}

template<class T>
void Polynom<T>::addP(int key, const T &num)
{
	auto itfind = this->poly.find(key);
	if (itfind != this->poly.end())
		this->poly[key] += num;
	else
		this->poly.insert(pair<int, T>(key, num));

	return;
}

template<class T>
Polynom<T> Polynom<T>::differentiation() const
{
	Polynom<T> newpoly;
	for (auto iter = this->poly.begin(); iter != this->poly.end(); ++iter)
	{
		if (iter->first == 0)	// степень = 0
			continue;

		newpoly.addP(iter->first - 1, iter->second * iter->first);
	}

	return newpoly;
}

template<class T>
T Polynom<T>::solve(T x) const
{
	T res;
	res = 0;

	for (auto iter = this->poly.begin(); iter != this->poly.end(); ++iter)
		res += iter->second * pow(x, iter->first);

	return res;
}

template<class T>
void Polynom<T>::isZero()
{
	vector<int> save;
	for (auto iter = this->poly.begin(); iter != this->poly.end(); ++iter)
	{
		if ((iter->second == 0) && (iter->first != 0))
			save.push_back(iter->first);
	}

	for (int i = 0; i < save.size(); i++)
		this->poly.erase(save[i]);

	return;
}

template<class T>
ostream& operator<<(ostream& os, const Polynom<T>& P)
{
	if (P.poly.size() == 0)
	{
		exit(-9);
	}
	else
		if (P.poly.size() == 1)
		{
			auto iter = P.poly.begin();
			os << iter->second;
			return os;
		}

	Polynom<T> copy(P);	// копируем для вывода
	if ((copy.poly.find(0) != copy.poly.end()) && (copy.poly.find(0)->second == 0))  //есть 0*x^0
		copy.poly.erase(0);

	int counter = copy.poly.size();
	for (auto iter = copy.poly.rbegin(); iter != copy.poly.rend(); ++iter)
	{
		if (iter->second != 0)
		{
			if (iter->first == 0)
				os << iter->second;
			else
				os << iter->second << "*x^" << iter->first;
		}
		else
		{
			--counter;
			continue;
		}

		if (counter > 1)
			os << " + ";

		--counter;
	}
	return os;
}


template<class T>
istream& operator>>(istream& in, Polynom<T>& P)
{
	P.poly.clear();
	T koef;
	koef = 0;
	int degree = 0;
	P.poly.insert(pair<int, T>(degree, koef));	//всегда присутствует нулевая степень

	while (true)
	{
		in >> koef >> degree;

		if (in.fail())	// "плохой символ"
			break;

		if ((koef != 0) || (degree == 0))
			P.add(degree, koef);

		if (degree == 0)	// нулевая степень - остановка ввода
			break;
	}

	return in;
}

template<class T, class U>
Fraction<U> pow(const Fraction<U> &arg, int degree)
{
	if (degree == 0)
		return Fraction<U>(1);
	else
		if (degree < 0)
		{
			Fraction<U> newarg(arg);
			newarg = 1 / newarg;
			for (int i = degree; i > 1; i--)
				newarg *= newarg;

			return newarg;
		}
		else
			if (degree > 0)
			{
				Fraction<U> newarg(arg);

				for (int i = 1; i < degree; i++)
					newarg = newarg * arg;

				return newarg;
			}
}

template<class T>
Polynom<T> pow(const Polynom<T> &arg, int degree)
{
	if (degree == 0)
		return Polynom<T>(0, pow(T(1), 0));
	else
		if (degree < 0)
		{
			throw std::invalid_argument("polynom to negative degree ");
			return Polynom<T>();
		}
		else
			if (degree > 0)
			{
				Polynom<T> newarg(arg);

				for (int i = 1; i < degree; i++)
					newarg = newarg * arg;

				return newarg;
			}
}
