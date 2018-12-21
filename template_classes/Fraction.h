#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Fraction
{
	/*static_assert(std::is_same<T, int>::value || std::is_same<T, char>::value || 
	std::is_same<T, unsigned char>::value,L"недопустимый тип");*/
public:
	// Constructors === Конструкторы
	Fraction();
	Fraction(const T);
	Fraction(const T Tnum, const T Tdenom);

	// Overloadings === Перегрузки
	friend istream& operator>> <T>(istream&, Fraction&);
	friend ostream& operator<< <T>(ostream&, const Fraction&);
	
	Fraction<T> operator+(const Fraction<T>&) const;
	Fraction<T> operator-(const Fraction<T>&) const;
	Fraction<T> operator*(const Fraction<T>&) const;
	Fraction<T> operator/(const Fraction<T>&) const;
	Fraction<T> operator*(int); // multiply by number === умножение на число
	bool operator==(int);
	bool operator!=(int);

	// Euclidean algorithm === Алгоритм Евклида
	T gcd(T, T);

private:
	T num; // numerator of the fraction === числитель дроби
	T denom; // denominator of the fraction === знаменатель дроби
};


// Constructors === Конструкторы
template <typename T>
Fraction<T>::Fraction() = default;

template<typename T>
Fraction<T>::Fraction(const T n)
{
	this->num = n;
	this->denom = 1;
}

template<typename T>
Fraction<T>::Fraction(const T Tnum, const T Tdenom)
{
	this->num = Tnum;
	this->denom = Tdenom;
}

template <typename T>
istream& operator>>(istream &is, Fraction<T>& F)
{
	is >> F.num >> F.denom;
	if (!F.denom)
	{
		cout << "Нулевой знаменатель.";
		exit(-4);
	}
	T tmp = F.gcd(F.num, F.denom);
	F.num /= tmp;
	F.denom /= tmp;
	return is;
}

template <typename T>
ostream &operator<<(ostream &os, const Fraction<T>& F)
{
	if (!F.num) // 0/a = 0
	{
		os << "0";
		return os;
	}
	if (!(F.num % F.denom)) // 2a/a = 2
	{
		os << F.num / F.denom;
		return os;
	}
	if (F.num > 0 && F.denom < 0) // 1/-3 = -1/3
	{
		os << -F.num << "/" << -F.denom;
		return os;
	}
	if (F.num < 0 && F.denom < 0) // -1/-3 = 1/3
	{
		os << -F.num << "/" << -F.denom;
		return os;
	}
	os << F.num << "/" << F.denom;
	return os;
}

template <typename T> 
Fraction<T> Fraction<T>::operator+(const Fraction<T>& F) const
{
	Fraction<T> obj;
	if (this->denom == F.denom)
	{
		obj.num = this->num + F.num;
		obj.denom = this->denom;
	}
	else
	{
		obj.num = this->num*F.denom + F.num*this->denom;
		obj.denom = this->denom*F.denom;
	}
	T tmp = obj.gcd(obj.num, obj.denom);
	obj.num /= tmp;
	obj.denom /= tmp;
	return Fraction<T>(obj.num, obj.denom);
}

template <typename T>
Fraction<T> Fraction<T>::operator-(const Fraction<T>& F) const
{
	Fraction<T> obj;
	if (this->denom == F.denom)
	{
		obj.num = this->num - F.num;
		obj.denom = this->denom;
	}
	else
	{
		obj.num = this->num*F.denom - F.num*this->denom;
		obj.denom = this->denom*F.denom;
	}
	T tmp = obj.gcd(obj.num, obj.denom);
	obj.num /= tmp;
	obj.denom /= tmp;
	return Fraction<T>(obj.num, obj.denom);
}

template <typename T>
Fraction<T> Fraction<T>::operator*(const Fraction<T>& F) const
{
	Fraction<T> obj;
	obj.num = this->num*F.num;
	obj.denom = this->denom*F.denom;
	T tmp = obj.gcd(obj.num, obj.denom);
	obj.num /= tmp;
	obj.denom /= tmp;
	return Fraction<T>(obj.num, obj.denom);
}

template <typename T>
Fraction<T> Fraction<T>::operator/(const Fraction<T>& F) const
{
	Fraction<T> obj;
	if ((!F.denom)||(!this->num))
	{
		cout << "Деление на ноль!";
		exit(-3);
	}
	obj.num = this->num*F.denom;
	obj.denom = this->denom*F.num;
	T tmp = obj.gcd(obj.num, obj.denom);
	obj.num /= tmp;
	obj.denom /= tmp;
	return Fraction<T>(obj.num, obj.denom);
}

template<typename T>
Fraction<T> Fraction<T>::operator*(int alpha)
{
	this->num = this->num*alpha;
	return *this;
}

// Euclidean algorithm === алгоритм Евклида
template <typename T>
T Fraction<T>::gcd(T a, T b)
{
	while (b)
	{
		a %= b;
		swap(a, b);
	}
	return a;
}

template<typename T>
bool Fraction<T>::operator==(int n)
{
	if (!(num % denom) && (num / denom == n))
		return true;

	return false;
}

template<typename T>
bool Fraction<T>::operator!=(int n)
{
	if ((num % denom == 0) && (num / denom == n))
		return false;

	return true;
}