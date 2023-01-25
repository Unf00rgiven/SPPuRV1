#include "Matrix2D.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Matrix2D::Matrix2D(int rows, int cols, int range) : rows(rows), cols(cols)
{
	// ZA URADITI:
	// Zauzeti memoriju za matricu dimenzija rows*cols
	mat = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		mat[i] = new int[cols];
	}
	// Matricu inicijalizovati nasumičnim vrednostima u opsegu [0, range)
	for (int i = 0; i < rows; i++)
	{
		for (int k = 0; k < cols; k++)
		{
			mat[i][k] = rand() % range;
		}
	}
}

void Matrix2D::print()
{
	// ZA URADITI:
	// Odštampati sadržaj matrice na ekran
	for (int i = 0; i < rows; i++)
	{
		for (int k = 0; k < cols; k++)
		{
			cout << mat[i][k] << "	";
		}
		cout << endl;
	}
}

void Matrix2D::process()
{
	// ZA URADITI:
	// Realizovati zadatu obradu nad matricom
	int suma = 0;

	for (int i = 0; i < rows; i++)
	{
		if (i % 2 != 0)
		{
			for (int k = 2; k < cols; k+=3)
			{
				suma += mat[i][k];
			}
		}
		
	}
	cout << endl << "Suma:" << suma << endl;
}

Matrix2D::~Matrix2D()
{
	// ZA URADITI:
	// Osloboditi zauzetu memoriju
	for (int i = 0; i < rows; i++)
	{
		delete[] mat[i];
	}
	delete[] mat;
	cout << "Oslobodjena memorija zauzeta matricom mat2D" << endl;

}
