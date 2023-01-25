//Ognjen Stojisavljevic RA 155/2019 datum:10.06.2021.

#include "IR.h"
#include <iostream>

using namespace std;

// variable
Variable::VariableType Variable::getType()
{
	return m_type;
}

std::string Variable::getName()
{
	return m_name;
}

int Variable::getPosition()
{
	return m_position;
}

Regs Variable::getAssignment()
{
	return m_assignment;
}

int Variable::getValue()
{
	return m_value;
}

void Variable::setPosition(int pos)
{
	m_position = pos;
}

void Variable::setName(std::string name)
{
	m_name = name;
}
void Variable::setType(VariableType type)
{
	m_type = type;
}
void Variable::setAssignment(Regs assignment)
{
	m_assignment = assignment;
}
void Variable::setValue(int value)
{
	m_value = value;
}


// labele
int Label::getPosition()
{
	return position;
}

void Label::setPosition(int _position)
{
	position = _position;
}

string Label::getName()
{
	return name;
}

void Label::setName(std::string _name)
{
	name = _name;
}


// instrukcije
int Instruction::getPosition()
{
	return m_position;
}

InstructionType Instruction::getType()
{
	return m_type;
}

Label* Instruction::getLabel()
{
	return m_lab;
}

Variable* Instruction::getVariable()
{
	return m_var;
}

string Instruction::getPrintOut()
{
	return m_printOut;
}

int Instruction::getNumber()
{
	return m_number;
}

Variables& Instruction::getDst()
{
	return m_dst;
}

Variables& Instruction::getSrc()
{
	return m_src;
}

Variables& Instruction::getUse()
{
	return m_use;
}

Variables& Instruction::getDef()
{
	return m_def;
}

Variables& Instruction::getIn()
{
	return m_in;
}

Variables& Instruction::getOut()
{
	return m_out;
}

list<Instruction*>& Instruction::getSucc()
{
	return m_succ;
}

list<Instruction*>& Instruction::getPred()
{
	return m_pred;
}

void Instruction::setPosition(int position)
{
	m_position = position;
}

void Instruction::setType(InstructionType inst)
{
	m_type = inst;
}

void Instruction::setLabel(Label* l)
{
	m_lab = l;
}

void Instruction::setDst(Variables& dst)
{
	m_dst = dst;
}

void Instruction::setSrc(Variables& src)
{
	m_src = src;
}

void Instruction::setUse(Variables& use)
{
	m_use = use;
}

void Instruction::setDef(Variables& def)
{
	m_def = def;
}

void Instruction::setIn(Variables& in)
{
	m_in = in;
}

void Instruction::setOut(Variables& out)
{
	m_out = out;
}

void Instruction::setSucc(list<Instruction*> succ)
{
	m_succ = succ;
}

void Instruction::setPred(list<Instruction*> pred)
{
	m_pred = pred;
}

void Instruction::setPrintOut(string tekst)
{
	m_printOut = tekst;
}

void Instruction::setNumber(int number)
{
	m_number = number;
}
