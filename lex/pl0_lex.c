#include <stdlib.h>
#include "../common/common.h"
#include "pl0_lex.h"
#include <string.h>
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
	lex->offset = 0;
	lex->isEOF = FALSE;

	return lex;
}

BOOL PL0Lex_destroy(PL0Lex * lex)
{
	free(lex);
	return TRUE;
}



BOOL PL0Lex_get_token(PL0Lex * lex)
{
    BOOL _get_token;            //Signal for result of getting token, 0 for failure, 1 for success
    lex->start = 0;lex->end = 0;
    lex->overlong = 0;
    _get_token = get_token(lex);
    if(!_get_token){
        if(lex->overlong){
            lex->last_token_type = TOKEN_NULL;
            return TRUE;
        }
        else{
            return 0;
        }
    }
    else{
        analysis(lex->token,lex);
        return TRUE;
    }
}


BOOL Is_split(PL0Lex *lex, char letter){      // cognize if letter is one of ' ','\t', '\n',
    if(letter == '\t'){
        lex->offset += 4;   
    }
    else if(letter == ' '){
        lex->offset += 1;
    }
    else if(letter == '\n'){
        lex->offset = 0;
        lex->line_number++;
    }
    else return 0;
    return 1;
}   //我想把分隔符的offset和linenumber管理放一起

BOOL get_token(PL0Lex * lex){
    char letter;
    int state = 0;
    char sym1,sym2;
    int iter = 0;
    
    while(1){
        switch(state){
            case 0:{
		    	letter = fgetc(fin);
        	    if(letter == EOF){
        	        lex->isEOF = TRUE;
                    return 0;
                }
		    	else if(isalnum(letter) || letter == '_'){//token
		    		state = 1;//跳转到状态s1
                    lex->start = lex->offset++;
                    lex->token[iter++] = letter;
                }
                else if(Is_split(lex,letter));
                else{
                    state = 2;
                    lex->start = lex->offset++;
                    sym1 = letter;
                }
                break;
            }
            case 1:{
                letter = fgetc(fin);
                if(isalnum(letter) || letter=='_'){//token
                    state = 1;//跳转到状态s1
                    lex->offset++;//行内位置++
                    if(iter > MAX_TOKEN_LEN){//长度超标
                        lex->overlong = 1;
                        lex->token[0]='\0';//暂存数组首位置空
                        iter = 0;//暂存数组指针指向首位
                        while(1){
                            letter = fgetc(fin);
                            if(isalnum(letter) || letter=='_'){//跳过之后的一串token
                                lex->offset++;
                                continue;	
                            }
                            else if(letter == EOF){
                                lex->isEOF = 1;
                                return 0;
                            }
                            else{
                                fseek(fin,-1,SEEK_CUR);//读至分隔符或符号，回退一位
                                return 0;
                            }
                        }
                    }
                    lex->token[iter] = letter;//存入暂存数组
                    iter++;//暂存数组的指针++
                    break;//继续该状态循环读入token
                }
                else{//symbol或分隔符
                    if(letter == EOF)  lex->isEOF = TRUE;
                    lex->end = lex->offset;
                    lex->offset++;
                    lex->token[iter] = '\0';
                    fseek(fin,-1,SEEK_CUR);//回退
                    return 1;
                }
                break;
            }
            case 2:{
                sym2 = (char)fgetc(fin);
                if(sym2==EOF){
                    lex->token[0] = sym1;
                    lex->token[1] = '\0';
                    lex->end = lex->offset;
                    lex -> isEOF = TRUE;
                    return 1;
                }
                else{
                    lex->offset ++;
                    if(is_symbol(sym2)!=-1){
                        state = 3;
                        continue;
                    } 
                    else{
                        fseek(fin, -1, SEEK_CUR);
                        lex->offset --;
                        lex->end = lex->offset;
                        lex->token[0] = sym1;
                        lex->token[1] = '\0';
                        return 1;
                    }
                }
                break;
            }
            case 3:{
                char tmp[3];
                tmp[0] = sym1;
                tmp[1] = sym2;
                tmp[2] = '\0';
                if(is_symbol(tmp)!=-1){
                    lex->token[0] = sym1;
                    lex->token[1] = sym2;
                    lex->token[2] = '\0';
                    return 1;
                }
                else if(sym1=='/' && sym2=='/'){
                    state = 4;
                }
                else if(sym1=='/' && sym2 == '*'){
                    state =5;
                }
                else{
                    fseek(fin,-1,SEEK_CUR);
                    lex->offset --;
                    lex->token[0] = sym1;
                    lex->token[1] = '\0';
                    lex->end = lex->offset;
                    return 1;
                }
                break;
            }
            case 4:{
                letter = fgetc(fin);
                if(letter == '\n'){
                    state = 0;
                    lex->line_number++;
                    lex->offset = 0;
                }
                else if(letter == EOF){
                    lex -> isEOF = TRUE;
                    return 0;
                }
                break;
            }
            case 5:{
                letter = fgetc(fin);
                if(letter == '*'){
                    state = 6;
                    lex->offset++;
                }
                else if(letter == EOF){
                    lex -> isEOF = TRUE;
                    return 0;
                }
                else{
                    if(!Is_split(lex,letter)){
                        lex->offset++;
                    }
                }
                break;
            }
            case 6:{
                letter = fgetc(fin);
                if(letter == '/'){
                    state = 0;
                }
                else if(letter == EOF){
                    lex -> isEOF = TRUE;
                    return 0;
                }
                else{
                    if(!Is_split(lex,letter)){
                        lex->offset++;
                    }
                }
                break;
            }
        }
    }
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
    int range = 9;
    if(word[0] == '-') neg_flag = TRUE;//判断是不是负数
    if(neg_flag && word[1] == '\0') return FALSE;
    if(!neg_flag){//正数情况
      if(word[0]== 0) range = 10;
      for(int i = 0; word[i]!='\0';i++){
	if(i == range) return FALSE;//超出range，false
        if(word[i]<'0' || word[i]>'9') return FALSE;//全为数字，否则false
      }
      return TRUE;//通过考验，true
    }
    else{//负数情况，同上
      if(word[1] == 0) range = 11;
      else range = 10; 
      for(int i = 1; word[i]!='\0';i++){
	if(i == range) return FALSE;
        if(word[i]<'0' || word[i]>'9') return FALSE;
      }
      return TRUE;
    }
}


