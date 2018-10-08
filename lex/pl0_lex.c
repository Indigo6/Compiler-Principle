#include <stdlib.h>
#include "../common/common.h"
#include "pl0_lex.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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

void analysis(const char * word, PL0Lex * lex){
    int test = is_reservedword(word);
    if(test!=-1){
        lex->last_token_type = test + TOKEN_RESWORDS + 1;
        return;
    }
    test = is_symbol(word);
    if(test!=-1){
        lex->last_token_type = test + TOKEN_SYMBOL + 1;
        return;
    }
    if(is_num(word)){
        lex->last_token_type = TOKEN_NUMBER;
        if (word[0] == '-'){
            int tmp = atoi(word+1);
            lex->last_num = -1*tmp;
        }
        else{
            int tmp = atoi(word);
            lex->last_num = tmp;
        }
        return;
    }
    if(is_id(word)){
        lex->last_token_type = TOKEN_IDENTIFIER;
        strcpy(lex->last_id,word);
        return;
    }
    else{
        lex->last_token_type = TOKEN_NULL;
    }
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
        if(word[i]<'0' || word[i]>'9') return FALSE;//全为数字，否则false
        if(i>8) return FALSE;//超出range，false
      }
      return TRUE;//通过考验，true
    }
    else{//负数情况，同上
      for(int i = 1; word[i]!='\0';i++){
        if(word[i]<'0' || word[i]>'9') return FALSE;
        if(i>9) return FALSE;
      }
      return TRUE;
    }
}

void outputWord(PL0Lex * lex){//输出函数，统一格式：【文件类型：（15位）】【空格】【token（10位）】【空格】【行数】【:】【起始位】【-】【结束位】【\n】
    FILE *fout;
    fout = fopen("dataout.txt",a+);
    
    switch(lex->last_token_type){
      case 0 :{//非法token
        fprintf(fout,"error in line %d, %d-%d\n",lex->line_num,lex->start,lex->end);//报错格式：……
        break;
      }
      case 1 :{//标识符
        fprintf(fout,"Identifier:     %-10s %d:%d-%d\n",lex->last_id,lex->line_num,lex->start,lex->end);
	break;
      } 
      case 2 :{//数字
	fprintf(fout,"Number:         %-10d %d:%d-%d\n",lex->last_num,lex->line_num,lex->start,lex->end);
	break;
      }

      case 4 :
      case 5 :
      case 6 :
      case 7 :
      case 8 :
      case 9 :
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
      case 16:
      case 17:
      case 18:
      case 19:{//标点符号
	fprintf(fout,"Symbol:        %-10s %d:%d-%d\n",TOKEN_SYMBOLS[lex->last_token_type-4],lex->line_num,lex->start,lex->end);
	break;
      }
      
      case 21:
      case 22:
      case 23:
      case 24:
      case 25:
      case 26:
      case 27:
      case 28:
      case 29:
      case 30:
      case 31:{//保留字
	fprintf(fout,"Reserved word: %-10s %d:%d-%d\n",TOKEN_RESERVED_WORDS[lex->last_token_type-21],lex->line_num,lex->start,lex->end);
	break;
      }
      default:break;
    }
    fclose(fout);   
}
