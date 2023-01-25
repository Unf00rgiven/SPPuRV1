//Ognjen Stojisavljevic RA 155/2019 datum:10.06.2021.

#include <iostream>
#include <exception>

#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"


using namespace std;


int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\simple.mavn";
		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		cout << endl << "Syntax analysis has started!" << endl;
		SyntaxAnalysis syntax(lex);

		if (syntax.Do())
		{
			cout << endl << "Sintax analysis finished successfully" << endl;
		}
		else
		{
			cout << endl << "ERROR SYNTAX ANALYSIS" << endl;
		}

		syntax.printISNT(&syntax.instrukcije);
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
