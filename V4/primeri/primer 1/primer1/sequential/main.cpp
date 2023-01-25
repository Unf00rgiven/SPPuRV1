#include <iostream>
#include <omp.h>

using namespace std;

void foo(int id)
{
	for (int i = 0; i < 10; i++)
		cout << id;
}


int main()
{
	printf("Starting off in the sequential world.\n");

	{
		int ID = omp_get_thread_num();
		foo(ID);
	}

	cout << endl << "Back to the sequential world." << endl;
	return 0;
}
