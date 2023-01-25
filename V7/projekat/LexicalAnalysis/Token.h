#ifndef __TOKEN_H__
#define __TOKEN_H__


#include <string>


/**
* Possible token types.
*/
enum TokenType
{
	NO_TYPE,
	START,
	NO_FINITE,
	COMMENT,
	ID,
	NUM,
	REAL,
	IF,
	THEN,
	ELSE,
	PLUS,
	MINUS,
	EQ,
	SEMI,
	WHITE_SPACE,
	ERROR,
	END_OF_FILE,
	BEGIN,
	END,
	PRINT,
	MINUSMINUS,
	MINUSEQ,
	PLUSPLUS,
	PLUSEQ,
	EQEQ
};


class Token
{
public:

	Token();

	Token(TokenType tokenType, std::string value) : m_tokenType(tokenType), m_value(value) {}

	/**
	* Returns token type
	*/
	TokenType getType();

	/**
	* Sets token type
	*/
	void setType(TokenType t);

	/**
	* Returns token value
	*/
	std::string getValue();

	/**
	* Sets token value
	*/
	void setValue(std::string s);

	/**
	* Gets string representation of token type
	*/
	std::string tokenTypeToString();

private:
	/**
	 * Type of the token - as enumeration (defined in common.h)
	 */
	TokenType m_tokenType;
	
	/**
	 * Value of the token - as string
	 */
	std::string m_value;
};

#endif
