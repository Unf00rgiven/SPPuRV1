#include "Registers.h"

using namespace std;


string getRegName(Reg reg)
{
	using namespace string_literals;
	return "t"s + std::to_string(reg);
}


Reg getNewReg()
{
	static int counter = 8;
	return (Reg)(counter++);
}
