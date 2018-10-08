#include <stdlib.h>
#include "../common/common.h"
#include "pl0_lex.h"

const char * TOKEN_RESERVED_WORDS[NRW] = {"var", "const", "procedure", "begin", "end", "if", "then", "do", "while", "call", "odd"};
const char * TOKEN_SYMBOLS[NSYM] = { "+", "-", "*", "/", "=", "!=", "<", "<=", ">", ">=", "(", ")", ",", ";", ".", ":=" };

PL0Lex * PL0Lex_create(PL0Compiler * parent)
{
	PL0Lex * lex = (PL0Lex *) calloc(1, sizeof(PL0Lex));
	lex->compiler = parent;
	lex->line_number = 1;
	lex->start = 0;
	lex->end = 0;

	return lex;
}

BOOL PL0Lex_destroy(PL0Lex * lex)
{
	free(lex);
	return TRUE;
}

BOOL PL0Lex_get_token(PL0Lex * lex)
{
    char charcter;
    unsigned int index = 0; //means the index of the character in the token,initialize to 0.
    while((charcter =(char)fgetc(fin)) != EOF){
        if(charcter == '\n' || charcter == ' ' || charcter == '\t'){

        }
    }
	return FALSE;
}

void analysis(char * word){

}

BOOL is_reservedword(char * word){

}

BOOL is_symbol(char * word){

}

BOOL is_id(char* word){

}

BOOL is_num(char * word){

}
