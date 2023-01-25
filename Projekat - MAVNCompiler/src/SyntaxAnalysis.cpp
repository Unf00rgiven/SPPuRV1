//Ognjen Stojisavljevic RA 155/2019 datum:10.06.2021.

#include <iostream>
#include <iomanip>
#include "SyntaxAnalysis.h"


using namespace std;

// PROVERA DA LI POSTOJI VEC NEKA VARIJABLA SA TIM IMENOM("SEMATICKA ANALIZA")
bool SyntaxAnalysis::jedinstvenaVarijabla(Variable* var)
{
	for (auto it = variable.begin(); it != variable.end(); it++)
	{
		if (!strcmp((*it)->getName().c_str(), var->getName().c_str())) return true;
	}
	return false; // ukoliko ni jednom ne udje u if, varijabla korektna
}

// PROVERA DA LI POSTOJI VEC NEKA LABELA SA TIM IMENOM("SEMATICKA ANALIZA")
bool SyntaxAnalysis::jedinstvenaLabela(Label* lab)
{
	for (auto it = labele.begin(); it != labele.end(); it++)
	{
		if (!strcmp((*it)->getName().c_str(), lab->getName().c_str())) return true;
	}
	return false; // ukoliko ni jednom ne udje u if, varijabla korektna
}

// POSTAVLJA PROMENLJIVE U INSTRUKCIJU
void SyntaxAnalysis::dodajVARuINST(Instruction* instr, bool source)
{
	Variable* var = new Variable();
	var->setName(currentToken.getValue());

	// provera da li promenljiva postoji u listi promenljivih
	if (!jedinstvenaVarijabla(var))
	{
		errorFound = true;
		throw runtime_error("Ne postoji promenljiva");
	}

}

// DODAJE LABELU U INSTRUKCIJU
void SyntaxAnalysis::dodajLABuINST(Instruction* instr)
{
	if (jedinstvenaLabela(new Label(-1, currentToken.getValue())))		// provera da li labela postoji
	{
		for (auto it = labele.begin(); it != labele.end(); it++)	// trazimo na kojoj se poziciji nalazi labela i dodeljujemo je instrukciji
		{
			if (!strcmp(currentToken.getValue().c_str(), (*it)->getName().c_str()))
			{
				(*instr).setLabel(*it);
			}
		}
	}
}


// ISPISUJE PODATKE
void SyntaxAnalysis::printISNT(Instructions* instr)
{
	Instructions::iterator it;

	char* insType[] = { "NO_TYPE", "ADD", "ADDI", "SUB", "LA", "LI", "LW", "SW", "BLTZ", "B", "NOP", "JALR", "SLL", "JR", "OR", "ABS" };

	for (it = instr->begin(); it != instr->end(); it++) {

		int br = 1;
		cout << "Type: " << insType[(*it)->getType()] << "	Pos: " << (*it)->getPosition() << endl;
		cout << "------------------------------------------" << endl;
		for (auto it1 = (*it)->getDst().begin(); it1 != (*it)->getDst().end(); it1++)
		{
			cout << "Dst" << br++ << ":	Naziv: " << (*it1)->getName() << ",  Pos: " << (*it1)->getPosition() << ",  Assignment: " << (*it1)->getAssignment() << endl;
		}
		br = 1;
		for (auto it1 = (*it)->getSrc().begin(); it1 != (*it)->getSrc().end(); it1++)
		{
			cout << "Src" << br++ << ":	Naziv: " << (*it1)->getName() << ",  Pos: " << (*it1)->getPosition() << ",  Assignment: " << (*it1)->getAssignment() << endl;
		}
		cout << "------------------------------------------" << endl;
		cout << "PRED:	";

		for (auto it1 = (*it)->getPred().begin(); it1 != (*it)->getPred().end(); it1++)
		{
			cout << (*it1)->getPosition() << " ";
		}
		cout << endl;
		cout << "SUCC:	";

		for (auto it1 = (*it)->getSucc().begin(); it1 != (*it)->getSucc().end(); it1++)
		{
			cout << (*it1)->getPosition() << " ";
		}
		cout << endl;
		cout << "USE:	";
		for (auto it1 = (*it)->getUse().begin(); it1 != (*it)->getUse().end(); it1++)
		{
			if ((*it1)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*it1)->getName() << '\t';
		}
		cout << endl;
		cout << "DEF:	";
		for (auto it1 = (*it)->getDef().begin(); it1 != (*it)->getDef().end(); it1++)
		{
			if ((*it1)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*it1)->getName() << '\t';
		}
		cout << endl;
		cout << "IN:	";
		for (auto it1 = (*it)->getIn().begin(); it1 != (*it)->getIn().end(); it1++)
		{
			if ((*it1)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*it1)->getName() << '\t';
		}
		cout << std::endl;
		cout << "OUT:	";
		for (auto it1 = (*it)->getOut().begin(); it1 != (*it)->getOut().end(); it1++)
		{
			if ((*it1)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*it1)->getName() << '\t';
		}
		cout << endl;
		cout << "------------------------------------------------" << endl;
	}
}


SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex)
	: lexicalAnalysis(lex), errorFound(false),position(0), tokenIterator(lexicalAnalysis.getTokenList().begin()), regPosition(0)
{
}


bool SyntaxAnalysis::Do()
{
	currentToken = getNextToken();
	Q();

	if (--tokenIterator == lexicalAnalysis.getTokenList().begin())
	{
		return false;

	}
	else
	{
		return !errorFound;
	}
}


void SyntaxAnalysis::printSyntaxError(Token token)
{
	cout << "Syntax error! Token: " << token.getValue() << " unexpected" << endl;
	throw runtime_error("Sintaksna analiza neuspesna");
}


void SyntaxAnalysis::eat(TokenType t)
{
	if (errorFound == false)
	{
		if (currentToken.getType() == t)
		{
			cout << currentToken.getValue() << endl;
			if (t != T_END_OF_FILE)
			{
				currentToken = getNextToken();
			}
		}
		else
		{
			printSyntaxError(currentToken);
			errorFound = true;
		}
	}
}


Token SyntaxAnalysis::getNextToken()
{
	if (tokenIterator == lexicalAnalysis.getTokenList().end())
		throw runtime_error("End of input file reached");
	return *tokenIterator++;
}


void SyntaxAnalysis::Q()
{
	S();
	if (currentToken.getType() == T_SEMI_COL) eat(TokenType::T_SEMI_COL);
	else throw runtime_error("Greska u sintaksi");
	L();
}


void SyntaxAnalysis::S()
{
	Variable* var;
	Label* lab;

	if (currentToken.getType() == TokenType::T_MEM)
	{
		eat(TokenType::T_MEM);
		var = new Variable(currentToken.getValue(), Variable::VariableType::MEM_VAR); // rec smestamo u promenljivu

		if (currentToken.getType() == T_M_ID) eat(TokenType::T_M_ID);
		else throw runtime_error("Greska u sintaksi");

		if (jedinstvenaVarijabla(var)) // ukoliko vrati true vec postoji takva varijabla
		{
			errorFound = true;
			throw runtime_error("Promenjliva vec postoji");
		}
		var->setValue(atoi(currentToken.getValue().c_str()));

		if (currentToken.getType() == T_NUM) eat(TokenType::T_NUM);
		else throw runtime_error("Greska u sintaksi");

		variable.push_back(var);
	}
	else if (currentToken.getType() == TokenType::T_REG)
	{
		eat(TokenType::T_REG);
		var = new Variable(currentToken.getValue(), Variable::VariableType::REG_VAR); // rec smestamo u promenljivu
		if (jedinstvenaVarijabla(var)) // ukoliko vrati true vec postoji takva varijabla
		{
			errorFound = true;
			throw runtime_error("Promenjliva vec postoji");
		}
		variable.push_back(var);
		var->setPosition(regPosition++);

		if (currentToken.getType() == T_R_ID) eat(TokenType::T_R_ID);
		else throw runtime_error("Greska u sintaksi");
		
	}
	else if (currentToken.getType() == TokenType::T_FUNC)
	{
		eat(TokenType::T_FUNC);
		if (!isalpha(currentToken.getValue()[0])) // funckija ne sme da pocinje sa brojem
		{
			errorFound = true;
			throw runtime_error("Funkcija ne sme da pocinje sa brojem");
		}
		
		lab = new Label(position, currentToken.getValue()); // cuvamo rec u labelu
		
		// provera da li labela postoji
		if (jedinstvenaLabela(lab))
		{
			errorFound = true;
			throw runtime_error("Labela vec postoji");
		}

		labele.push_back(lab);

		if (currentToken.getType() == T_ID) eat(TokenType::T_ID);
		else throw runtime_error("Greska u sintaksi");
	}
	else if (currentToken.getType() == TokenType::T_ID)
	{
		eat(TokenType::T_ID);

		lab = new Label(position, currentToken.getValue()); // cuvamo rec u labelu

		// provera da li labela postoji
		if (jedinstvenaLabela(lab))
		{
			errorFound = true;
			throw runtime_error("Labela vec postoji");
		}

		labele.push_back(lab);
		if (currentToken.getType() == T_COL) eat(TokenType::T_COL);
		else throw runtime_error("Greska u sintaksi");
		E();
	}
	else E();
}


void SyntaxAnalysis::L()
{
	if (currentToken.getType()==TokenType::T_END_OF_FILE)
	{
		eat(TokenType::T_END_OF_FILE);
	}
	else Q();
}


void SyntaxAnalysis::E()
{
	if (currentToken.getType() == TokenType::T_ADD) // add rd,rs,rs
	{
		eat(TokenType::T_ADD);
		Instruction* instruction = new Instruction(I_ADD);
		instruction->setPrintOut("add \t `d,`s,`s");
		
		if (currentToken.getType() == TokenType::T_R_ID)
		{
			dodajVARuINST(instruction, false);			// false destination
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == TokenType::T_COMMA)
		{
			eat(TokenType::T_COMMA);
		}
		else throw runtime_error("Greska u sintaksi");
		
		if (currentToken.getType() == TokenType::T_R_ID)
		{
			dodajVARuINST(instruction, true);			// true source
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == TokenType::T_COMMA)
		{
			eat(TokenType::T_COMMA);
		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == TokenType::T_R_ID)
		{
			dodajVARuINST(instruction, true);			// true source
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		instruction->setPosition(position++);			// broji koja je po redu instrukcija
		instrukcije.push_back(instruction);
	}
	else if (currentToken.getType() == TokenType::T_JALR) // jalr rs,rd
	{
		eat(TokenType::T_JALR);
		Instruction* instruction = new Instruction(I_JALR);
		instruction->setPrintOut("jalr \t `s,`d");


		if (currentToken.getType() == TokenType::T_R_ID)
		{
			dodajVARuINST(instruction, true);			// true source
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == TokenType::T_COMMA)
		{
			eat(TokenType::T_COMMA);
		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == TokenType::T_R_ID)
		{
			dodajVARuINST(instruction, false);			// false destination
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		instruction->setPosition(position++);
		instrukcije.push_back(instruction);
	
	}
	else if (currentToken.getType() == TokenType::T_SLL) //sll rd,rs,n
	{
		eat(TokenType::T_SLL);
		Instruction* instruction = new Instruction(I_SLL);
		instruction->setPrintOut("sll \t `d,`s,`n");

		if (currentToken.getType() == T_R_ID)
		{
			dodajVARuINST(instruction, false);			// false destination
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_COMMA)
		{
			eat(TokenType::T_COMMA);

		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_R_ID)
		{
			dodajVARuINST(instruction, true);			// true source
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_COMMA)
		{
			eat(TokenType::T_COMMA);

		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_NUM)
		{
			eat(TokenType::T_NUM);
		}
		else throw runtime_error("Greska u sintaksi");

		instruction->setPosition(position++);
		instrukcije.push_back(instruction);
	
	}
	else if (currentToken.getType() == TokenType::T_LA) // la rd,rs
	{	
		eat(TokenType::T_LA);
		Instruction* instruction = new Instruction(I_LA);
		instruction->setPrintOut("la \t `d,`s");

		if (currentToken.getType() == T_R_ID)
		{
			dodajVARuINST(instruction, false);			// false destination
			eat(TokenType::T_R_ID);

		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_COMMA)
		{
			eat(TokenType::T_COMMA);

		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_R_ID)
		{
			dodajVARuINST(instruction, true);			// true source
			eat(TokenType::T_R_ID);
			
		}
		else throw runtime_error("Greska u sintaksi");

		
		instruction->setPosition(position++);
		instrukcije.push_back(instruction);

	}
	else  if (currentToken.getType() == TokenType::T_LW) // lw rd,n(rs)
	{
		eat(TokenType::T_LW);
		Instruction* instruction = new Instruction(I_LW);
		instruction->setPrintOut("lw \t `d,`n(`s)");

		if (currentToken.getType() == T_R_ID)
		{
			dodajVARuINST(instruction, false);			// false destination
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");
		
		if (currentToken.getType() == T_COMMA)
		{
			eat(TokenType::T_COMMA);
			
		}
		else throw runtime_error("Greska u sintaksi");
		
		if (currentToken.getType() == T_NUM)
		{
			eat(TokenType::T_NUM);

		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_L_PARENT)
		{
			eat(TokenType::T_L_PARENT);

		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_R_ID)
		{
			
			dodajVARuINST(instruction, true);			// true source
			eat(TokenType::T_R_ID);

		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_R_PARENT)
		{
			eat(TokenType::T_R_PARENT);

		}
		else throw runtime_error("Greska u sintaksi");


		instruction->setPosition(position++);
		instrukcije.push_back(instruction);

	
	}
	else if (currentToken.getType() == TokenType::T_JR) // jr rs
	{
		eat(TokenType::T_JR);
		Instruction* instruction = new Instruction(I_JR);
		instruction->setPrintOut("jr \t `s");

		if (currentToken.getType() == T_R_ID)
		{
			
			dodajVARuINST(instruction, true);			// true source
			eat(TokenType::T_R_ID);

		}
		else throw runtime_error("Greska u sintaksi");

		instruction->setPosition(position++);
		instrukcije.push_back(instruction);
	}
	else if (currentToken.getType() == TokenType::T_OR) // or rd ,rs ,rs 
	{
		eat(TokenType::T_OR);
		Instruction* instruction = new Instruction(I_OR);
		instruction->setPrintOut("or \t `d,`s,`s");

		if (currentToken.getType() == T_R_ID)
		{
			
			dodajVARuINST(instruction, false);			// false destination
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_COMMA) eat(TokenType::T_COMMA);
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_R_ID)
		{
			
			dodajVARuINST(instruction, true);			// true source
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_COMMA) eat(TokenType::T_COMMA);
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_R_ID)
		{
			
			dodajVARuINST(instruction, true);			// true source
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		instruction->setPosition(position++);			// broji koja je po redu instrukcija
		instrukcije.push_back(instruction);
	}
	else if (currentToken.getType() == TokenType::T_B) //b l
	{	
		eat(TokenType::T_B);
		Instruction* instruction = new Instruction(I_B);
		instruction->setPrintOut("b \t `l");

		if (currentToken.getType() == T_ID)
		{
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		instruction->setPosition(position++);
		instrukcije.push_back(instruction);
	}
	else if (currentToken.getType() == TokenType::T_BLTZ) //bltz rs, l
	{
		eat(TokenType::T_BLTZ);
		Instruction* instruction = new Instruction(I_BLTZ);
		instruction->setPrintOut("bltz \t `s,`l");
		
		if (currentToken.getType() == T_R_ID)
		{
			
			dodajVARuINST(instruction, true);		//true source
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");
		
		if (currentToken.getType() == T_COMMA)
		{
			eat(TokenType::T_COMMA);
		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_ID)
		{
			eat(TokenType::T_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		instruction->setPosition(position++);
		instrukcije.push_back(instruction);
	}
	else if(currentToken.getType()==TokenType::T_ABS)	//abs rd,rs
	{
		eat(TokenType::T_ABS);
		Instruction* instruction = new Instruction(I_ABS);
		instruction->setPrintOut("abs \t `d,`s");

		if (currentToken.getType() == T_R_ID)
		{
			
			dodajVARuINST(instruction, false);			// false destination
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_COMMA) eat(TokenType::T_COMMA);
		else throw runtime_error("Greska u sintaksi");

		if (currentToken.getType() == T_R_ID)
		{
			
			dodajVARuINST(instruction, true);			// true source
			eat(TokenType::T_R_ID);
		}
		else throw runtime_error("Greska u sintaksi");

		instruction->setPosition(position++);
		instrukcije.push_back(instruction);
	}
	else
	{
		throw runtime_error("Nepodrzavajuca instrukcija");
	}
}


