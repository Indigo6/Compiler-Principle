#include <stdlib.h>
#include "../common/common.h"
#include "pl0_lex.h"
#include <string.h>
#include <ctype.h>
<<<<<<< HEAD
#include "../error/pl0_error.h"
const char * TOKEN_RESERVED_WORDS[NRW] = {"elif","else","var", "const", "procedure", "begin", "end", "if", "then", "do", "while", "call", "odd","return","print"};
const char * TOKEN_SYMBOLS[NSYM] = { "+", "-", "*", "/", "=", "!=", "<", "<=", ">", ">=", "(", ")", ",", ";", ".", ":=" };

int nFlag = 1;
=======

const char * TOKEN_RESERVED_WORDS[NRW] = {"var", "const", "procedure", "begin", "end", "if", "then", "do", "while", "call", "odd"};
const char * TOKEN_SYMBOLS[NSYM] = { "+", "-", "*", "/", "=", "!=", "<", "<=", ">", ">=", "(", ")", ",", ";", ".", ":=" };
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca

PL0Lex * PL0Lex_create(PL0Compiler * parent)
{
	PL0Lex * lex = (PL0Lex *) calloc(1, sizeof(PL0Lex));
	lex->compiler = parent;
	lex->line_number = 1;
	lex->start = 0;
	lex->end = 0;
	lex->offset = 0;
<<<<<<< HEAD
	lex->realoffset  = 0;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
	lex->isEOF = FALSE;
	lex->last_level = 0;
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
    lex->cmmt_error = 0;
    _get_token = get_token(lex);
    if(!_get_token){
        if(lex->overlong){
            lex->last_token_type = TOKEN_NULL;
            return TRUE;
        }
        else if(lex->cmmt_error){
            printf("//The following error comes from unpaired '/*'.\n");
            lex->last_token_type = TOKEN_NULL;
            return TRUE;
        }
<<<<<<< HEAD
        else{ // EOF also return TOKEN_NULL
            lex->last_token_type = TOKEN_NULL;
=======
        else{
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
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
<<<<<<< HEAD
        lex->offset += 4;
        lex->realoffset += 1;
    }
    else if(letter == ' '){
        lex->offset += 1;
        lex->realoffset += 1;
    }
    else if(letter == '\n'){
        lex->offset = 0;
        lex->realoffset = 0;
=======
        lex->offset += 4;   
    }
    else if(letter == ' '){
        lex->offset += 1;
    }
    else if(letter == '\n'){
        lex->offset = 0;
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        lex->line_number++;
    }
    else return 0;
    return 1;
}   //我想把分隔符的offset和linenumber管理放一起

BOOL get_token(PL0Lex * lex){
    char letter;
    int state = 0;
    char sym[3];
    int iter = 0;
    sym[2] = '\0';
<<<<<<< HEAD
    int num_head=0;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
    
    while(1){
        switch(state){
            case 0:{    //Start state
		    	letter = (char)fgetc(fin);
<<<<<<< HEAD
                if(!Islegal(letter)){//Illegal letter
                    lex->offset++;
                    lex->realoffset++;
                    print_error(lex,ERR_UNRECOGNIZED_CHAR);
                    continue;
                }
        	    else if(letter == EOF){  //Begin with EOF, then fail
=======
        	    if(letter == EOF){  //Begin with EOF, then fail
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        	        lex->isEOF = TRUE;
                    return FALSE;
                }
		    	else if(isalnum(letter) || letter == '_'){  //Begin with token
<<<<<<< HEAD
                    if(isdigit(letter)!=0) num_head=1;
		    		state = 1;//跳转到状态s1
                    lex->start = lex->offset++;
                    lex->realoffset ++;
=======
		    		state = 1;//跳转到状态s1
                    lex->start = lex->offset++;
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    lex->token[iter++] = letter;
                }
                else if(Is_split(lex,letter)){  //Begin with split(need to be filtered)
                    //printf("State 0 find split:%c,still state0.\n",letter);
                    continue;
                }
                else{   //Begin with symbol
                    //printf("s0->s2, letter=%d???\n",letter);
                    state = 2;
                    lex->start = lex->offset++;
<<<<<<< HEAD
                    lex->realoffset ++;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    sym[0] = letter;
                }
                break;
            }
            case 1:{
                letter = (char)fgetc(fin);
<<<<<<< HEAD
				if(num_head == 1 && isalpha(letter)!=0){
					print_error(lex,ERR_WRONG_IDEN_FORMAT);
					num_head = 0;	
				}
                if(isalnum(letter) || letter=='_'){//token
                    state = 1;//跳转到状态s1
                    lex->offset++;//行内位置++
                    lex->realoffset++;
                    if(iter > MAX_TOKEN_LEN){//长度超标
                        lex->overlong = 1;			
						print_error(lex, ERR_TOO_LONG_IDEN_OR_NUM);
=======
                if(isalnum(letter) || letter=='_'){//token
                    state = 1;//跳转到状态s1
                    lex->offset++;//行内位置++
                    if(iter > MAX_TOKEN_LEN){//长度超标
                        lex->overlong = 1;
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                        lex->token[0]='\0';//暂存数组首位置空
                        iter = 0;//暂存数组指针指向首位
                        while(1){
                            letter = (char)fgetc(fin);
                            if(isalnum(letter) || letter=='_'){//跳过之后的一串token
                                lex->offset++;
<<<<<<< HEAD
                                lex->realoffset++;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                                continue;	
                            }
                            else if(letter == EOF){
                                lex->isEOF = 1;
                                return FALSE;
                            }
                            else{
                                fseek(fin,-1,SEEK_CUR);//读至分隔符或符号，回退一位
                                return FALSE;
                            }
                        }
                    }
                    lex->token[iter] = letter;//存入暂存数组
                    iter++;//暂存数组的指针++
                    break;//继续该状态循环读入token
                }
                else{//symbol或分隔符
<<<<<<< HEAD
                    nFlag = 0;
                    if(letter == EOF)  lex->isEOF = TRUE;
                    lex->end = lex->offset - 1;// 回退
                    lex->token[iter] = '\0';
                    if(!Islegal(letter)){//Illegal letter
                        print_error(lex,ERR_UNRECOGNIZED_CHAR);
                        lex->offset++;
                        lex->realoffset++;
                        return TRUE;
                    }
=======
                    if(letter == EOF)  lex->isEOF = TRUE;
                    lex->end = lex->offset - 1;// 回退
                    lex->token[iter] = '\0';
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    if(letter != EOF)   fseek(fin,-1,SEEK_CUR);//EOF no 回退
                    //printf("Return from s1.\n");
                    return TRUE;
                }
            }
            case 2:{
                sym[1] = (char)fgetc(fin);
<<<<<<< HEAD
                if(sym[0]=='-' && isdigit(sym[1]) && nFlag > 0){
                    state = 1;
                    lex->offset++;//行内位置++
                    lex->realoffset++;
                    lex->token[iter++] = sym[0];
                    lex->token[iter++] = sym[1];
                    continue;
                }
				if(sym[0]==':' && sym[1]!='='){//err := 
					print_error(lex,ERR_COLON_EXPECT_EQUAL);
					fseek(fin, -1, SEEK_CUR);					
					lex->token[0] = sym[0];
                    lex->token[1] = '=';
                    lex->token[2] = '\0';
                    lex->end = lex->offset - 1;
                    //printf("Return from s3-> one symbol.\n");
                    nFlag = 1;
                    return TRUE;
				}
				if(sym[0]=='!' && sym[1]!='='){//err != 
					print_error(lex,ERR_EXCLAMATION_EXPECT_EQUAL);
					fseek(fin, -1, SEEK_CUR);
					lex->token[0] = sym[0];
                    lex->token[1] = '=';
                    lex->token[2] = '\0';
                    lex->end = lex->offset - 1;
                    //printf("Return from s3-> one symbol.\n");
                    nFlag = 1;
                    return TRUE;				
				}
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                if(sym[1]==EOF){    //One symbol end with EOF
                    lex->token[0] = sym[0];
                    lex->token[1] = '\0';
                    lex->end = lex->offset - 1;
                    lex->isEOF = TRUE;
                    //printf("Return from s2->EOF.\n");
                    return TRUE;
                }
<<<<<<< HEAD
                else if(!Islegal(letter)){//Illegal letter
                    print_error(lex,ERR_UNRECOGNIZED_CHAR);
                    lex->token[0] = sym[0];
                    lex->token[1] = '\0';
                    lex->end = lex->offset - 1;
                    lex->offset++;
                    lex->realoffset++;
                    nFlag = 1;
                    return TRUE;
                }
                else{
                    lex->offset ++;
                    lex->realoffset++;
=======
                else{
                    lex->offset ++;
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    if(is_symbol(sym+1)!=-1){   //Two symbols, need to follow longest-pattern-rule
                        state = 3;
                        continue;
                    } 
                    else{   //One symbol, end with other character
<<<<<<< HEAD
                        if(sym[0]==')') nFlag = 0;
                        else nFlag = 1;
                        fseek(fin, -1, SEEK_CUR);
                        lex->offset --;
                        lex->realoffset--;
=======
                        fseek(fin, -1, SEEK_CUR);
                        lex->offset --;
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                        lex->end = lex->offset - 1;
                        lex->token[0] = sym[0];
                        lex->token[1] = '\0';
                        //printf("Return from s2->valid symbol.\n");
                        return TRUE;
                    }
                }
            }
            case 3:{
                if(is_symbol(sym)!=-1){ //Check if len-two-symbol is valid
                    lex->token[0] = sym[0];
                    lex->token[1] = sym[1];
                    lex->token[2] = '\0';
                    lex->end = lex->offset - 1;
                    //printf("Return from s3-> one symbol.\n");
<<<<<<< HEAD
                    nFlag = 1;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    return TRUE;
                }
                else if(sym[0]=='/' && sym[1]=='/'){    //Comment type 1
                    state = 4;
                }
                else if(sym[0]=='/' && sym[1] == '*'){  //Comment type 2
                    lex->start = lex->offset - 2;
                    lex->end = lex->offset - 1;
                    state =5;
                }
                else{   // len-two-symbol is invalid, then symbol len 1
                    fseek(fin,-1,SEEK_CUR);
                    lex->offset --;
<<<<<<< HEAD
                    lex->realoffset--;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    lex->token[0] = sym[0];
                    lex->token[1] = '\0';
                    lex->end = lex->offset - 1;
                    //printf("Return from s3->two symbol.\n");
<<<<<<< HEAD
                    nFlag = 0;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    return TRUE;
                }
                break;
            }
            case 4:{    //Comment '//' type
<<<<<<< HEAD
                letter = (char)fgetc(fin);//no need to maintain offset
=======
                letter = (char)fgetc(fin);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                if(letter == '\n'){
                    state = 0;
                    lex->line_number++;
                    lex->offset = 0;
<<<<<<< HEAD
                    lex->realoffset=0;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                }
                else if(letter == EOF){
                    lex -> isEOF = TRUE;
                    return FALSE;
                }
                break;
            }
            case 5:{    //Comment '/*' type
                letter = (char)fgetc(fin);
                if(letter == '*'){  //Hope to meet '*/'
                    state = 6;
                    lex->offset++;
<<<<<<< HEAD
                    lex->realoffset++;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    continue;
                }
                else if(letter == EOF){ //Comment character '/*' unpaired
                    lex -> isEOF = TRUE;
                    lex->cmmt_error = TRUE;
<<<<<<< HEAD
                    print_error(lex,ERR_MISS_END_FOR_COMMENT);
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    return FALSE;
                }
                else{
                    if(!Is_split(lex,letter)){  //Still in comment
                        lex->offset++;
<<<<<<< HEAD
                        lex->realoffset++;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    }
                    continue;
                }
            }
            case 6:{
                letter = (char)fgetc(fin);
                if(letter == '/'){  //Meet with '*/', then return to start to find next token
                    state = 0;
                    lex->offset++;
<<<<<<< HEAD
                    lex->realoffset++;
                    nFlag = 1;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    continue;
                }
                else if(letter == EOF){ //Comment character '/*' unpaired
                    lex -> isEOF = TRUE;
                    lex->cmmt_error = TRUE;
                    return FALSE;
                }
                else{
                    state = 5;  //Hope of endding comment failed :(
                    if(!Is_split(lex,letter)){
                        lex->offset++;
<<<<<<< HEAD
                        lex->realoffset++;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    }
                    continue;
                }
            }
        }
    }
}

<<<<<<< HEAD
BOOL Islegal(char letter){
    char temp[2];
    temp[0]=letter;
    temp[1]='\0';
    for(int i = 0;i<NSYM;i++){
        if(strcmp(TOKEN_SYMBOLS[i] ,temp) == 0 ) return 1;
    }
    if(isalnum(letter) || letter==':' || letter=='\t'
        || letter==' ' || letter=='\n' || letter=='!'
                || letter == EOF)
        return 1;
    else    return 0;
}
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca

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
    unsigned int i = 0;
    char c = word[i];
<<<<<<< HEAD
    if(c == '-'){
        if(word[1]!='-' && is_num(word+1))
            return TRUE;
        return FALSE;
    }
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
    while(c != '\0'){
        if(!(c>='0' && c<='9')){
            return FALSE;
        }
        else{
            i ++ ;
            c = word[i];
        }
    }
    if (i>=MAX_NUM_LEN){
        return FALSE;
    }
    else{
        return TRUE;
    }
}

<<<<<<< HEAD
void print_error(PL0Lex* lex, char* errmsg){
    fseek(fin,-1*(lex->realoffset),SEEK_CUR);
    char c[200];
    fscanf(fin,"%[^\n]",c);
    PL0_print_error(errmsg,c,lex->line_number,lex->offset);
    size_t linelen = strlen(c);
    fseek(fin,lex->offset - linelen,SEEK_CUR);
}

=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca

