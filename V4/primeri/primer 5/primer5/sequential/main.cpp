#include <iostream>
#include <omp.h>

using namespace std;

void print1()
{
	for (int i = 0; i < 100; i++)
	{
		cout << "Crvena";
		cout << " Zvezda";
		cout << " je";
		cout << " prvak";
		cout << " sveta!";
		cout << endl;
	}
}

void print2()
{
	int i;
	for (i = 0; i < 100; i++)
	{
		cout << "Priprema";
		cout << " vezbe";
		cout << " iz ";
		cout << " SPPuRV";
		cout << endl;
	}
}

void print3()
{
	int i;
	for (i = 0; i < 100; i++)
	{
		cout << "Danas";
		cout << " je";
		cout << " lep";
		cout << " i";
		cout << " suncan";
		cout << " dan";
		cout << endl;
	}
}


int main()
{
	cout << "Example 5 - Sequential" << endl;

	print1();
	print2();
	print3();

	return 0;
}

