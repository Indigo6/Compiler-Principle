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
    for(int i = 0;i<NRW;i++){
      if(strcmp(TOKEN_RESERVED_WORDS[i],word) == 0) return true;
    }
    return false;
}

BOOL is_symbol(char * word){
    for(int i = 0;i<NSYM;i++){
      if(strcmp(TOKEN_SYMBOLS[i],word) == 0) return true;
    }
    return false;
}

BOOL is_id(char* word){
       
}

BOOL is_num(char * word){
    bool neg_flag = false;
    if(word[0] == '-') neg_flag = true;//判断是不是负数
    if(!neg_flag){//正数情况
      for(int i = 0; word[i]!='\0';i++){
        if(word[i]<'0' || word[i]>9) return false;//全为数字，否则false
        if(i>8) return false;//超出range，false
      }
      return true;//通过考验，true
    }
    else{//负数情况，同上
      for(int i = 1; word[i]!='\0';i++){
        if(word[i]<'0' || word[i]>9) return false;
        if(i>9) return false;
      }
      return true;
    }
}
