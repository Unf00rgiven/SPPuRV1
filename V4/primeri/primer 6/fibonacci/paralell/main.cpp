#include <iostream>
#include <omp.h>

using namespace std;


int fib_serial(int n)
{
	if (n < 2)
		return n;

	int x = fib_serial(n - 1);
	int y = fib_serial(n - 2);

	return x + y;
}


int fib(int n)
{
	if (n < 2)
		return n;

	int x, y;
#pragma omp parallel sections num_threads(2)
	{
		#pragma omp section 
		{
			x = fib_serial(n - 1);
		}
	    
        #pragma omp section 
		{
			y = fib_serial(n - 2);
		}
	}
	return x + y;
}


int main(int argc, char* argv[])
{
	int n = 20;

	double startTime = omp_get_wtime();
	int result = fib(n);
	double endTime = omp_get_wtime();


	cout << "Example 6 - Parallel" << endl;
	cout << "Run time: " << (endTime - startTime) * 1000 << "ms." << endl;

	cout << "Fibonacci of " << n << " is " << result << endl;

	return 0;
}
