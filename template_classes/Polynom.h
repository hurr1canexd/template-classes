#pragma once

#include <map>
#include <iterator>

using namespace std;

/*template <typename T>
class Polynom
{
public:
	// Constructors === Конструкторы
	Polynom() = default;
	Polynom(map<int, T>&);
	Polynom(const Polynom&);

	// Overloadings === Перегрузки
	Polynom operator+(const Polynom&);
	Polynom operator-(const Polynom&);
	Polynom operator*(const Polynom&);
	Polynom operator*(const int&);
	Polynom operator/(const Polynom&);
	Polynom operator%(const Polynom&);
	Polynom& operator=(const Polynom&);

	// Add monom === Добавить моном
	void addMonom(const T&, const int&);
	// Differentiate === Дифференцировать
	Polynom differentiate();
	// ----- Значение функции в точке -----
	T atX(const T&);
	// ----- Суперпозиция -----
	Polynom superposition(const Polynom&);

	// ===== Перегрузка оператора вставки в поток =====
	template<typename U>
	friend ostream& operator<< (ostream &, const Polynom<U>&);

private:
	// ===== Хэш: ключ-степень, значение-коэффициент =====
	map<int, T> polynom;
};



// ===== Конструкторы =====
template <typename T>
Polynom<T>::Polynom(map<int, T>& initmap)
{
	this->polynom = initmap;
}

template <typename T>
Polynom<T>::Polynom(const Polynom& other)
{
	this->polynom = other.polynom;
}

// operator+
template <typename T>
Polynom<T> Polynom<T>::operator+(const Polynom<T>& other)
{
	Polynom<T> result(*this);
	for (auto it : other.polynom)
		result.addMonom(it.second, it.first);
	return result;
}

// operator-
template <typename T>
Polynom<T> Polynom<T>::operator-(const Polynom<T>& other)
{
	Polynom<T> result(other * -1);
	result = *this + result;
	return result;
}

// operator*
template <typename T>
Polynom<T> Polynom<T>::operator*(const Polynom<T>& other)
{
	Polynom<T> result;
	for (auto it : this->polynom)
		for (auto jt : other.polynom)
			result.addMonom(it.second * jt.second, it.first + jt.first);
	return result;
}

// multiply by number
template <typename T>
Polynom<T> Polynom<T>::operator*(const int& num)
{
	Polynom<T> result;
	for (auto it : this->polynom)
		result.addMonom(it.second * num, it.first);
	return result;
}

// operator/
template<typename T>
Polynom<T> Polynom<T>::operator/(const Polynom<T>& other)
{
	Polynom<T> divident(*this), result;
	auto inp_it = other.polynom.end();
	--inp_it;
	while (true)
	{
		auto div_it = divident.polynom.end();
		--div_it;
		if (div_it->first < inp_it->first)
			return result;
		else
		{
			for (auto it = other.polynom.begin(); it != inp_it; ++it)
			{
				divident.addMonom(T(-1) * it->second * div_it->second / inp_it->second,
					it->first + div_it->first - inp_it->first);
			}
			result.addMonom(div_it->second / inp_it->second,
				div_it->first - inp_it->first);
			divident.polynom.erase(div_it);
		}
	}
}

// operator%
template <typename T>
Polynom<T> Polynom<T>::operator%(const Polynom<T>& other)
{
	Polynom<T> result(*this);
	auto inp_it = other.polynom.end();
	--inp_it;
	while (true)
	{
		auto res_it = result.polynom.end();
		--res_it;
		if (res_it->first < inp_it->first)
			return result;
		else
		{
			for (auto it = other.polynom.begin(); it != inp_it; ++it)
			{
				result.addMonom(T(-1) * it->second * res_it->second / inp_it->second,
					it->first + res_it->first - inp_it->first);
			}
			result.polynom.erase(res_it);
		}
	}
}

// operator=
template <typename T>
Polynom<T>& Polynom<T>::operator=(const Polynom<T>& other)
{
	this->polynom = other.polynom;
	return *this;
}


// Добавить моном
template <typename T>
void Polynom<T>::addMonom(const T& coef, const int& degree)
{
	if (this->polynom.count(degree))
		this->polynom[degree] = this->polynom[degree] + coef;
	else
		this->polynom[degree] = coef;

	if (polynom[degree] == T(0))
	{
		auto it = this->polynom.find(degree);
		this->polynom.erase(it);
	}
}

// Производная
template <typename T>
Polynom<T> Polynom<T>::differentiate()
{
	Polynom<T> result;
	for (auto it = this->polynom.begin(); it != this->polynom.end(); ++it)
	{
		if (0 != it->first)
			result.addMonom(it->second * it->first, it->first - 1);
	}
	return result;
}

// Значение функции в точке
template <typename T>
T Polynom<T>::atX(const T& num)
{
	if (this->polynom.empty())
		return T(0);
	T result(0), pw_val;
	for (auto it = this->polynom.begin(); it != this->polynom.end(); ++it)
	{
		if (0 != it->first)
			pw_val = num;
		else
			pw_val = 1;
		for (int i = it->first - 1; i > 0; --i)
			pw_val = pw_val * num;
		result = result + pw_val * it->second;
	}
	return result;
}

// Суперпозиция
template <typename T>
Polynom<T> Polynom<T>::superposition(const Polynom<T>& inner)
{
	Polynom<T> result;
	for (auto it = this->polynom.begin(); it != this->polynom.end(); ++it)
	{
		if (it->first > 0)
		{
			Polynom<T> grPol(inner), coefPol;
			for (int i = it->first - 1; i > 0; --i)
				grPol = grPol * inner;
			coefPol.addMonom(it->second, 0);
			result = result + grPol * coefPol;
		}
		else
			result.addMonom(it->second, 0);
	}
	return result;
}

// Перегрузка оператора вывода
template <typename T>
ostream& operator<<(ostream& os, const Polynom<T>& pol)
{
	if (pol.polynom.empty())
		os << 0;
	else
	{
		auto it = pol.polynom.end();
		--it;
		for (auto jt = pol.polynom.begin(); jt != it; ++jt)
			if (jt->first == 0)
				os << jt->second << " + ";
			else
				if (jt->first == 1)
					os << jt->second << "x" << " + ";
				else
					os << jt->second << "x^" << jt->first << " + ";

		if (0 == it->first)
			os << it->second;
		else
			if (it->first == 1)
				os << it->second << "x";
			else
				os << it->second << "x^" << it->first;
	}
	return os;
}*/


#include<map>
#include<iterator>

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

	void addMonom(T, int);
	Polynom differentiate();
	void SetItems(map<int, T>&);
	map<int, T>& GetItems();
	T pointValue(T);
	Polynom superposition(Polynom);
	friend ostream& operator<< <T>(ostream&, const Polynom&);

	friend Polynom operator*(const int num, const Polynom& P)
	{
		Polynom<T> res;
		for (auto it : P.polynom) // I LOVE C++11 <3
			res.addMonom(it.second * num, it.first);
		return res;
	}

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
	T num; num = 0;
	for (auto it : mp)
		if (!(it.second == num))
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
	for (auto it1 : P.polynom)
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
	Polynom<T> divisPol(*this);
	Polynom<T> res;
	auto inp_it = P.polynom.end();
	--inp_it;
	while (true)
	{
		if (divisPol.polynom.empty())
		{
			T var; var = 0;
			res.addMonom(0, var);
			return res;
		}
		auto div_it = divisPol.polynom.end(); --div_it;
		if (div_it->first < inp_it->first)
			return res;
		else
		{
			for (auto it = P.polynom.begin(); it != inp_it; ++it)
			{
				T num = -1;
				divisPol.addMonom(num * it->second * div_it->second / inp_it->second, it->first + div_it->first - inp_it->first);
			}
			res.addMonom(div_it->second / inp_it->second, div_it->first - inp_it->first);
			divisPol.polynom.erase(div_it);
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
			T var; var = 0;
			res.addMonom(0, var);
			return res;
		}
		auto res_it = res.polynom.end(); --res_it;
		if (res_it->first < inp_it->first)
			return res;
		else
		{
			for (auto it = P.polynom.begin(); it != inp_it; ++it)
			{
				T num; num = -1;
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

	T nul; nul = 0;
	if (polynom[degree] == nul)
	{
		auto it = polynom.find(degree);
		polynom.erase(it);
	}
}
//Derivative
template<typename T>
Polynom<T> Polynom<T>::differentiate()
{
	Polynom<T> derPolynom;
	for (auto it : polynom)
	{
		if (it.first != 0)
			derPolynom.addMonom(it.second * it.first, it.first - 1);
		else 
		{
			T num = 0;
			derPolynom.addMonom(num, 0);
		}
	}
	return derPolynom;
}

//set map
template<typename T>
void Polynom<T>::SetItems(map<int, T>& m)
{
	polynom.clear();
	T num = 0;
	for (auto it : m)
		if (it.second != num)
			polynom[it.first] = it.second;
}

//get map
template<typename T>
map<int, T>& Polynom<T>::GetItems()
{
	return polynom;
}
//
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
			sum = sum + pw_val * it.second;
		}
		return sum;
	}
	else
	{
		//T val = 0;
		//return val;
		return 0;
	}
}

template<typename T>
Polynom<T> Polynom<T>::superposition(Polynom<T> P)
{
	Polynom<T> result;
	for (auto it : polynom)
	{
		if (it.first > 0)
		{
			Polynom<T> pwPol(P), coeffPol;
			for (int i = it.first - 1; i > 0; i--)
				pwPol = pwPol * P;
			coeffPol.addMonom(it->second, 0);
			result = result + pwPol * coeffPol;
		}
		else if (it.first == 0)
			result.addMonom(it.second, 0);
	}
	return result;
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