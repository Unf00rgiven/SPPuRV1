#include <iostream>
#include <omp.h>

using namespace std;

void print1()
{
	for (int i = 0; i < 100; i++)
	{
		// This is critical section
		cout << "Crvena";
		cout << " Zvezda";
		cout << " je";
		cout << " prvak";
		cout << " sveta! ";
		cout << endl;
		
	}
}

void print2()
{
	int i;
	for (i = 0; i < 100; i++)
	{
		// This is critical section
		cout << "Priprema";
		cout << " vezbe";
		cout << " iz ";
		cout << " SPPuRV ";
		cout << endl;
		
	}
}

void print3()
{
	int i;
	for (i = 0; i < 100; i++)
	{
		// This is critical section
		cout << "Danas";
		cout << " je";
		cout << " lep";
		cout << " i";
		cout << " suncan";
		cout << " dan ";
		cout << endl;
		
	}
}



int main()
{
	cout << "Example 5 - Parallel" << endl;

	#pragma omp parallel sections num_threads(3)
	{
		#pragma omp section
		print1();

		#pragma omp section
		print2();

		#pragma omp section
		print3();
	}

	return 0;
}

