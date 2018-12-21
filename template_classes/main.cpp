#include <iostream>
#include "Fraction.h"
#include "Matrix.h"
#include "Polynom.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
	// Fraction
	/*Fraction<int> first;
	cin >> first;
	cout << "first = " << first << endl;

	Fraction<int> second;
	cin >> second;
	cout << "second = " << second << endl;

	cout << "first + second = " << first + second << endl;
	cout << "first - second = " << first - second << endl;
	cout << "first * second = " << first * second << endl;
	cout << "first / second = " << first / second << endl;*/


	// Matrix
	/*Matrix<double, 2> myMatr1;
	cin >> myMatr1;
	cout << "first matrix:" << endl << myMatr1 << endl; // << myMatr1.determinant() << endl << myMatr1.inverse();

	Matrix<double, 2> myMatr2;
	cin >> myMatr2;
	cout << "second matrix:" << endl << myMatr2 << endl;

	cout << "myMatr1 + myMatr2:" << endl << myMatr1 + myMatr2 << endl;
	cout << "myMatr1 - myMatr2:" << endl << myMatr1 - myMatr2 << endl;
	cout << "myMatr1 * myMatr2:" << endl << myMatr1 * myMatr2 << endl;
	cout << endl;*/

	// Polynom
	map<int, int> mp1 = {{2, 4}, {3, 4}}; // 4x^2 + 4x^3
	map<int, int> mp2 = {{2, 4}}; // 4x^2
	Polynom<int> myPoly1(mp1), myPoly2(mp2);
	cout << "myPoly1(x) = " << myPoly1 << endl;
	cout << "myPoly2(x) = " << myPoly2 << endl;
	cout << "myPoly1 + myPoly2 = " << myPoly1 + myPoly2 << endl;
	cout << "myPoly1 - myPoly2 = " << myPoly1 - myPoly2 << endl;
	cout << "myPoly1 * myPoly2 = " << myPoly1 * myPoly2 << endl;
	cout << "myPoly1 / myPoly2 = " << myPoly1 / myPoly2 << endl;
	cout << "myPoly1 % myPoly2 = " << myPoly1 % myPoly2 << endl;
	cout << "myPoly1(5) = " << myPoly1.pointValue(5) << endl;
	cout << "myPoly1'(x) = " << myPoly1.differentiate() << endl;
	//cout << "myPoly1(myPoly2) = " << myPoly1.superposition(myPoly2) << endl;
	//map<int, Fraction<int>> mp3 = {{0, fract1}, {1, fract2}, {2, fract3}}, mp4 = {{0, fract2}, {1, fract3}};
	
	system("pause");
	return 0;
}