#include "Instruction.h"

#include <iostream>
#include <cassert>

using namespace std;

/* Format the assembly instruction string by adding sources and destinations
* to specified locations in the asm string (replacing `s and `d)
*/
static std::string format(const Instruction& inst);


std::string Instruction::toString() const
{
	return format(*this);
}


static std::string format(const Instruction& inst)
{
	list<Reg>::const_iterator srci, dsti;
	char c;				// current character in asm string
	int i;				// current index of a characted in a string
	string formattedString = "";

	if (!inst.getSrc().empty())
		srci = inst.getSrc().begin();

	if (!inst.getDst().empty())
		dsti = inst.getDst().begin();

	i = 0;
	while (i != inst.getAsmString().size())
	{
		c = inst.getAsmString()[i];
		
		if (c == '`')
		{
			switch (inst.getAsmString()[i+1])
			{
				case 's':
					formattedString += getRegName(*srci);
					srci++;
					i++;
					break;

				case 'd':
					formattedString += getRegName(*dsti);
					dsti++;
					i++;
					break;

				default:
					assert(0);
			}
		}
		else
		{
			formattedString += c;
		}
		i++;
	}

	return formattedString;
}
