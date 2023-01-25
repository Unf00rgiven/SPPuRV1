//Ognjen Stojisavljevic RA 155/2019 datum:10.06.2021.

#pragma once
#ifndef __IR__
#define __IR__

#include "Types.h"
#include <iostream>
#include <stack>

/**
 * This class represents one variable from program code.
 */
class Variable
{
public:
	enum VariableType
	{
		MEM_VAR,
		REG_VAR,
		NO_TYPE
	};

	Variable() : m_type(NO_TYPE), m_name(""), m_position(-1), m_assignment(no_assign) {}
	Variable(std::string name, int pos) : m_type(NO_TYPE), m_name(name), m_position(pos), m_assignment(no_assign) {}

	Variable(std::string name, VariableType vt) : m_type(vt), m_name(name), m_position(0), m_assignment(no_assign) {}

	VariableType getType();
	std::string getName();
	int getPosition();
	Regs getAssignment();
	int getValue();

	void setPosition(int);
	void setName(std::string);
	void setType(VariableType);
	void setAssignment(Regs);
	void setValue(int);

private:
	VariableType m_type;
	std::string m_name;
	int m_position;
	Regs m_assignment;
	int m_value;
};
/**
 * This type represents list of variables from program code.
 */
typedef std::list<Variable*> Variables;

/**
 * This type represents list of labels from program code.
 */
class Label {
private:
	int position;
	std::string name;

public:
	Label() {}
	Label(int _position, std::string _name) : position(_position), name(_name) {}

	int getPosition();
	void setPosition(int _position);
	std::string getName();
	void setName(std::string _name);
};

typedef std::list<Label*> Labels;
/**
 * This class represents one instruction in program code.
 */
class Instruction
{
public:
	Instruction() : m_position(0), m_type(I_NO_TYPE) {}
	Instruction(int pos, InstructionType type, Variables& dst, Variables& src) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src) {}

	Instruction(InstructionType instr) : m_position(-1), m_type(instr) {}

	int getPosition();
	InstructionType getType();
	std::string getPrintOut();
	int getNumber();
	Label* getLabel();
	Variable* getVariable();

	Variables& getDst();
	Variables& getSrc();

	Variables& getUse();
	Variables& getDef();
	Variables& getIn();
	Variables& getOut();

	std::list<Instruction*>& getSucc();
	std::list<Instruction*>& getPred();

	void setPosition(int position);
	void setType(InstructionType inst);
	void setLabel(Label* l);

	void setDst(Variables& dst);
	void setSrc(Variables& src);

	void setUse(Variables& use);
	void setDef(Variables& def);
	void setIn(Variables& in);
	void setOut(Variables& out);

	void setSucc(std::list<Instruction*> succ);
	void setPred(std::list<Instruction*> pred);
	void setPrintOut(std::string text);
	void setNumber(int number);

private:
	int m_position;
	InstructionType m_type;
	std::string m_printOut;
	int m_number;
	Label* m_lab;
	Variable* m_var;

	Variables m_dst;
	Variables m_src;

	Variables m_use;
	Variables m_def;
	Variables m_in;
	Variables m_out;
	std::list<Instruction*> m_succ;
	std::list<Instruction*> m_pred;

};


/**
 * This type represents list of instructions from program code.
 */
typedef std::list<Instruction*> Instructions;


#endif

