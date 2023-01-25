#ifndef __TYPES_H__
#define __TYPES_H__

//#include "Constants.h"

#include <list>
#include <string>


/**
 * Instruction type.
 */
enum InstructionType
{
	move = 0,
	equ,
	sub,
	add,
	mul,
	cond,
	ret,
	others
};


/**
 * Reg names.
 */
enum Regs
{
	undefined = -1,
	reg0 = 0,
	reg1,
	reg2,
	reg3
};


/**
 * This structure represent one variable in program code.
 */
struct Variable
{
	std::string name;	///< variable name
	unsigned int pos;			///< position in interference matrix
	Regs assignment;	///< variable assignment to reg

	Variable(std::string nName, int pPos) : name(nName), pos(pPos), assignment(undefined) {}
};


/**
 * This structure represent few variable from program code.
 */
typedef std::list<Variable*> Variables;


/**
 * This structure represent one instruction in program code.
 */
struct Instruction
{
	unsigned int pos;		///< instruction (node) position in flow control graph

	InstructionType type;	///< instruction type

	Variables use;			///< use variables in this instruction
	Variables def;			///< defined variables in this instruction

	Variables in;			///< live in variables for this instruction, get this from livness annalysis
	Variables out;			///< live out variables for this instruction, get this from livness annalysis

	std::list<Instruction*> succ;		///< successive instructions in control flow graph
	std::list<Instruction*> pred;		///< previous instructions in control flow graph
};


/**
 * This type represent few instruction in program code.
 */
typedef std::list<Instruction*> Instructions;

#endif
