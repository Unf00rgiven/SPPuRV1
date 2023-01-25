#include "Matrix1D.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Matrix1D::Matrix1D(int rows, int cols, int range) : rows(rows), cols(cols)
{
	// ZA URADITI:
	// Zauzeti memoriju za matricu dimenzija rows*cols
	int dimenzija = rows * cols;
	mat1D = new int[dimenzija];
	// Matricu inicijalizovati nasumičnim vrednostima u opsegu [0, range)
	for (int i = 0; i < dimenzija; i++)
	{
		mat1D[i] = rand() % range;
	}

}

void Matrix1D::print()
{
	// ZA URADITI:
	// Odštampati sadržaj matrice na ekran
	int dimenzija = rows * cols;
	for (int i = 0; i < dimenzija; i++)
	{
		cout << mat1D[i] << endl;
	}

}

void Matrix1D::process()
{
	// ZA URADITI:
	// Realizovati zadatu obradu nad matricom
	int suma=0;
	int dimenzija = rows * cols;
	int kolona = 0;
	
	for (int i= 0; i < dimenzija; i+=cols)
	{ 
		if (kolona % 2 != 0)
		{
			for (int j=1; j <= cols; j++)
			{	
				if (j % 3 == 0)
				{
					int k = i + j -1;
					suma += mat1D[k];
				}
			}
		}
		kolona++;
	}

	cout << endl << "Suma:" << suma << endl;
	
}

Matrix1D::~Matrix1D()
{
	// ZA URADITI:
	// Osloboditi zauzetu memoriju
	delete[] mat1D;
	cout << "Oslobodjena memorija zauzeta matricom mat1D" << endl;
}
