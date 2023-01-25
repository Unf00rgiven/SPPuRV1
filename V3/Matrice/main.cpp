#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Matrix1D.h"
#include "Matrix2D.h"
#include "MatrixVec.h"

using namespace std;

#define NUMBER_RANGE		10

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Niste uneli potrebne argumente za pokretanje programa!" << endl;
		cout << "Argumenti komandne linije treba da budu:" << endl;
		cout << "1. N dimenzija matrice" << endl;
		cout << "2. M dimenzija matrice" << endl;
		exit(-1);
	}

	// inicijalizacija generatora nasumičnih brojeva
	srand(unsigned int(time(NULL)));

	int rowNum = atoi(argv[1]);
	int colNum = atoi(argv[2]);

	// a)
	cout << endl << endl << "a) Matrix 1D representation" << endl ;

	// ZA URADITI:
	// Napraviti objekat klase Matrix1D

	Matrix1D mat1(rowNum, colNum, 5);
	
	// Pozvati metodu print nad objektom
	mat1.print();
	// Pozvati metodu process nad objektom
	mat1.process();
	
	//b)
	cout << endl << endl << "b) Matrix 2D representation" << endl;

	// ZA URADITI:
	// Napraviti objekat klase Matrix2D
	Matrix2D mat2(rowNum, colNum, 5);
	
	// Pozvati metodu print nad objektom
	mat2.print();
	// Pozvati metodu process nad objektom
	mat2.process();
	
	//c)
	cout << endl << endl << "c) Matrix vector of vector representation" << endl;

	// ZA URADITI:
	// Napraviti objekat klase MatrixVec
	MatrixVec mat3(rowNum, colNum, 5);

	// Pozvati metodu print nad objektom
	mat3.print();
	// Pozvati metodu process nad objektom
	mat3.process();

	return 0;
}

