#pragma once
#include "Matrix.h"

class Matrix1D : public Matrix
{
	
public:
	Matrix1D(int rows, int cols, int range);
	void print();
	void process();
	~Matrix1D();

private:
	int rows;
	int cols;
	
	// ZA URADITI: 
	// Napisati definiciju polja koje predstavlja matricu
	int* mat1D;
};

