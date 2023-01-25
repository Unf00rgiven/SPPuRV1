//Ognjen Stojisavljevic RA 155/2019 datum:10.06.2021.

#pragma once
#include <iostream>
#include <iomanip>

#include "LexicalAnalysis.h"
#include "Token.h"
#include "IR.h"

using namespace std;


class SyntaxAnalysis
{
private:
	void printSyntaxError(Token tok); // stampa gresku i token gde je greska nastala

	void eat(TokenType tok); // uzima tip tokena

	Token getNextToken(); // sledeci token iz liste

	void Q(); // neterminalni Q
	void S(); // neterminalni S
	void L(); // neterminalni L
	void E(); // neterminalni E

	LexicalAnalysis& lexicalAnalysis; 
	
	int regPosition;
	int position;

	bool errorFound;

	TokenList::iterator tokenIterator;

	Token currentToken;

	

public:

	bool Do(); // metoda zapocinje analizu
	SyntaxAnalysis(LexicalAnalysis& lex); // konstruktor

	bool jedinstvenaVarijabla(Variable* var);				 //provera variable
	bool jedinstvenaLabela(Label* lab);						 //provera labele
	void dodajVARuINST(Instruction* instr, bool source);	 //dodaje VAR u INST
	void dodajLABuINST(Instruction* instr);					 //dodaje LAB u INST
	Variable* getVariable(Variable* var);					 //uzima iz postojece liste variabli
	void printISNT(Instructions* instr);				     //ispisuje INST
	
	Labels labele;
	Variables variable;
	Instructions instrukcije;

};