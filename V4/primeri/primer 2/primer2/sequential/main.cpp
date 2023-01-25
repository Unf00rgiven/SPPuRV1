#include <vector>
#include <iostream>
#include <omp.h>
#include <windows.h>

using namespace std;

template <typename T>

void print_vector(T &vec)
{
	cout << "{ ";
	for (T::iterator it = vec.begin(); it < vec.end(); it++)
		cout << *it << " ";
	cout << "}" << endl;
}

void do_work(int i)
{
	//simulate doing some work
	Sleep(i*100);
}


int main(int argc, char **argv)
{
	const int n = 10;
	vector<int> x(n), y(n);

	float startTime = omp_get_wtime();

	for (int i = 0; i < n; ++i)
	{
		x[i] = i;
		y[i] = 2 * i;

		do_work(i);
	}

	float endTime = omp_get_wtime();

	cout << "Example 2 - Serial" << endl;
	cout << "Run time: " << (endTime - startTime) * 1000 << "ms." << endl;

	print_vector(x);
	print_vector(y);

	return 0;
}
