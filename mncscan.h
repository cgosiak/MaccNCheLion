/*	____________________________________________________________________________

	                 Scanner Component for the Micro Compiler

	                                mscan.h

	                              Version 2007
 
	                           James L. Richards
	                         Updated by Jeff Arthur
	                     Last Update: January 28th, 2016

	The routines in this unit are based on those provided in the book 
	"Crafting A Compiler" by Charles N. Fischer and Richard J. LeBlanc, Jr., 
	Benjamin Cummings Publishing Co. (1991).

	See Section 2.2, pp. 25-29.
	____________________________________________________________________________
*/

#ifndef SCANNER
#define SCANNER
#include <string>

extern ifstream sourceFile;

const int ID_STRING_LEN = 32;

enum Token {
	EOF_SYM, 
	BOOL_SYM, 
	BREAK_SYM,
	CASE_SYM,
	CHEESE_SYM,
	DECS_SYM,
	DO_SYM,
	ELSE_SYM,
	END_SYM,
	FALSE_SYM,
	FLOAT_SYM,
	FOR_SYM,
	HIPHIP_SYM,
	IF_SYM,
	INT_SYM,
	LISTEN_SYM,
	OTHERWISE_SYM,
	SELECT_SYM,
	SHOUT_SYM,
	THEN_SYM,
	TRUE_SYM,
	WHILE_SYM,
	UNTIL_SYM,
	LSTAPLE,
	RSTAPLE,
	LBANANA,
	RBANANA,
	LMUSTACHE,
	RMUSTACHE,
	COLON,
	SEMICOLON,
	COMMA,
	ASSIGN_OP,
	PLUS_OP,
	MINUS_OP,
	MULT_OP,
	DIV_OP,
	LT_OP,
	LE_OP,
	GT_OP,
	GE_OP,
	EQ_OP1,
	EQ_OP2,
	NE_OP,
	ID,
	INT_LIT,
	FLOAT_LIT,
	CHEESE_LIT
};

class Scanner
{
public:

	string	tokenBuffer, // current token
			lineBuffer,  // current line
			stringBuffer; // buffer to hold string
	int		lineNumber;  // line counter

	Scanner();
	// Initializes the scanner object.

	Token GetNextToken();
	// Retrieves the next token available in the input stream.

	string GetTokenString(int input);

private:

   void BufferChar(char c);
   // Appends character c to the end of the token buffer provided that the
   // buffer is not full.

   Token CheckReserved();
   // Checks the identifier in the token buffer to see if it is a reserved word
   // or a user-defined identifier and returns the appropriate token.

   void ClearBuffer();
   // Erases the contents of the tokenBuffer.

   void LexicalError(char& c);
   // Processes a lexical error at character c by ignoring that character and 
   // getting the next character.

   char NextChar();
   // Gets next available character from the source file.
};
#endif
