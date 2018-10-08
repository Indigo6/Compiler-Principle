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

	return lex;
}

BOOL PL0Lex_destroy(PL0Lex * lex)
{
	free(lex);
	return TRUE;
}



BOOL PL0Lex_get_token(PL0Lex * lex)
{
    BOOL _get_token; //Signal for result of getting token, 0 for failure, 1 for success
    lex->start = 0;lex->end = 0;
    _get_token = get_token(lex);
}

BOOL split(PL0Lex *lex, char letter){     // cognize if letter is one of ' ','\t', '\n',
    if(letter == '\t'){
        lex->offset += 4;   
    }
    else if(letter == ' '){
        lex->offset += 1;
    }
    else if(letter == '\n'){
        lex->offset = 0;
    }
    else return 0;
    return 1;
}   //我想把分隔符的offset和linenumber管理放一起

BOOL get_token(PL0Lex * lex){
    char letter;
    BOOL getted = 0; //signal of "has got non-' ','\t','\n' letter or not"
    int cmt = 0;        // signal for comment , 0:no '/', 1:one '/', 2: '//', 3: '/* ...'; 
                        //4:'/* ... *'
    int _split = 0;     // signal for split letter;

    letter = fgec(fin);
    if(lex->offset == 0) lex->line_number++;
    //All line_number' change due to '\n' right after token is handle next time
    /*If '\n' in continuous blank or comment, handled after function 'split' according to
        lex->offset(0 -> line_number+1) */

    while(letter != EOF){
        if(cmt == 1){       // Right after '/'
            if(letter == '/'){  // type '//' comment
                cmt = 2;
                lex->iter = 0;
                getted = 0;
            }
            else if(letter == '*'){  // type '/*' comment
                cmt = 3;
                lex->iter = 0;
                getted = 0;
            }
            else{               //Not a comment;
                lex->end = lex->offset - 1;
                _split = split(lex,letter);
                if(_split == 1){   // Just a divide symbol
                    lex->token[lex->iter]= 0;
                    lex->iter = 0;
                    return 1;
                }
                else{               // Illegal '/...' pattern
                    lex->offset++;
                    lex->token[lex->iter] = letter;
                    lex->iter++;
                    cmt = 0;
                }
            }
        }
        else if(cmt == 2){  // Pattern '// ...'
            if(letter == '\n'){     //Comment type 1 ended
                lex->offset = 0;
                lex->line_number++;
                cmt = 0;
                getted = 0;
            }
        }
        else if(cmt == 3){          // Pattern '/* ...'
            if(letter == '*'){      // Pattern '/* ... *'
                cmt = 4;
                lex->offset++;
            }
            else{                   // Pattern '/* ...'
                _split = split(lex,letter);
                if(_split == 1){
                    if(lex->offset == 0){
                        lex->line_number++;
                    }
                }
                else{
                    lex->offset++;
                }
            }
        }
        else if(cmt == 4){  // Pattern '/* ... *'
            if(letter == '/'){
                lex->offset++;
                cmt = 0;    // Comment tpye 2 ended
            }
            else{
                cmt = 3;    // Back to '/* ...' pattern
                _split = split(lex,letter);
                if(_split == 1){
                    if(lex->offset == 0){
                        lex->line_number++;
                    }
                }
                else{
                    lex->offset++;
                }
            }
        }   
        else{                       //Not in pre_comment or comment pattern
            if(getted == 0){        //Didn't get out of blank yet
                _split = split(lex,letter);
                if(_split == 1){    //Still in blank
                    if(lex->offset == 0)    lex->line_number++;
                }
                else{               // Into token or comment
                    lex->start = lex->offset;
                    lex->offset++;
                    getted = 1;
                    lex->token[lex->iter] = letter;
                    lex->iter++;
                    if(letter == '/'){
                        cmt = 1;    // Get a '/' the first time
                    }
                }
            }
            else{                   //In token 
                lex->end = lex->offset - 1;     //In order to get right offset before function   
                _split = split(lex,letter);     //split() may change lex->offset.
                if(_split == 1){
                    lex->token[iter] = 0;
                    lex->iter = 0;
                    return 1;
                }
                else{
                    if(lex->iter < MAX_TOKEN_LEN){
                        lex->offset++;
                        lex->token[lex->iter] = letter;
                        lex->iter++;
                    }
                    else{
                        // Too long, don't know how to handle?
                    }
                }
            }
        }
        letter = fgec(fin);
    } 
    if(cmt == 1 || (cmt ==0 && getted == 1)){    // If token (include '/') ends with EOF
        lex->end = lex->offset - 1;
        lex->token[iter] = 0;
        lex->iter = 0;
        lex->offset = 0;
        return 1;
    }
    return 0;   // Others: Comment or blank ends with EOF
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
        if(word[i]<'0' || word[i]>'9') return FALSE;//全为数字，否则false
        if(i>8) return FALSE;//超出range，false
      }
      return TRUE;//通过考验，true
    }
    else{//负数情况，同上
      for(int i = 1; word[i]!='\0';i++){
        if(word[i]<'0' || word[i]>'9') return TRUE;
        if(i>9) return FALSE;
      }
      return TRUE;
    }
}
