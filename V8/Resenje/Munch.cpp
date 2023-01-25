#include "Munch.h"
#include "Instruction.h"
#include "Registers.h"

#include <cassert>
#include <string>
#include <sstream>

using namespace std;


static InstructionList selectedInstructions;

/*
* Use this function to translate integer value to string
*/
string toString(int value)
{
	string retVal = "";
	stringstream s;
	s << value;
	s >> retVal;
	return retVal;
}

/*
* Add the instruction to the list of selected instructions
*/
void emit(Instruction* instr)
{
	selectedInstructions.push_back(instr);
}


InstructionList& getInstructionList()
{
	return selectedInstructions;
}


void munchStm(Statement* statement)
{
	switch (statement->getType())
	{
		case Statement::MOVE_STM:
		{
			S_Move* moveStm = static_cast<S_Move*>(statement);
			
			Expression* destExp = moveStm->getLeftExp();
			Expression* srcExp = moveStm->getRightExp();

			// if the destination expression (left expression) is memory access
			// then the statement represents storing to memory
			if (destExp->getType() == Expression::MEM_EXP)
			{
				// Here goes the code for sw instruction
				// sw is represented by T_MOVE with T_MEM as destination, and any expression as source
				// consider T_MOVE with all other types of destination expression as not supported ( just call assert(0) )
			}
			else
			{
				assert(0);
			}
		}
		break;


		case Statement::SEQ_STM:
		{
			S_Seq* stmSeq = static_cast<S_Seq*>(statement);

			Statement* left = stmSeq->getLeftStm();
			Statement* right = stmSeq->getRightStm();

			munchStm(left);
			munchStm(right);
		}
		break;


		case Statement::EXP_STM:
		{
			S_Exp* stmExp = static_cast<S_Exp*>(statement);
			
			Expression* expression = stmExp->getExp();
			
			munchExp(expression);
		}
		break;


		default:
			assert(0);
	}
}


Reg munchExp(Expression* expression)
{
	switch (expression->getType())
	{
		case Expression::MEM_EXP:
		{
			// Here goes the code for lw instruction

			//TO DO
			E_Mem* memExp = static_cast<E_Mem*>(expression);
			Expression* innerMemExp = memExp->getExp();
			E_Binop* binopExp = static_cast<E_Binop*>(innerMemExp);

			if (innerMemExp->getType() == E_Binop::PLUS_OP) {						//ako nailazim na +
				Expression* binopLeftExp = binopExp->getLeftExp();
				Expression* binopRightExp = binopExp->getRightExp();

				if (binopLeftExp->getType() == Expression::CONST_EXP)
				{
					E_Const* constExp = static_cast<E_Const*>(binopLeftExp);

					string instructionString = "lw `d, " + toString(constExp->getValue()) + "(`s)";

					Reg sourceReg = munchExp(binopRightExp);
					Reg dstReg = getNewReg();

					Instruction* instr = new Instruction(instructionString);
					instr->getDst().push_back(dstReg);
					instr->getSrc().push_back(sourceReg);

					emit(instr);

					return dstReg;
				}
				else if (binopRightExp->getType() == Expression::CONST_EXP)
				{
					E_Const* constExp = static_cast<E_Const*>(binopRightExp);

					string instructionString = "lw `d, " + toString(constExp->getValue()) + "(`s)";

					Reg sourceReg = munchExp(binopLeftExp);
					Reg dstReg = getNewReg();

					Instruction* instr = new Instruction(instructionString);
					instr->getDst().push_back(dstReg);
					instr->getSrc().push_back(sourceReg);

					emit(instr);

					return dstReg;
				}

			}else if (innerMemExp->getType() == E_Const::CONST_EXP) {			//ako nailazim na const
			
				E_Const* constExp = static_cast<E_Const*>(innerMemExp);

				string instructionString = "lw `d, " + toString(constExp->getValue()) + "($zero)";

				Reg dstReg = getNewReg();

				Instruction* instr = new Instruction(instructionString);
				instr->getDst().push_back(dstReg);

				emit(instr);

				return dstReg;
			}else {									//ako ne nailazim ni na sta
				string instructionString = "lw `d, 0(`s)";

				Reg sourceReg = munchExp(memExp->getExp());
				Reg dstReg = getNewReg();

				Instruction* instr = new Instruction(instructionString);
				instr->getDst().push_back(dstReg);
				instr->getSrc().push_back(sourceReg);

				emit(instr);

				return dstReg;
			}
			

			assert(0);		
			return -1;
		}
		break;

		case Expression::BINOP_EXP:
		{
			E_Binop* binopExp = static_cast<E_Binop*>(expression);
			
			if (binopExp->getOperType() == E_Binop::PLUS_OP)
			{
				Expression* binopLeftExp = binopExp->getLeftExp();
				Expression* binopRightExp = binopExp->getRightExp();

				if (binopRightExp->getType() == Expression::CONST_EXP)
				{
					E_Const* constExp = static_cast<E_Const*>(binopRightExp);

					string instructionString = "addi `d,`s, " + toString(constExp->getValue());

					Reg sourceReg = munchExp(binopLeftExp);
					Reg dstReg = getNewReg();

					Instruction* instr = new Instruction(instructionString);
					instr->getDst().push_back(dstReg);
					instr->getSrc().push_back(sourceReg);

					emit(instr);

					return dstReg;
				}
				else if (binopLeftExp->getType() == Expression::CONST_EXP)
				{
					E_Const* constExp = static_cast<E_Const*>(binopLeftExp);

					string instructionString = "addi `d,`s, " + toString(constExp->getValue());

					Reg sourceReg = munchExp(binopRightExp);
					Reg dstReg = getNewReg();

					Instruction* instr = new Instruction(instructionString);
					instr->getDst().push_back(dstReg);
					instr->getSrc().push_back(sourceReg);

					emit(instr);

					return dstReg;
				}
				else {

				//TO DO
					string instructionString = "addi `d,`s,`s";
					Reg sourceRegL = munchExp(binopLeftExp);
					Reg sourceRegR = munchExp(binopRightExp);
					Reg dstReg = getNewReg();

					Instruction* instr = new Instruction(instructionString);
					instr->getDst().push_back(dstReg);
					instr->getSrc().push_back(sourceRegL);
					instr->getSrc().push_back(sourceRegR);

					emit(instr);

					return dstReg;
				}
			}
			else
			{
				assert(0);
				return -1;
			}
		}

		case Expression::REG_EXP:
		{
			E_Reg* regExp = static_cast<E_Reg*>(expression);
			return regExp->getRegId();
		}

		case Expression::CONST_EXP:
		{
			E_Const* constExp = static_cast<E_Const*>(expression);

			string instructionString = "li `d, " + toString(constExp->getValue());

			Reg dstReg = getNewReg();

			Instruction* instr = new Instruction(instructionString);
			instr->getDst().push_back(dstReg);

			emit(instr);

			return dstReg;
		}

		case Expression::ESEQ_EXP:
		{
			E_Eseq* eseqExp = static_cast<E_Eseq*>(expression);

			Expression* eseqLeft = eseqExp->getLeftExp();
			Statement* eseqRight = eseqExp->getRightStm();

			Reg dstReg = munchExp(eseqLeft);
			munchStm(eseqRight);

			return dstReg;
		}

		default:
			assert(0);
			return -1;
	}

	assert(0);
}
