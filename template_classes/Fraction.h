#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Fraction
{
	//static_assert(std::is_same<T, int>::value || std::is_same<T, char>::value ||std::is_same<T, unsigned char>::value,L"недопустимый тип");
public:
	Fraction();
	Fraction(T);
	friend istream& operator>> <T>(istream&, Fraction&);
	friend ostream& operator<< <T>(ostream&, const Fraction&);
	Fraction<T> operator+(const Fraction<T>&);
	Fraction<T> operator-(const Fraction<T>&);
	Fraction<T> operator*(const Fraction<T>&);
	Fraction<T> operator/(const Fraction<T>&);
	Fraction<T> operator*(int); // multiply by number
	bool operator==(int);
	bool operator!=(int);

	T gcd(T, T);
	Fraction<T>(T Tnum, T Tdenom)
	{
		this->num = Tnum;
		this->denom = Tdenom;
	}

private:
	T num; // numerator of the fraction
	T denom; // denominator of the fraction
};

template <typename T>
Fraction<T>::Fraction() = default;

template<typename T>
inline Fraction<T>::Fraction(T n)
{
	this->num = n;
	this->denom = 1;
}

// const Fraction<T> ? https://msdn.microsoft.com/ru-ru/library/1z2f6c2k.aspx
template <typename T>
istream& operator>>(istream &is, Fraction<T> &F)
{
	is >> F.num >> F.denom;
	if (!F.denom) exit(-4); // тупа выходит погулять с кодом -4, если знаменатель равен нулю
	T tmp = F.gcd(F.num, F.denom);
	F.num /= tmp;
	F.denom /= tmp;
	return is;
}

template <typename T>
ostream &operator<<(ostream &os, const Fraction<T> &F)
{
	if (!F.num) // чтобы не было всяких дробей 0/4
	{
		os << "0";
		return os;
	}
	if (!(F.num % F.denom)) // чтобы вместо всяких 3/3 было 1
	{
		os << F.num / F.denom;
		return os;
	}
	os << F.num << "/" << F.denom;
	return os;
}

template <typename T> 
Fraction<T> Fraction<T>::operator+(const Fraction<T>& F)
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
Fraction<T> Fraction<T>::operator-(const Fraction<T>& F)
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
Fraction<T> Fraction<T>::operator*(const Fraction<T>& F)
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
Fraction<T> Fraction<T>::operator/(const Fraction<T>& F)
{
	Fraction<T> obj;
	if ((!F.denom)||(!this->num))
	{
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

template<typename T>
inline bool Fraction<T>::operator==(int n)
{
	if ((num % denom == 0) && (num / denom == n))
		return true;

	return false;
}

template<typename T>
inline bool Fraction<T>::operator!=(int n)
{
	if ((num % denom == 0) && (num / denom == n))
		return false;

	return true;
}

template <typename T>
T Fraction<T>::gcd(T a, T b) // Euclidean algorithm
{
	if (!b) exit(-5);
	while (a > 0 && b > 0)
	{
		if (a > b)
			a -= b;
		else
			b -= a;
	}
	return a + b;
}