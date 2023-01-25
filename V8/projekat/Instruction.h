#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "Registers.h"

#include <list>
#include <string>

/*
* Class used for intermediate representation of MIPS instructions.
* Each instruction has lists of destination and source registers and
* also its string representation.
*/
class Instruction
{

public:
	Instruction(std::string asmString) : m_asmString(asmString) {};

	/* Gets full instruction string. */
	std::string toString() const;

	std::string getAsmString() const { return m_asmString; }

	std::list<Reg>& getDst() { return m_dst; }
	const std::list<Reg>& getDst() const { return m_dst; }
	std::list<Reg>& getSrc() { return m_src; }
	const std::list<Reg>& getSrc() const { return m_src; }

private:
	std::string m_asmString;

	std::list<Reg> m_dst;

	std::list<Reg> m_src;
};

#endif
