#include "Filter.h"

extern vector<int> in2FilterVector;
extern vector<int> filter2ClipVector;


using namespace std;

RetVal Filter()
{
	int i;
	int Arg;
	const int size_vec = in2FilterVector.size();
	//filter2ClipVector.resize(size_vec - 2);

	for (i = 1; i < size_vec - 1; ++i) {
		Arg = floor((in2FilterVector[i - 1] + in2FilterVector[i] + in2FilterVector[i + 1])*(1 / 3.0f));
		filter2ClipVector.push_back(Arg);
	}

	return RET_OK;
}
