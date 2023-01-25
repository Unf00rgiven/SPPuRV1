#include <iostream>
#include <omp.h>

using namespace std; 

long long  compute(int i)
{
	return i; // return a value computed from i
}

int main()
{
	long long n = 100000000;
	long long  total = 0;

	double startTime = omp_get_wtime();

	// Compute the sum of integers  1..n
	for (int i = 1; i <= n; ++i)
	{
		long long temp = compute(i);
		total += temp;
	}

	double endTime = omp_get_wtime();

	cout << "Example 4 - Sequential" << endl;
	cout << "Run time: " << (endTime - startTime) * 1000 << "ms." << endl;

	// the sum of the first n integers
	// should be n * (n + 1) / 2
	long long correct = (n * (n + 1)) / 2;

	if (total == correct)
	{
		cout << "Total (" << total << ") is correct" << endl;
	}
	else
	{
		cout << "Total (" << total << ") is WRONG, should be " << correct << endl;
	}

	return 0;
}

