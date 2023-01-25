#include <iostream>
#include <omp.h>
#include <windows.h>

 
using namespace std;

int do_work()
{
	//simulate doing some work
	Sleep(10);
	return 0;
}

void nowait_example2(int n, float *a, float *b, float *y, float *z)
{
	omp_set_num_threads(8);

	for (int i = 0; i < n; i++)
		z[i] = (a[i] + b[i]) / 2.0f + do_work();

	for (int i = 0; i < n; i++)
		y[i] = 100 + do_work();

	for (int i = 1; i <= n; i++)
		y[i - 1] += z[i - 1] - a[i] + do_work();
}

int main(int argc, char **argv)
{
	int n = 100;
	float *a = new float[n + 1];
	float *b = new float[n];
	float *y = new float[n];
	float *z = new float[n];

	for (int i = 0; i < n; i++)
	{
		a[i] = i;
		b[i] = 3*i;
		y[i] = 0;
		z[i] = 0;
	}
	a[n] = 0.25;

	float startTime = omp_get_wtime();
	nowait_example2(n, a, b, y, z);
	float endTime = omp_get_wtime();

	cout << "Example 2 - Sequential" << endl;
	cout << "Run time: " << (endTime - startTime) * 1000 << "ms." << endl;

	cout << "Reuslt: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << y[i] << " ";
		if (i % 10 == 9)
			cout << endl;
	}
	cout << endl;

	return 0;
}
