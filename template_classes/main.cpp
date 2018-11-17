#include <iostream>
#include <cstdlib> // for system("pause")
#include "Fraction.h"
#include "Matrix.h"
#include "Polynom.h"

using namespace std;

int main()
{
	// Fraction
	/*Fraction<int> first;
	cin >> first;
	cout << first << endl;

	Fraction<int> second;
	cin >> second;
	cout << second << endl;

	cout << first + second << endl;
	cout << first - second << endl;
	cout << first * second << endl;
	cout << first / second << endl;*/

	// Matrix
	Matrix<double, 3> myMatr1;
	cin >> myMatr1;
	cout << myMatr1 << endl << myMatr1.determinant() << endl << myMatr1.inverse();

	// Polynom
	/*Polynom<int> frPoly1, frPoly2;
	cin >> frPoly1; 
	cout << frPoly1 << endl;
	cin >> frPoly2;
	cout << frPoly2 << endl;
	cout << "diff" << frPoly1.differentiation() << endl;
	cout << "in the point" << frPoly1.solve(2) << endl;*/

	system("pause");
	return 0;
}