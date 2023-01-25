#include "MatrixVec.h"
#include <cstdlib>
#include <iostream>


MatrixVec::MatrixVec(int rows, int cols, int range)
{
	// ZA URADITI:
	// Zauzeti memoriju za matricu dimenzija rows*cols
	// Matricu inicijalizovati nasumičnim vrednostima u opsegu [0, range)
	int broj;

	for (int i = 0; i < rows; i++)
	{
		vector<int> kolone;
		for (int k = 0; k < cols; k++)
		{
			broj = rand() % range;
			kolone.push_back(broj);
		}
		matvec.push_back(kolone);
	}
}

void MatrixVec::print()
{
	// ZA URADITI:
	// Odštampati sadržaj matrice na ekran
	int rows = matvec.size();
	int cols = matvec[0].size();

	for (int i = 0; i < rows; i++)
	{
		for (int k = 0; k < cols; k++)
		{
			cout << matvec[i][k] << "	";
		}
		cout << endl;
	}
}

void MatrixVec::process()
{
	// ZA URADITI:
	// Realizovati zadatu obradu nad matricom
	int rows = matvec.size();
	int cols = matvec[0].size();
	int suma = 0;

	for (int i = 0; i < rows; i++)
	{
		if (i % 2 != 0)
		{
			for (int k = 2; k < cols; k += 3)
			{
				suma += matvec[i][k];
			}
		}

	}
	cout << endl << "Suma:" << suma << endl << endl;
}

