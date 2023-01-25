#include <iostream>
#include <omp.h>

using namespace std;

int fib(int n)
{
	if (n < 2)
		return n;

	int x = fib(n - 1);
	int y = fib(n - 2);

	return (x + y);
}

int main(int argc, char* argv[])
{
	const int n = 20;

	double startTime = omp_get_wtime();
	int result = fib(n);
	double endTime = omp_get_wtime();

	cout << "Example 6 - Sequential" << endl;
	cout << "Run time: " << (endTime - startTime) * 1000 << "ms." << endl;

	cout << "Fibonacci of " << n << " is " <<  result << endl;

	return 0;
}
