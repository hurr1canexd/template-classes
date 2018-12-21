#pragma once

#include <map>
#include <iterator>

using namespace std;

template<typename T>
class Polynom
{
private:
	map<int, T> polynom;
public:
	// Конструкторы
	Polynom() = default;
	Polynom(map<int, T>&);
	Polynom(const Polynom&);
	
	// Перегрузки
	Polynom operator+(const Polynom&) const;
	Polynom operator-(const Polynom&) const;
	Polynom operator*(const Polynom&) const;
	Polynom operator/(const Polynom&) const;
	Polynom operator%(const Polynom&);
	Polynom& operator=(const Polynom&);

	friend ostream& operator<< <T>(ostream&, const Polynom&);

	void addMonom(T, int);
	Polynom differentiate();
	T pointValue(T);
	Polynom superposition(Polynom);
	
	friend Polynom operator*(const Polynom& P, const int num)
	{
		Polynom<T> res;
		for (auto it : P.polynom)
			res.addMonom(it.second * num, it.first);
		return res;
	}
};

template<typename T>
Polynom<T>::Polynom(map<int, T> &mp)
{
	for (auto it : mp)
		if (it.second != 0)
			polynom[it.first] = it.second;
}

// Конструктор копирования
template<typename T>
Polynom<T>::Polynom(const Polynom& P)
{
	polynom = P.polynom;
}
//operator=
template<typename T>
Polynom<T> & Polynom<T>::operator=(const Polynom<T>& P)
{
	polynom = P.polynom;
	return *this;
}

//operator+
template<typename T>
Polynom<T> Polynom<T>::operator+(const Polynom<T>& P) const
{
	Polynom<T> res(*this);
	for (auto it : P.polynom)
		res.addMonom(it.second, it.first);
	return res;
}

//operator-
template<typename T>
Polynom<T> Polynom<T>::operator-(const Polynom<T>& P) const
{
	Polynom<T> res(P * -1);
	res = res + *this;
	return res;
}

//operator*
template<typename T>
Polynom<T> Polynom<T>::operator*(const Polynom<T>& P) const
{
	Polynom<T> res;
	for (auto it1 : this->polynom)
	{
		for (auto it2 : P.polynom)
		{ 
			res.addMonom(it1.second * it2.second, it1.first + it2.first);
		}
	}
	return res;
}

template<typename T>
Polynom<T> Polynom<T>::operator/(const Polynom<T>& P) const
{
	Polynom<T> divisionPoly(*this);
	Polynom<T> res;
	auto inp_it = P.polynom.end();
	--inp_it;
	while (true)
	{
		if (divisionPoly.polynom.empty())
		{
			T var = 0;
			res.addMonom(0, var);
			return res;
		}
		auto div_it = divisionPoly.polynom.end();
		--div_it;
		if (div_it->first < inp_it->first)
			return res;
		else
		{
			for (auto it = P.polynom.begin(); it != inp_it; ++it)
			{
				T num = -1;
				divisionPoly.addMonom(num * it->second * div_it->second / inp_it->second, it->first + div_it->first - inp_it->first);
			}
			res.addMonom(div_it->second / inp_it->second, div_it->first - inp_it->first);
			divisionPoly.polynom.erase(div_it);
		}
	}
}

//operator%
template<typename T>
Polynom<T> Polynom<T>::operator%(const Polynom<T>& P)
{
	Polynom<T> res(*this);
	auto inp_it = P.polynom.end();
	--inp_it;
	while (true)
	{
		if (res.polynom.empty())
		{
			T var = 0;
			res.addMonom(0, var);
			return res;
		}
		auto res_it = res.polynom.end();
		--res_it;
		if (res_it->first < inp_it->first)
			return res;
		else
		{
			for (auto it = P.polynom.begin(); it != inp_it; ++it)
			{
				T num = -1;
				res.addMonom(num * it->second * res_it->second / inp_it->second, it->first + res_it->first - inp_it->first);
			}
			res.polynom.erase(res_it);
		}
	}
}

// Добавить моном
template<typename T>
void Polynom<T>::addMonom(T item, int degree)
{
	if (polynom.count(degree))
	{
		polynom[degree] = polynom[degree] + item;
	}
	else
		polynom[degree] = item;

	if (!polynom[degree])
	{
		auto it = polynom.find(degree);
		polynom.erase(it);
	}
}

// Производная
template<typename T>
Polynom<T> Polynom<T>::differentiate()
{
	Polynom<T> res;
	for (auto it : polynom)
	{
		if (it.first != 0)
			res.addMonom(it.second * it.first, it.first - 1);
		else 
		{
			T num = 0;
			res.addMonom(num, 0);
		}
	}
	return res;
}

// Значение в точке
template<typename T>
T Polynom<T>::pointValue(T x)
{
	if (!polynom.empty())
	{
		T sum = 0, pw_val;
		for (auto it : polynom)
		{
			if (it.first != 0)
				pw_val = x;
			else
				pw_val = 1;
			for (int i = it.first - 1; i > 0; i--)
				pw_val = pw_val * x;
			sum += pw_val * it.second;
		}
		return sum;
	}
	else
	{
		return 0;
	}
}

template<typename T>
Polynom<T> Polynom<T>::superposition(Polynom<T> P)
{
	Polynom<T> res;
	for (auto it : polynom)
	{
		if (it.first > 0)
		{
			Polynom<T> pwPolу(P), coeffsPoly;
			for (int i = it.first - 1; i > 0; i--)
				pwPolу = pwPolу * P;
			coeffsPoly.addMonom(it.second, 0);
			res = res + coeffsPoly * pwPolу;
		}
		else if (it.first == 0)
			res.addMonom(it.second, 0);
	}
	return res;
}

// Перегрузка оператора вставки в поток  
template<typename T>
ostream& operator<<(ostream& os, const Polynom<T>& P)
{
	if (P.polynom.empty())
		os << 0;
	else
	{
		auto iter = P.polynom.end();
		iter--;
		for (auto it = P.polynom.begin(); it != iter; ++it)
		{
			if (it->first == 0)
				os << it->second << " + ";
			else
				if (it->first == 1)
					os << it->second << "x" << " + ";
				else
					os << it->second << "x^" << it->first << " + ";
		}
		if (iter->first == 0)
			os << iter->second;
		else
			if (iter->first == 1)
				os << iter->second << "x";
			else
				os << iter->second << "x^" << iter->first;
	}
	return os;
}