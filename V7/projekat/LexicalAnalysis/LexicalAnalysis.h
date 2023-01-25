#ifndef __LEXICAL_ANALYSIS_H__
#define __LEXICAL_ANALYSIS_H__

#include <fstream>
#include <vector>
#include <list>

#include "Token.h"

typedef std::list<Token> TokenList;

class LexicalAnalysis
{
public:

	/**
	* Method for initializing the lexical analysis and FSM
	*/
	void initialize();

	/**
	* Method which performs lexical analysis
	*/
	bool Do();

	/**
	* Method for reading the input file
	*/
	bool readInputFile(std::string fileName);

	/**
	* Use this function to get the list of tokens read from the source code
	*
	* @return list of tokens
	*/
	TokenList& getTokenList();

	/**
	* Prints the token list
	*
	*/
	void printTokens();

	/**
	* Prints the errornous token if present
	*
	*/
	void printLexError();

private:
	/**
	* Use this function to get next lexical token from program source code.
	*
	* @return next lexical token in program source code
	*/
	Token getNextTokenLex();

	/**
	* Used for printing the test list. It decorates the output with header naming the columns
	*/
	void printMessageHeader();

	std::ifstream m_inputFile; //** Input file containing program text to be analyzed

	std::vector<char> m_programBuffer; //** Program buffer containing the contents of the input files

	unsigned int m_programBufferPosition; //** Current position of the program buffer

	TokenList m_tokenList; //** List of parsed tokens

	Token m_errorToken; //** If an error occurs while parsing this attribute will hold the errornous Token
};

#endif
