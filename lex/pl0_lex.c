#include <stdlib.h>
#include "../common/common.h"
#include "pl0_lex.h"
#include <string.h>

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

int is_reservedword(const char * word){  //return the index of the reserved word table or -1(not find)
    for(int i = 0;i<NRW;i++){
      if(strcmp(TOKEN_RESERVED_WORDS[i],word) == 0) return i;
    }
    return -1;
}

int is_symbol(const char * word){  //return the index of the symbol table or -1(not find)
    for(int i = 0;i<NSYM;i++){
      if(strcmp(TOKEN_SYMBOLS[i],word) == 0) return i;
    }
    return -1;
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
    BOOL neg_flag = FALSE;
    if(word[0] == '-') neg_flag = TRUE;//判断是不是负数
    if(neg_flag && word[1] == '\0') return FALSE;
    if(!neg_flag){//正数情况
      for(int i = 0; word[i]!='\0';i++){
        if(word[i]<'0' || word[i]>9) return FALSE;//全为数字，否则false
        if(i>8) return FALSE;//超出range，false
      }
      return TRUE;//通过考验，true
    }
    else{//负数情况，同上
      for(int i = 1; word[i]!='\0';i++){
        if(word[i]<'0' || word[i]>9) return TRUE;
        if(i>9) return FALSE;
      }
      return TRUE;
    }
}
