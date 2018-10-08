#include <stdlib.h>
#include "../common/common.h"
#include "pl0_lex.h"
#include <ctype.h>

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
    
}

void analysis(const char * word){

}

BOOL is_reservedword(const char * word){

}

BOOL is_symbol(const char * word){

}

BOOL is_id(const char* word){
    char tmp = word[0];
    if(!isalpha(tmp) && tmp!='_'){
        return FALSE;
    }
    else{
        unsigned index = 1;
        char tmp2;
        tmp2 = word[index];
        while(tmp2!='\0'){
            if(!isalnum(tmp2) && tmp2!='_'){
                return FALSE;
            }
            else{
                index ++;
                tmp2 = word[index];
                if(index > 10){
                    return FALSE;
                }
            }
        }
        return TRUE;
    }
}


BOOL is_num(const char * word){

}
