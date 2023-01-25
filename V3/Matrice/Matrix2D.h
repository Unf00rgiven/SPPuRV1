#pragma once
#include "Matrix.h"

class Matrix2D : public Matrix
{

public:
	Matrix2D(int rows, int cols, int range);
	void print();
	void process();
	~Matrix2D();

private:
	int** mat;
	int rows;
	int cols;
	
	// ZA URADITI: 
	// Napisati definiciju polja koje predstavlja matricu
	
};

