#include <stdio.h>
#include <stdlib.h>
#include "../common/common.h"
<<<<<<< HEAD
#include "../error/pl0_error.h"
#include "pl0_tax.h"
#include <string.h>
//extern FILE* fout;
// -----
// lexlabel should also update when argument pl0
const char* lexLabel[] = {"P","B","D",".","S","C","V","R","const","A",";","id","=","num","W",",",
                          "V","var","E","H","R","procedure","S","F","M",":=","call","begin",
                          "end","if","O","then","while","do","odd","X","Q","!=","<=",">=",
                          "<",">","T","G","+","-","*","/","Y","Z","(",")","return","I","J","K","THEN_STMT",
                          "ES","EF","elif","else","print"};
//const char* instuctions[] = {"PUT","LD","ST","JMP","JPC","INT","ADD","SUB","MUL","DIV","EQ","LE","LT","GE","GT","AND","OR",};
#define MAX_CODE_LINES 1000
typedef struct{
    char* instruction;
    BOOL hasOp;
    int op;
}code;
code codes[MAX_CODE_LINES];
short offset = 0;
short address = 0;
stack* taxstack ;
int pairL = 0;
int table_index = 0;
int off[10];// all of 'then-stmt' need to jmp to the end of 'if stmt'
//store all code address that need to jmp to the end of 'if stmt'
int count = 0;
/*operations for token table*/
void generate_code(){
    for(short i = 0;i<offset;i++){
        fprintf(fout,"%s",codes[i].instruction);
        if(codes[i].hasOp==TRUE){
            fprintf(fout," %d",codes[i].op);
        }
        fprintf(fout,"\n");
    }
    //fclose(fout);
}
=======
#include "pl0_tax.h"
#include <string.h>


const char* lexLabel[] = {"P","B","D",".","S","C","V","R","const","A",";","id","=","num","W",",",
                          "V","var","E","H","R","procedure","S","F","M",":=","call","begin",
                          "end","if","O","then","while","do","odd","X","Q","!=","<=",">=",
                          "<",">","T","G","+","-","*","/","Y","Z","(",")"};
stack* taxstack ;
int pairFlag = 0;
int table_index = 0;
/*operations for token table*/
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
void table_append(PL0Lex * lex, int kind) {
	strcpy(token_table[table_index].name, lex->last_id);
	token_table[table_index].kind = kind;
	switch (kind) {
		case ID_CONSTANT:
			if (lex->last_num > MAXADDRESS) {
				printf("the number is too great!\n");
				lex->last_num = 0;
			}
			token_table[table_index].value = lex->last_num;
<<<<<<< HEAD
			token_table[table_index].address = address;
			address += 1;   // this address means the constant variable stored in the memory
			break;
		case ID_VARIABLE:
			token_table[table_index].level = lex->last_level;
			token_table[table_index].address = address;
			address += 1;
			break;
		case ID_PROCEDURE:
			token_table[table_index].level = lex->last_level-1;
			token_table[table_index].address = offset;   // this address means the start line number of the procedure in the assembly code file
			                                             // and the offset should be changed in the analysis code not in table append procedure
=======
			break;
		case ID_VARIABLE:
			token_table[table_index].level = lex->last_level;
			break;
		case ID_PROCEDURE:
			token_table[table_index].level = lex->last_level;
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
			break;
	} //switch
	table_index += 1;
} //table_append
<<<<<<< HEAD
BOOL is_defined(const char* id,int kind){
    for(int i = 0; i<=table_index;i++){
        if(kind == token_table[i].kind && strcmp(id,token_table[i].name) == 0){
            return TRUE;
        }
    }
    return FALSE;
}

int indexInTable(const char* id,short level){
    int i = 0;
    for(;i<table_index;i++){
        if(level==token_table[i].level && strcmp(id,token_table[i].name)==0){
            return i;
        }
    }
    for(i=0;i<table_index;i++){
        if(token_table[i].level==1 && strcmp(id,token_table[i].name)==0){
            return i;
        }
    }
    for(i=0;i<table_index;i++){
        if(token_table[i].level==0 && strcmp(id,token_table[i].name)==0){
            return i;
        }
    }
    return -1;
}
=======

>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
void initializestack(stack* s){
    for(int i = 0; i < MAXSTACKSIZE;i++){
        s->Stack[i] = -1;  // because index of lebel tabel can not be minus
    }
    s->length = 0;
}
void destroystack(stack* s){
    free(s);
}

int top(stack* s){
    if(s->length <= 0){
        printf("Stack is empty!");
        return -1;
    }else{
    return s->Stack[s->length];
 }
}

int pop(stack* s){
    if(s->length <= 0){
        printf("Stack is empty!");
        return -1;
    }
    else{
        return s->Stack[--s->length];
    }
}

void push(stack* s, int element){
    if(s->length+1 == MAXSTACKSIZE){
        printf("Stack is full!");
    }
    else{
        s->Stack[s->length++] = element;
    }
}
void print_stack(stack* s){
    for(int i = 0; i< s->length;i++){
        printf("%s ",lexLabel[s->Stack[i]]);
    }
    printf("\n");
}
/*functions for syntax analysis*/

void expression(PL0Lex * lex) {//表达shi X,产生式：X->TG
	//printf("analysis the expression\n");

	pop(taxstack);//rm 'X'
	push(taxstack,43);//G
	push(taxstack,42);//T
	print_stack(taxstack);
<<<<<<< HEAD
	if(lex->last_token_type == TOKEN_COMMA) PL0Lex_get_token(lex);


	if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL){
=======



	if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
	    term(lex);//'T'
	    if(lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS) G(lex);//'G'
	}
	else{
	    //pop(taxstack);
	    //print_stack(taxstack);
	}//some error ...

<<<<<<< HEAD
    if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH ||lex->last_token_type == TOKEN_COMMA) {
        if(lex->last_token_type == TOKEN_COMMA) { return;}
=======
    if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH ) {
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        pop(taxstack);
        print_stack(taxstack);
        return;
    }
    else if(lex->last_token_type == TOKEN_RPAREN){
<<<<<<< HEAD
        if(pairL>=0){
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        else {
            //printf("Unpaired ) at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            print_error(lex,ERR_LEFT_PARENTHESIS_MISS);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                                            ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                            || lex->last_token_type== TOKEN_PRINT
                                            || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type==TOKEN_RETURN));
=======
        if(pairFlag){
            pop(taxstack);
            print_stack(taxstack);
            pairFlag = 0;
            return;
        }
        else {
            printf("Unpaired ) at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE));
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            //Ignore until Follow of F, ';' or '.' or 'end' or F.FIRST.
            pop(taxstack);
            return;
        }
    }
    else {
<<<<<<< HEAD
        //printf("Expected 'X.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
        while(!(lex->last_token_type==TOKEN_PERIOD||
                                         lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                         || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                                        ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                        || lex->last_token_type== TOKEN_PRINT
                                        || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type==TOKEN_RETURN)) PL0Lex_get_token(lex);

=======
        printf("Expected 'X.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
        while(!(lex->last_token_type==TOKEN_PERIOD||
                                         lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                         || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        //Ignore until Follow of F, ';' or '.' or 'end'.or F.first
        pop(taxstack);
        return;
    }
        return;
}

void term(PL0Lex * lex) {//xiang,T->YZ
	//printf("analysis the term\n");

	pop(taxstack);//rm T
	push(taxstack,49);//Z
	push(taxstack,48);//Y
	print_stack(taxstack);


<<<<<<< HEAD
	if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL){
        	factor(lex);//'Y'
        	if(lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_COMMA) {
=======
	if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
        	factor(lex);//'Y'
        	if(lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH) {
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                Z(lex);//'Z'
            }
	}
    else {
<<<<<<< HEAD
        //printf("Expected 'T.FIRST' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
        print_error(lex,ERR_WRONG_BEGIN_OF_FACTOR);
        while(!(lex->last_token_type==TOKEN_PERIOD||
        lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
        || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
        ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
        || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_RETURN
        || lex->last_token_type== TOKEN_PRINT))
            PL0Lex_get_token(lex);

=======
        printf("Expected 'T.FIRST' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
        while(!(lex->last_token_type==TOKEN_PERIOD||
        lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
        || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        //Ignore until Follow of F, ';' or '.' or 'end'.or F.first
        pop(taxstack);
        return;
    }//some error...
<<<<<<< HEAD

=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
    if(lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS
       || lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ
       || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ
       || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ
       || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD
       || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO
<<<<<<< HEAD
       || lex->last_token_type == TOKEN_RPAREN || lex->last_token_type == TOKEN_COMMA)
=======
       || lex->last_token_type == TOKEN_RPAREN)
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
    {
        pop(taxstack);
        print_stack(taxstack);
        return;
    }
    else {
<<<<<<< HEAD
        //printf("Expected 'T.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
        while(!(lex->last_token_type==TOKEN_PERIOD||
                                         lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                         || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                                       ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                       || lex->last_token_type== TOKEN_PRINT
                                       || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type==TOKEN_RETURN)) PL0Lex_get_token(lex);
=======
        printf("Expected 'T.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
        while(!(lex->last_token_type==TOKEN_PERIOD||
                                         lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                         || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        //Ignore until Follow of F, ';' or '.' or 'end'.or F.first
        pop(taxstack);
        return;
    }
	return;
}

void G(PL0Lex * lex){
	if(lex->last_token_type == TOKEN_PLUS){//G->+TG
		pop(taxstack);//rm 'G'
		push(taxstack,43);//G
		push(taxstack,42);//T
		push(taxstack,44);//+
		print_stack(taxstack);
		pop(taxstack);
		print_stack(taxstack);

		PL0Lex_get_token(lex);
<<<<<<< HEAD
		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL){
		    term(lex);//'T'
            codes[offset].instruction="ADD";
            codes[offset].hasOp=FALSE;
            offset++;

=======
		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
		    term(lex);//'T'
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            if(lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS) {
                G(lex);//'G'
            }

            if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {

                return;
			}
            else {
<<<<<<< HEAD
                //printf("Expected 'X.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
                while(!(lex->last_token_type==TOKEN_PERIOD||
                                                 lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                                 || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                                               ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                               || lex->last_token_type== TOKEN_PRINT
                                               || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO)) PL0Lex_get_token(lex);
=======
                printf("Expected 'X.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
                while(!(lex->last_token_type==TOKEN_PERIOD||
                                                 lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                                 || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                //Ignore until Follow of F, ';' or '.' or 'end'.or F.first
                pop(taxstack);
                return;
            }
		}
	}

	else if(lex->last_token_type == TOKEN_MINUS){//G->-TG
		pop(taxstack);//rm 'G'
		push(taxstack,43);//G
		push(taxstack,42);//T
		push(taxstack,45);//-
		print_stack(taxstack);
        pop(taxstack);
        print_stack(taxstack);

		PL0Lex_get_token(lex);
<<<<<<< HEAD
        codes[offset].instruction="ST";
        codes[offset].hasOp=TRUE;
        codes[offset].op = 104;// a ST IN 104
        offset++;
		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL){
		    term(lex);//'T',get b on top
            codes[offset].instruction="LD";
            codes[offset].hasOp=TRUE;
            codes[offset].op = 104;//get a on top
            offset++;

            codes[offset].instruction="SUB";//a-b
            codes[offset].hasOp=FALSE;
            offset++;
=======
		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
		    term(lex);//'T'
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            if(lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS) {
                G(lex);//'G'
            }

            if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {

                return;
			}
			else {
<<<<<<< HEAD
                //printf("Expected 'X.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
                while(!(lex->last_token_type==TOKEN_PERIOD||
                                                 lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                                 || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                                               ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                               || lex->last_token_type== TOKEN_PRINT
                                               || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_RETURN)) PL0Lex_get_token(lex);
=======
                printf("Expected 'X.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
                while(!(lex->last_token_type==TOKEN_PERIOD||
                                                 lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                                 || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                //Ignore until Follow of F, ';' or '.' or 'end'.or F.first
                pop(taxstack);
                return;
            }
		}
	}
	else{
        pop(taxstack);
        print_stack(taxstack);
        return;
	}
	return;
}

void Z(PL0Lex * lex){
	if(lex->last_token_type == TOKEN_TIMES){//Z->*YZ
		pop(taxstack);//rm 'Z'
		push(taxstack,49);//Z
		push(taxstack,48);//Y
		push(taxstack,46);//*
		print_stack(taxstack);
        pop(taxstack);
        print_stack(taxstack);

		PL0Lex_get_token(lex);
<<<<<<< HEAD
		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL){
        		factor(lex);//'Y'
            codes[offset].instruction="MUL";
            codes[offset].hasOp=FALSE;//MUL A,B
            offset++;
=======
		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
        		factor(lex);//'Y'
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca

            if(lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH) {
                Z(lex);//'Z'
            }

            if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_RPAREN || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS ||  lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
                return;
            }
			else {
<<<<<<< HEAD
                //printf("Expected 'Z.FOOLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
                while(!(lex->last_token_type==TOKEN_PERIOD||
                                                 lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                                 || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                                               ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                               || lex->last_token_type== TOKEN_PRINT
                                               || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type==TOKEN_RETURN)) PL0Lex_get_token(lex);
=======
                printf("Expected 'Z.FOOLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
                while(!(lex->last_token_type==TOKEN_PERIOD||
                                                 lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                                 || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                //Ignore until Follow of F, ';' or '.' or 'end'.or F.first
                pop(taxstack);
                pop(taxstack);
                return;
			}
		}
<<<<<<< HEAD
        else {
            //printf("Expected 'T.FIRST' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            print_error(lex,ERR_WRONG_BEGIN_OF_FACTOR);
            while(!(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                    || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                  ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                  || lex->last_token_type== TOKEN_PRINT
                  || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_RETURN)) PL0Lex_get_token(lex);
            //Ignore until Follow of F, ';' or '.' or 'end'.or F.first
            pop(taxstack);
            return;
        }//some error...
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
	}
	else if(lex->last_token_type == TOKEN_SLASH){//Z->/YZ
        pop(taxstack);//rm 'Z'
        push(taxstack,49);//Z
        push(taxstack,48);//Y
<<<<<<< HEAD
        push(taxstack,47);//'/'
=======
        push(taxstack,46);//*
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        print_stack(taxstack);
        pop(taxstack);
        print_stack(taxstack);

        PL0Lex_get_token(lex);
<<<<<<< HEAD

        codes[offset].instruction="ST";
        codes[offset].hasOp=TRUE;
        codes[offset].op = 100;//eg. a/b, then st a into address 100
        offset++;

		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_CALL){
		    factor(lex);//'Y',get b on top

            codes[offset].instruction="LD";
            codes[offset].hasOp=TRUE;
            codes[offset].op = 100;//LD a, now stack: a(top),b(second)
            offset++;

            codes[offset].instruction="DIV";//a/b
            codes[offset].hasOp=FALSE;
            offset++;

=======
		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
		    factor(lex);//'Y'
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            if(lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH) {
                Z(lex);//'Z'
            }
            if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_RPAREN || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS ||  lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
<<<<<<< HEAD
                //pop(taxstack);
                //print_stack(taxstack);
                return;
			}
			else {
                //printf("Expected 'Z.FOOLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
                while(!(lex->last_token_type==TOKEN_PERIOD||
                                                 lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                                 || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                                   ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                   || lex->last_token_type== TOKEN_PRINT
                                   || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_RETURN)) PL0Lex_get_token(lex);
=======

                return;
			}
			else {
                printf("Expected 'Z.FOOLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
                while(!(lex->last_token_type==TOKEN_PERIOD||
                                                 lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                                                 || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                //Ignore until Follow of F, ';' or '.' or 'end'.or F.first
                pop(taxstack);
                pop(taxstack);
                return;
			}
		}
<<<<<<< HEAD
        else {
            //printf("Expected 'T.FIRST' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            print_error(lex,ERR_WRONG_BEGIN_OF_FACTOR);
            while(!(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL
                    || lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                    ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                    || lex->last_token_type== TOKEN_PRINT
                    || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_RETURN)) PL0Lex_get_token(lex);
            //Ignore until Follow of F, ';' or '.' or 'end'.or F.first
            pop(taxstack);
            return;
        }//some error...
	}
	else{
        if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_RPAREN || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS ||  lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN || lex->last_token_type == TOKEN_COMMA) {
            pop(taxstack);//pop z
            print_stack(taxstack);
            return;
        }
        else {
            //printf("Expected 'Z.FOOLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                    lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                    lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                    ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                    || lex->last_token_type== TOKEN_PRINT
                    || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO || lex->last_token_type==TOKEN_RETURN)) PL0Lex_get_token(lex);
=======
	}
	else{
        if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_RPAREN || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS ||  lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
            return;
        }
        else {
            printf("Expected 'Z.FOOLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            //Ignore until Follow of F, ';' or '.' or 'end' or F.FIRST.
            pop(taxstack);
            pop(taxstack);
            return;
        }	}
	return;
}

void factor(PL0Lex * lex) {//yinzi
	//printf("analysis the factor\n");
	if(lex->last_token_type == TOKEN_IDENTIFIER){//Y->id
		pop(taxstack);//rm 'Y'
		push(taxstack,11);//id
		print_stack(taxstack);

<<<<<<< HEAD
        codes[offset].instruction="LD";
        codes[offset].hasOp=TRUE;

        int index = indexInTable(lex->last_id,lex->last_level);
        if(index==-1){
            printf("ERROR:not found in token table\n");
            codes[offset].op = -1;
            offset++;
        }
        else{
            codes[offset].op = token_table[index].address;//LD id.address
            offset++;
        }



		PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN || lex->last_token_type == TOKEN_COMMA) {
=======
		PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            pop(taxstack);//rm 'id'
            print_stack(taxstack);
            return;
        } else {
            if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_RPAREN || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS ||  lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
<<<<<<< HEAD
                pop(taxstack);//rm 'id'
                print_stack(taxstack);
                return;
            }
            else {
                //printf("Expected 'Y.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
                while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                        lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                        lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                       ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                       || lex->last_token_type== TOKEN_PRINT
                       || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO)) PL0Lex_get_token(lex) ;
=======

                return;
            }
            else {
                printf("Expected 'Y.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
                while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                        lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                        lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex) ;
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                //Ignore until Follow of F, ';' or '.' or 'end' or F.FIRST.
                pop(taxstack);
                return;
            }
        }
	}
	else if(lex->last_token_type == TOKEN_NUMBER){//Y->num
		pop(taxstack);//rm 'Y'
		push(taxstack,13);//num
		print_stack(taxstack);

<<<<<<< HEAD
        codes[offset].instruction="PUT";
        codes[offset].hasOp=TRUE;
        codes[offset].op = lex->last_num;//PUT value
        offset++;

		PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN || lex->last_token_type == TOKEN_COMMA) {
=======
		PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            pop(taxstack);
            print_stack(taxstack);
            return;
        } else {
<<<<<<< HEAD
            //printf("Expected 'Y.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                                            ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                            || lex->last_token_type== TOKEN_PRINT
                                            || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO)) PL0Lex_get_token(lex);
=======
            printf("Expected 'Y.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            //Ignore until Follow of F, ';' or '.' or 'end' or F.FIRST.
            pop(taxstack);
            return;
        }
	}
	else if(lex->last_token_type == TOKEN_MINUS){//Y->-X
		pop(taxstack);//rm 'Y'
		push(taxstack,35);//X
		push(taxstack,45);//-
		print_stack(taxstack);

		PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN) {
            expression(lex);//'X'
<<<<<<< HEAD

            codes[offset].instruction="PUT";
            codes[offset].hasOp=TRUE;
            codes[offset].op = 0;//PUT 0
            offset++;

            codes[offset].instruction="SUB";
            codes[offset].hasOp=FALSE;//SUB 0,X   get -x on top
            offset++;
        }
        else {
            print_error(lex,ERR_NEED_EXP_MINUS);
            //printf("Expected expression at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while( !(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                                            ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                            || lex->last_token_type== TOKEN_PRINT
                                            || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO)) PL0Lex_get_token(lex);
=======
        }
        else {
            printf("Expected expression at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while( !(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            //Ignore until Follow of F, ';' or '.' or 'end' or F.FIRST.
            pop(taxstack);
            return;
        }
        if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
            pop(taxstack);
            print_stack(taxstack);
            return;
        } else {
<<<<<<< HEAD
            //printf("Expected 'Y.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                                            ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                            || lex->last_token_type== TOKEN_PRINT
                                            || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO)) PL0Lex_get_token(lex);
=======
            printf("Expected 'Y.FOLLOW' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            //Ignore until Follow of F, ';' or '.' or 'end' or F.FIRST.
            pop(taxstack);
            return;
        }
	}
	else if(lex->last_token_type == TOKEN_LPAREN){//Y->(X)
		pop(taxstack);//rm 'Y'
		push(taxstack,51);//)
		push(taxstack,35);//X
		push(taxstack,50);//(
		print_stack(taxstack);
		pop(taxstack);
		print_stack(taxstack);
<<<<<<< HEAD
        pairL += 1;

		PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER
        || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN
        || lex->last_token_type == TOKEN_CALL) {
            expression(lex);//'X'
        }
        else {
            //printf("Expected expression at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            print_error(lex,ERR_NEED_EXP_PARENTHESIS);
            while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                                            ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                            || lex->last_token_type== TOKEN_PRINT
                                            || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO)) PL0Lex_get_token(lex);
=======
        pairFlag = 1;

		PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN) {
            expression(lex);//'X'
        }
        else {
            printf("Expected expression at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            //Ignore until Follow of F, ';' or '.' or 'end' or F.FIRST.
            pop(taxstack);
            pop(taxstack);
            return;
        }

<<<<<<< HEAD
        if(lex->last_token_type == TOKEN_RPAREN) {//ONLY LEGAL )
            pairL -= 1;
=======

        if(lex->last_token_type == TOKEN_RPAREN) {//ONLY LEGAL )
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            pop(taxstack);
            print_stack(taxstack);
            PL0Lex_get_token(lex);//)
            return;
<<<<<<< HEAD
        } else if(lex->last_token_type == TOKEN_SEMICOLON){
            if(pairL < 0)  print_error(lex,ERR_RIGHT_PARENTHESIS_MISS);
            pairL = 0;
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
	}
	else if(lex->last_token_type == TOKEN_CALL){ // Y -> call id II
	    pop(taxstack);
	    push(taxstack,53);
	    push(taxstack,11);
	    push(taxstack,26); // Y -> call id
	    print_stack(taxstack);
	    pop(taxstack); // remove call
	    print_stack(taxstack);

        int tindex = 0;
        int taddr = 0;
        int toffset = 0;
        int tlevel = 0;

	    PL0Lex_get_token(lex);
	    if(lex->last_token_type == TOKEN_IDENTIFIER){
	        //int addr = token_table[indexInTable(lex->last_id,lex->last_level)].address;//存入函数的生成汇编的行数
	        pop(taxstack); //reduce id
	        print_stack(taxstack);
            //trans part
            tindex = indexInTable(lex->last_id,lex->last_level);
            if(tindex!=-1) {
                taddr = token_table[tindex].address;
            }
            else{
                taddr = -1;
                printf("ERROR:token not found in the table\n");

            }
            tlevel = token_table[tindex].level;
            if(lex->last_level >=1 && tlevel == (lex->last_level - 1)){
                for(int i=0;i<TXMAX;i++){
                    if(token_table[i].level == lex->last_level && token_table[i].kind == ID_VARIABLE){
                        codes[offset].hasOp = 1;
                        codes[offset].instruction = "LD";
                        codes[offset++].op = token_table[i].address;
                    }
                }
            }
            toffset = offset;
            codes[offset].hasOp = 1;
            codes[offset++].instruction = "PUT";
            //trans part

	        PL0Lex_get_token(lex);
	        if(lex->last_token_type == TOKEN_LPAREN) {
                II(lex);
            }
            else if(lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH
                ||lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS
                || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_GTR
                || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_LES
                || lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ
                || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_ELIF
                || lex->last_token_type == TOKEN_ELSE || lex->last_token_type == TOKEN_SEMICOLON
                || lex->last_token_type == TOKEN_END || lex->last_token_type == TOKEN_PERIOD
                || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_RPAREN){
                pop(taxstack);//rm 'I'
                print_stack(taxstack);
            }
            else{

            }

            //trans part
            codes[offset].hasOp = 1;
            codes[offset].instruction = "JMP";
            codes[offset++].op = taddr;
            codes[toffset].op = offset; // PUT return address

            codes[offset].hasOp = 1;//temporally store return-value
            codes[offset].instruction = "ST";
            codes[offset++].op = 105;

            if(lex->last_level >=1 && tlevel == (lex->last_level - 1)){    //recover values of local variables;
                for(int i=TXMAX-1;i>=0;i--){
                    if(token_table[i].level == lex->last_level && token_table[i].kind == ID_VARIABLE){
                        codes[offset].hasOp = 1;
                        codes[offset].instruction = "ST";
                        codes[offset++].op = token_table[i].address;
                    }
                }
            }

            //restore return-value for operations
            codes[offset].hasOp = 1;
            codes[offset].instruction = "LD";
            codes[offset++].op = 105;
            //trans part
	    }
	    else{
	        print_error(lex,ERR_CALL_EXPECT_IDEN);
            while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                    lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                    lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE
                    ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                    || lex->last_token_type== TOKEN_PRINT
                    || lex->last_token_type == TOKEN_WHILE || lex->last_token_type == TOKEN_DO)) PL0Lex_get_token(lex);
	    }
	}

    if(lex->last_token_type == TOKEN_RPAREN && pairL>=0){
        pairL -= 1;
        //return;
    }
	if(lex->last_token_type != TOKEN_SEMICOLON) PL0Lex_get_token(lex);
=======
        } else {
            pairFlag = 0;
            printf("Expected ) at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(!(lex->last_token_type==TOKEN_PERIOD|| lex->last_token_type == TOKEN_SEMICOLON ||
                                             lex->last_token_type==TOKEN_END || lex->last_token_type==TOKEN_IDENTIFIER || lex->last_token_type==TOKEN_CALL ||
                                             lex->last_token_type==TOKEN_BEGIN || lex->last_token_type==TOKEN_IF || lex->last_token_type==TOKEN_WHILE)) PL0Lex_get_token(lex);
            //Ignore until Follow of F, ';' or '.' or 'end' or F.FIRST.
            pop(taxstack);
            return;
        }
	}

	PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
}



void W(PL0Lex* lex){
    if(lex->last_token_type == TOKEN_COMMA){
        int tmp = pop(taxstack); // W -> ,A
        push(taxstack,9);
        push(taxstack,15);
        print_stack(taxstack);
        tmp = pop(taxstack); //reduce ,
        print_stack(taxstack);
        PL0Lex_get_token(lex);
        const_declaration(lex);
    }
    else{//W ->;
        int tmp = pop(taxstack);
        push(taxstack,10);
        print_stack(taxstack);
        pop(taxstack); //pop ;， reduce ;
        print_stack(taxstack);
        //PL0Lex_get_token(lex);
    }
}
void const_declaration(PL0Lex * lex) { //A
	if (lex->last_token_type == TOKEN_IDENTIFIER) {
	    int tmp = pop(taxstack);
<<<<<<< HEAD
	    char* tmpname = lex->last_id;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
	    push(taxstack,14); // A -> id=numW
	    push(taxstack,13);
	    push(taxstack,12);
	    push(taxstack,11);
	    print_stack(taxstack);
	    tmp = pop(taxstack); //reduce id
	    print_stack(taxstack);
		PL0Lex_get_token(lex);
		if (lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_BECOMES) {
			if (lex->last_token_type == TOKEN_BECOMES)
<<<<<<< HEAD
				//printf("found ':=' when expecting '='\n at line %d",lex->line_number);
			    print_error(lex,ERR_IDEN_EXPECT_EQUAL);
=======
				printf("found ':=' when expecting '='\n at line %d",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
			tmp = pop(taxstack); //reduce =
			print_stack(taxstack);
			PL0Lex_get_token(lex);
			if (lex->last_token_type == TOKEN_NUMBER) {
				table_append(lex, ID_CONSTANT);
<<<<<<< HEAD
				codes[offset].instruction = "PUT";
				codes[offset].hasOp = TRUE;
				codes[offset].op = lex->last_num;
				offset++;
				codes[offset].instruction = "ST";
				codes[offset].hasOp = TRUE;
				codes[offset].op = token_table[indexInTable(tmpname,lex->last_level)].address;
				offset++;
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
				tmp = pop(taxstack);
				print_stack(taxstack); // reduce number
				PL0Lex_get_token(lex);
				if(lex->last_token_type!=TOKEN_COMMA && lex->last_token_type!=TOKEN_SEMICOLON){
				    if(lex->last_token_type==TOKEN_VAR||lex->last_token_type==TOKEN_PROCEDURE||
				    lex->last_token_type==TOKEN_CALL||lex->last_token_type==TOKEN_BEGIN||
<<<<<<< HEAD
				    lex->last_token_type==TOKEN_IF||lex->last_token_type==TOKEN_WHILE
                    || lex->last_token_type== TOKEN_PRINT){
                        print_error(lex,ERR_SEMICOLON_MISS);
				        //printf("missing ';' around line %d\n",lex->line_number);
				    }
				    else{
				        print_error(lex,ERR_SEMICOLON_OR_COMMA_MISS);
                    //printf("missing ',' or ';' around line %d\n",lex->line_number);
=======
				    lex->last_token_type==TOKEN_IF||lex->last_token_type==TOKEN_WHILE){
                        printf("missing ';' around line %d\n",lex->line_number);
				    }
				    else{
                    printf("missing ',' or ';' around line %d\n",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
				    }
                    pop(taxstack); // pop W
                    print_stack(taxstack);
                    do{
                        PL0Lex_get_token(lex);
<<<<<<< HEAD
                    }while(lex->last_token_type!=TOKEN_SEMICOLON && lex->isEOF==FALSE);
=======
                    }while(lex->last_token_type!=TOKEN_SEMICOLON);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    return;
				}
				else{
				    W(lex);
				    //PL0Lex_get_token(lex);
				}
			} else {
<<<<<<< HEAD
			    print_error(lex,ERR_IDEN_EXPECT_EQUAL);
				//printf("there must be a number to follow '=' at line %d\n",lex->line_number);
=======
				printf("there must be a number to follow '=' at line %d\n",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
				pop(taxstack); //pop num
				pop(taxstack); // pop W
                //pop(taxstack);
                //do{  // like gcc , skip all token until ";"
                  //  PL0Lex_get_token(lex);
                //}while(lex->last_token_type!=TOKEN_SEMICOLON);
<<<<<<< HEAD
                while(lex->last_token_type!=TOKEN_SEMICOLON && lex->isEOF==FALSE){
=======
                while(lex->last_token_type!=TOKEN_SEMICOLON){
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    PL0Lex_get_token(lex);
                }
                print_stack(taxstack);
                return;
			}
		} else {
<<<<<<< HEAD
		    print_error(lex,ERR_IDEN_EXPECT_EQUAL);
			//printf("there must be an '=' to follow the identifier at line %d\n",lex->line_number);
=======
			printf("there must be an '=' to follow the identifier at line %d\n",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            pop(taxstack);//pop =
            pop(taxstack); //pop num
            pop(taxstack); //pop W
            //do{
              //  PL0Lex_get_token(lex);
            //}while(lex->last_token_type!=TOKEN_SEMICOLON);
<<<<<<< HEAD
            while(lex->last_token_type!=TOKEN_SEMICOLON && lex->isEOF==FALSE){
=======
            while(lex->last_token_type!=TOKEN_SEMICOLON){
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                PL0Lex_get_token(lex);
            }
            print_stack(taxstack);
            return;
		}
	} else {
<<<<<<< HEAD
		//printf("There must be an identifier to follow 'const' at line %d\n",lex->line_number);
		print_error(lex,ERR_CONST_EXPECT_IDEN);
		// ERR_CONST_EXPECT_IDEN
		pop(taxstack);//pop A
		while(lex->last_token_type!=TOKEN_SEMICOLON && lex->isEOF==FALSE){
=======
		printf("There must be an identifier to follow 'const' at line %d\n",lex->line_number);
		pop(taxstack);//pop A
		while(lex->last_token_type!=TOKEN_SEMICOLON){
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
		    PL0Lex_get_token(lex);
		}
		print_stack(taxstack);
        return;
	}

} //const_declaration

void H(PL0Lex * lex){ //H
    if(lex->last_token_type==TOKEN_COMMA){ //H -> ,E
        pop(taxstack);// pop H
        push(taxstack,18);
        push(taxstack,15);
        print_stack(taxstack);
        pop(taxstack); //reduce ,
        PL0Lex_get_token(lex);
        variable_declaration(lex);
    } else{ // H -> ;
        pop(taxstack);
        push(taxstack,10);
        print_stack(taxstack);
        pop(taxstack); //reduce ;
        print_stack(taxstack);

    }
}
void variable_declaration(PL0Lex * lex){ //E
    if(lex->last_token_type == TOKEN_IDENTIFIER){
        pop(taxstack); // E -> idH
        push(taxstack,19);
        push(taxstack,11);
        print_stack(taxstack);
        table_append(lex,ID_VARIABLE);
        pop(taxstack); //reduce id
        print_stack(taxstack);
        PL0Lex_get_token(lex);
        if(lex->last_token_type!=TOKEN_COMMA && lex->last_token_type!=TOKEN_SEMICOLON){
<<<<<<< HEAD
            print_error(lex,ERR_SEMICOLON_OR_COMMA_MISS);
            //printf("missing ',' or ';' around line %d\n",lex->line_number);
            pop(taxstack); //pop H
            do{
                PL0Lex_get_token(lex);
            }while (lex->last_token_type!=TOKEN_SEMICOLON && lex->isEOF==FALSE);
=======
            printf("missing ',' or ';' around line %d\n",lex->line_number);
            pop(taxstack); //pop H
            do{
                PL0Lex_get_token(lex);
            }while (lex->last_token_type!=TOKEN_SEMICOLON);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            PL0Lex_get_token(lex);
            print_stack(taxstack);
            return;
        }
        else{
            H(lex);
        }
    }
    else{
<<<<<<< HEAD
        //printf("There must be an identifier to follow 'var' at line %d\n",lex->line_number);
        print_error(lex,ERR_VAR_EXPECT_IDEN);
        // ERR_VAR_EXPECT_IDEN
=======
        printf("There must be an identifier to follow 'var' at line %d\n",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        pop(taxstack); // pop E
        //do{
          //  PL0Lex_get_token(lex);
        //}while(lex->last_token_type!=TOKEN_SEMICOLON);
<<<<<<< HEAD
        while(lex->last_token_type!=TOKEN_SEMICOLON && lex->isEOF==FALSE){
=======
        while(lex->last_token_type!=TOKEN_SEMICOLON){
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            PL0Lex_get_token(lex);
        }
        print_stack(taxstack);
    }
}//variable_declaration

<<<<<<< HEAD
void procedure_declaration(PL0Lex* lex){ // procedure id I ; B ;
    lex->last_level ++;
    int tmp1 = address;
    codes[offset].instruction = "JMP";
    codes[offset].hasOp = TRUE;
    short tmpoffset = offset;
    offset++;
=======
void procedure_declaration(PL0Lex* lex){ // procedure id ; B ;
    lex->last_level ++;
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
    if(lex->last_token_type == TOKEN_IDENTIFIER){
        //Table * tmptable = malloc(sizeof(Table));
        //strcpy(tmptable->name,lex->last_id);
        //tmptable->level = lex->last_level;
        table_append(lex,ID_PROCEDURE);
        pop(taxstack); // reduce id
        print_stack(taxstack);
<<<<<<< HEAD

        PL0Lex_get_token(lex);//GET FIRST OF I
        if(lex->last_token_type==TOKEN_LPAREN){
            I(lex);
            PL0Lex_get_token(lex);
        }
        else if(lex->last_token_type == TOKEN_SEMICOLON){
            pop(taxstack);//rm 'I'
            print_stack(taxstack);
        }
        else{
            print_error(lex,ERR_PROC_EXPECT_I);
            pop(taxstack);
            print_stack(taxstack);
        }


=======
        PL0Lex_get_token(lex);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        if(lex->last_token_type==TOKEN_SEMICOLON){
            pop(taxstack); // reduce ;
            print_stack(taxstack);
            PL0Lex_get_token(lex);
            if(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
               && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
<<<<<<< HEAD
               lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE
               && lex->last_token_type != TOKEN_PRINT){
=======
               lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE){
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                printf("at the beginning of program block, it must be 'const' or 'var' or 'procedure' or  'identifier' or 'call' or 'if' or 'begin' or 'while'\n ");
                do{
                    PL0Lex_get_token(lex);
                }while(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
                       && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
<<<<<<< HEAD
                       lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE 
                       && lex->last_token_type != TOKEN_PRINT && lex->isEOF==FALSE);
=======
                       lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                block(lex);
                //PL0Lex_get_token(lex);
                if(lex->last_token_type==TOKEN_SEMICOLON){
                    pop(taxstack); // reduce ;
                    print_stack(taxstack);
                }
                else{
                    pop(taxstack);
<<<<<<< HEAD
                    print_error(lex,ERR_SEMICOLON_MISS);
                    //printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
                }
            }
            else{
                int tmp = address-4;
                while(tmp>=tmp1){
                    codes[offset].instruction = "ST";
                    codes[offset].hasOp = TRUE;
                    codes[offset].op = tmp;
                    tmp -= 4;
                    offset += 1;
                }
=======
                    printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
                }
            }
            else{
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                block(lex);
                //PL0Lex_get_token(lex);
                if(lex->last_token_type==TOKEN_SEMICOLON){
                    pop(taxstack); // reduce ;
                    print_stack(taxstack);
                }
                else{
                    pop(taxstack);
<<<<<<< HEAD
                    print_error(lex,ERR_SEMICOLON_MISS);
                    //printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
=======
                    printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                }
            }
        }
        else{
<<<<<<< HEAD
            print_error(lex,ERR_SEMICOLON_MISS);
            //printf("There must be a ';' follow identifier at line %d \n",lex->line_number);
=======
            printf("There must be a ';' follow identifier at line %d \n",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            pop(taxstack); //pop ;
            while (lex->last_token_type!=TOKEN_SEMICOLON){
                PL0Lex_get_token(lex);
            }
            if(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
               && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
<<<<<<< HEAD
               lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE
               && lex->last_token_type != TOKEN_PRINT) {
=======
               lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE) {
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                do{
                    PL0Lex_get_token(lex);
                }while(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
                       && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
<<<<<<< HEAD
                       lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE && 
                       lex->last_token_type != TOKEN_PRINT && lex->isEOF==FALSE);
=======
                       lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                print_stack(taxstack);
                block(lex);
                //PL0Lex_get_token(lex);
                if(lex->last_token_type==TOKEN_SEMICOLON){
                    pop(taxstack); // reduce ;
                    print_stack(taxstack);
                }
                else{
                    pop(taxstack);
<<<<<<< HEAD
                    print_error(lex,ERR_SEMICOLON_MISS);
                    //printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
=======
                    printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                }
            }
            else{
                print_stack(taxstack);
                block(lex);
                //PL0Lex_get_token(lex);
                if(lex->last_token_type==TOKEN_SEMICOLON){
                    pop(taxstack); // reduce ;
                    print_stack(taxstack);
                }
                else{
                    pop(taxstack);
<<<<<<< HEAD
                    print_error(lex,ERR_SEMICOLON_MISS);
                    //printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
=======
                    printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                }
            }

        }
    }
    else{
<<<<<<< HEAD
        //printf("There must be an identifier follow 'procedure' at line %d\n ",lex->line_number);
        print_error(lex,ERR_PROC_EXPECT_IDEN);
        // ERR_PROC_EXPECT_IDEN
        while(lex->last_token_type!=TOKEN_SEMICOLON && lex->isEOF==FALSE){
=======
        printf("There must be an identifier follow 'procedure' at line %d\n ",lex->line_number);
        while(lex->last_token_type!=TOKEN_SEMICOLON){
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            PL0Lex_get_token(lex);
        }
        pop(taxstack); //pop id
        pop(taxstack); //pop ;
        PL0Lex_get_token(lex);
        if(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
           && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
<<<<<<< HEAD
           lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE
           && lex->last_token_type != TOKEN_PRINT) {
=======
           lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE) {
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            do{
                PL0Lex_get_token(lex);
            }while(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
                   && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
<<<<<<< HEAD
                   lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE 
                   && lex->last_token_type != TOKEN_PRINT&& lex->isEOF==FALSE);
=======
                   lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            print_stack(taxstack);
            block(lex);
            //PL0Lex_get_token(lex);
            if(lex->last_token_type==TOKEN_SEMICOLON){
                pop(taxstack); // reduce ;
                print_stack(taxstack);
            }
            else{
                pop(taxstack);
<<<<<<< HEAD
                print_error(lex,ERR_SEMICOLON_MISS);
                //printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
=======
                printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            }
        }
        else{
            print_stack(taxstack);
            block(lex);
            //PL0Lex_get_token(lex);
            if(lex->last_token_type==TOKEN_SEMICOLON){
                pop(taxstack); // reduce ;
                print_stack(taxstack);
            }
            else{
                pop(taxstack);
<<<<<<< HEAD
                print_error(lex,ERR_SEMICOLON_MISS);
                //printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
            }
        }
    }
    codes[tmpoffset].op = offset + 4;
    codes[offset].instruction = "ST";
    codes[offset].hasOp = TRUE;
    codes[offset].op = 100;
    offset++;
    codes[offset].instruction = "PUT";
    codes[offset].hasOp = TRUE;
    codes[offset].op = 0;
    offset++;
    codes[offset].instruction = "LD";
    codes[offset].hasOp = TRUE;
    codes[offset].op = 100;
    offset ++;
    codes[offset].instruction = "JMP";
    codes[offset++].hasOp = FALSE;
    lex -> last_level --;
}

void I(PL0Lex *lex){//I->(J
    pairL +=1;
    pop(taxstack);//reduce I
    push(taxstack,54);//push J
    push(taxstack,50);//push (
    print_stack(taxstack);//I->(J
    pop(taxstack);
    print_stack(taxstack);
    PL0Lex_get_token(lex);
    if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_RPAREN) {
        J(lex);
        //pop(taxstack);
        //print_stack(taxstack);
    }
    else{
        print_error(lex,ERR_PROC_EXPECT_J);
    }

    //if(lex->last_token_type == TOKEN_RPAREN) PL0Lex_get_token(lex);
}

void J(PL0Lex *lex){//J->XK|)
    pop(taxstack);//pop J
    if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN) {//J->XK
        push(taxstack,55);//K
        push(taxstack,35);//X
        print_stack(taxstack);//J->XK
        //expression(lex);//'X' don't need in translate
        table_append(lex, ID_VARIABLE);
        codes[offset].instruction = "ST";
        codes[offset].hasOp = TRUE;
        codes[offset++].op = token_table[indexInTable(lex->last_id,lex->last_level)].address;
        PL0Lex_get_token(lex);
        //PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_COMMA || lex->last_token_type == TOKEN_RPAREN){
            K(lex);

        }
        else{
            //need fix
        }
    }
    else {//J->)
        push(taxstack,51);//push )
        print_stack(taxstack);
        pop(taxstack);
        PL0Lex_get_token(lex);
    }
}

void K(PL0Lex *lex){
    pop(taxstack);//reduce K
    if(lex->last_token_type == TOKEN_RPAREN){//K->)
        push(taxstack,51);//push )
        print_stack(taxstack);
        pop(taxstack);
        print_stack(taxstack);
    }
    else{//K-> ,XK
        push(taxstack,55);//K
        push(taxstack,35);//X
        push(taxstack,15);//,
        print_stack(taxstack);
        pop(taxstack);//pop ,
        print_stack(taxstack);
        //expression(lex);//'X'
        PL0Lex_get_token(lex);
        table_append(lex,ID_VARIABLE);
        codes[offset].instruction = "ST";
        codes[offset].hasOp = TRUE;
        codes[offset++].op = token_table[indexInTable(lex->last_id,lex->last_level)].address;
        PL0Lex_get_token(lex);
        //PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_COMMA || lex->last_token_type == TOKEN_RPAREN){
            K(lex);

        }
        else{
            //need fix
        }
    }
}

void II(PL0Lex *lex){//I->(J
    pairL +=1;
    pop(taxstack);//reduce I
    push(taxstack,54);//push J
    push(taxstack,50);//push (
    print_stack(taxstack);//I->(J
    pop(taxstack);
    print_stack(taxstack);
    PL0Lex_get_token(lex);
    if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type == TOKEN_RPAREN) {
        JJ(lex);
        //pop(taxstack);
        //print_stack(taxstack);
    }
    else{
        print_error(lex,ERR_PROC_EXPECT_J);
    }

    //if(lex->last_token_type == TOKEN_RPAREN) PL0Lex_get_token(lex);
}

void JJ(PL0Lex *lex){//J->XK|)
    pop(taxstack);//pop J
    if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN) {//J->XK
        push(taxstack,55);//K
        push(taxstack,35);//X
        print_stack(taxstack);//J->XK
        expression(lex);//'X'

        //PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_COMMA || lex->last_token_type == TOKEN_RPAREN){
            KK(lex);

        }
        else{
            //need fix
        }
    }
    else {//J->)
        push(taxstack,51);//push )
        print_stack(taxstack);
        pop(taxstack);
        PL0Lex_get_token(lex);
    }
}

void KK(PL0Lex *lex){
    pop(taxstack);//reduce K
    if(lex->last_token_type == TOKEN_RPAREN){//K->)
        push(taxstack,51);//push )
        print_stack(taxstack);
        pop(taxstack);
        print_stack(taxstack);
    }
    else{//K-> ,XK
        push(taxstack,55);//K
        push(taxstack,35);//X
        push(taxstack,15);//,
        print_stack(taxstack);
        pop(taxstack);//pop ,
        print_stack(taxstack);

        expression(lex);//'X'

        //PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_COMMA || lex->last_token_type == TOKEN_RPAREN){
            KK(lex);

        }
        else{
            //need fix
        }
    }
}

=======
                printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
            }
        }
    }
    lex -> last_level --;
}
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
void block(PL0Lex *lex){ // B
    pop(taxstack); //pop B
    // because FIRST(P) = FIRST(B)
    push(taxstack,23);
    push(taxstack,2);
    print_stack(taxstack); // B -> DF
    do{//D
        if (lex->last_token_type == TOKEN_CONST) {
            push(taxstack, 5); // D -> CD
            print_stack(taxstack);
            pop(taxstack);
            push(taxstack,9); // C -> constA
            push(taxstack,8);
            print_stack(taxstack);
            pop(taxstack); // reduce const
            print_stack(taxstack);
            PL0Lex_get_token(lex);
            const_declaration(lex);
            PL0Lex_get_token(lex);
            /*while (lex->last_token_type == TOKEN_COMMA) {
                PL0Lex_get_token(lex);
                const_declaration(lex);
            }
            if (lex->last_token_type == TOKEN_SEMICOLON) {
                PL0Lex_get_token(lex);
            }
            else {
                printf("missing ',' or ';'\n");
            }*/
        } else if(lex->last_token_type == TOKEN_VAR){//D -> VD
            push(taxstack,6);
            print_stack(taxstack);
            pop(taxstack); //V -> var E
            push(taxstack,18);
            push(taxstack,17);
            print_stack(taxstack);
            pop(taxstack);//reduce var
            print_stack(taxstack);
            PL0Lex_get_token(lex);
            variable_declaration(lex);
            PL0Lex_get_token(lex);
            /*while (lex->last_token_type == TOKEN_COMMA){
                PL0Lex_get_token(lex);
                varible_declaration(lex);
            }*/
        } else if(lex -> last_token_type == TOKEN_PROCEDURE){ //D->RD
<<<<<<< HEAD
            push(taxstack,7);
            print_stack(taxstack);
            pop(taxstack); // R -> procedure id I;B;
            push(taxstack,10);
            push(taxstack,1); //push B
            push(taxstack,10); // push ;
            push(taxstack,53); // push I
=======
            push(taxstack,10);
            print_stack(taxstack);
            pop(taxstack); // R -> procedure id;B;
            push(taxstack,10);
            push(taxstack,1); //push B
            push(taxstack,10); // push ;
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            push(taxstack,11); // push id
            push(taxstack,21); // push procedure
            print_stack(taxstack);
            pop(taxstack); //reduce procedure
            print_stack(taxstack);
            PL0Lex_get_token(lex);
            procedure_declaration(lex);
<<<<<<< HEAD
            /*if(lex->last_token_type == TOKEN_SEMICOLON)//because I don't know what 'procedure_declaration' return with
                pop(taxstack);//pop ';'
            print_stack(taxstack);*/
            PL0Lex_get_token(lex);
        }
        else{ // then should determine if it is in the FIRST of F, or it has an error
=======
            PL0Lex_get_token(lex);
        }
        else{ // then should determine if it is in the FIRST of F, then it has an error
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            //D -> epsilon
            pop(taxstack); // D reduced by epsilon
            print_stack(taxstack);
            //PL0Lex_get_token(lex); // don't need get another token
            break;
        }
    } while(TRUE);//while(lex->last_token_type == TOKEN_CONST
    // || lex->last_token_type == TOKEN_VAR || lex->last_token_type == TOKEN_PROCEDURE);

    // !!!------  F should be written below here ------ !!!
    if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
        || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
<<<<<<< HEAD
        lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_DO || 
        lex->last_token_type == TOKEN_RETURN || lex->last_token_type==TOKEN_PRINT){
=======
        lex->last_token_type == TOKEN_CALL){
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            statement(lex);
    }
    else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON){
        printf("Warning: block without statement.\n");//No legal statement after declaration
    }
<<<<<<< HEAD
    else {
        printf("Illegal statement.\n");//No legal statement after declaration
        PL0Lex_get_token(lex);
        if (lex->last_token_type != TOKEN_PERIOD && lex->last_token_type != TOKEN_SEMICOLON) {
            printf("Excess element after block.\n");
            while (PL0Lex_get_token(lex) && !(lex->last_token_type == TOKEN_PERIOD ||
                                              lex->last_token_type ==
                                              TOKEN_SEMICOLON));//Ignore until Follow of F, ';' or '.'
        }
    }
=======
    else{
        printf("Illegal statement.\n");//No legal statement after declaration
        PL0Lex_get_token(lex);
        if(lex->last_token_type != TOKEN_PERIOD && lex->last_token_type != TOKEN_SEMICOLON){
            printf("Excess element after 'call'.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                lex->last_token_type == TOKEN_SEMICOLON));//Ignore until Follow of F, ';' or '.'
        }
    }
    return;
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
}
void program_block(PL0Lex * lex) { // P -> B .
    taxstack = (stack*)malloc(sizeof(stack));
    initializestack(taxstack);
	printf("analysis the program block\n");
	// PL0Lex * lex = (PL0Lex *) calloc(1, sizeof(PL0Lex));
	// PL0Lex_get_token(lex);
	push(taxstack,0); // p
	print_stack(taxstack);
    //int tmp = pop(taxstack);// pop P
    //push(taxstack,3);
    //PL0Lex_get_token(lex);
    // if not in the FIRST set of P and FIRST set of B
<<<<<<< HEAD
    //codes[offset].instruction = "JMP";
    //codes[offset].hasOp = TRUE;
    //offset++;
    for(int i=0;i<10;i++)
        off[i] = -1;
    if(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
    && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
    lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE&&lex->last_token_type!=TOKEN_DO&&lex->last_token_type!=TOKEN_RETURN
    &&lex->last_token_type!=TOKEN_PRINT){
        printf("at the beginning of program, it must be 'const' or 'var' or 'procedure' or  'identifier' or 'call' or 'if' or 'begin' or 'while' or 'do' or 'return' or 'print'\n ");
        do{
            PL0Lex_get_token(lex);
            if(lex->isEOF==TRUE){
                return;
            }
        }while(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
               && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
               lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE
               && lex->last_token_type!=TOKEN_DO&&lex->last_token_type!=TOKEN_RETURN
               &&lex->last_token_type!=TOKEN_PRINT);
=======
    if(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
    && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
    lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE){
        printf("at the beginning of program, it must be 'const' or 'var' or 'procedure' or  'identifier' or 'call' or 'if' or 'begin' or 'while'\n ");
        do{
            PL0Lex_get_token(lex);
        }while(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
               && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
               lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
    }
    pop(taxstack); // pop P
    push(taxstack,3); // push .
    push(taxstack,1); //push B
    print_stack(taxstack);
    block(lex); //B
    //PL0Lex_get_token(lex);
<<<<<<< HEAD
=======
    while(PL0Lex_get_token(lex) && (lex->last_token_type!=TOKEN_PERIOD));//Ignore until period(in case illegal stmt)
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
    if(lex->last_token_type==TOKEN_PERIOD){
        pop(taxstack); // pop .
        print_stack(taxstack);
        printf("analysis end1");
    }
    else{
<<<<<<< HEAD
        printf("Illegal words after 'block' in 'program',line:%d\n",lex->line_number);
        while(PL0Lex_get_token(lex) && (lex->last_token_type!=TOKEN_PERIOD));//Ignore until period(in case illegal stmt)
        if(lex->last_token_type==TOKEN_PERIOD){
            pop(taxstack); // pop .
            print_stack(taxstack);
            printf("analysis end1");
        }
        else{
            print_error(lex,ERR_DOT_MISS);
        }
    }
    codes[offset].instruction = "INT";
    codes[offset].hasOp = TRUE;
    codes[offset].op = 1;
    offset++;
    generate_code();
=======
        printf("there must an '.' in the program block end \n");
    }
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
destroystack(taxstack);
} //program_block

void statement(PL0Lex * lex){ //analysis the statement F, return only when meet 'FOLLOW' of F
    if(lex->last_token_type == TOKEN_IDENTIFIER){// F-> id := X
        pop(taxstack);
        push(taxstack,35);//X
        push(taxstack,25);//:=
        push(taxstack,11);//id
        print_stack(taxstack);
        pop(taxstack);//rm 'id'
        print_stack(taxstack);
<<<<<<< HEAD

        int tindex = indexInTable(lex->last_id,lex->last_level);
        int taddr = token_table[tindex].address;

        PL0Lex_get_token(lex);

        if(lex->last_token_type != TOKEN_BECOMES){
            //print_error(lex,ERR_ASSIGN_EXPECT_IDEN);//"Expected ':='
            printf("Expect an ':=' after indentifier.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END ||
                lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                || lex->last_token_type == TOKEN_WHILE));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
=======
        PL0Lex_get_token(lex);
        if(lex->last_token_type != TOKEN_BECOMES){
            printf("Expected ':=' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);
            pop(taxstack);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            return;
        }
        pop(taxstack);//rm ':='
        print_stack(taxstack);
        PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER
<<<<<<< HEAD
            || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN
            || lex->last_token_type == TOKEN_CALL){
            expression(lex); //expression must return with ';' or '.'

            //trans part
            codes[offset].hasOp = 1;
            codes[offset].instruction = "ST";
            codes[offset++].op = taddr;
            //trans part
        }
        else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            || lex->last_token_type==TOKEN_END||
               lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
               || lex->last_token_type == TOKEN_WHILE){
            printf("'become' statement without expression.\n");
            pop(taxstack);//rm 'X'
            print_stack(taxstack);
            return;
=======
            || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
            expression(lex); //expression must return with ';' or '.'
        }
        else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            || lex->last_token_type==TOKEN_END){
            printf("'become' statement without expression.\n");
            pop(taxstack);//rm 'X'
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        }
        else{
            printf("'become' statement with illegal expression.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
<<<<<<< HEAD
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                   lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);//rm 'X'
            print_stack(taxstack);
            return;
        }
        //after 'expression'
        if(!(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            ||lex->last_token_type == TOKEN_END||
              lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
              || lex->last_token_type == TOKEN_WHILE))
        {
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                   lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE));
        }

        return;
    }
    else if(lex->last_token_type == TOKEN_PRINT){ // print statement， really easy to translate
        pop(taxstack);
        push(taxstack,35);
        push(taxstack,61);
        print_stack(taxstack);
        pop(taxstack); // rm 'print'
        print_stack(taxstack);
        PL0Lex_get_token(lex);

        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER
            || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN
            || lex->last_token_type == TOKEN_CALL){
            expression(lex); //expression must return with ';' or '.'

            //trans part
            codes[offset].hasOp = 1;
            codes[offset].instruction = "INT";
            codes[offset++].op = 0;
            codes[offset].hasOp = 1;
            codes[offset].instruction = "ST";
            codes[offset++].op = 101;
            //trans part

        }
        else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            || lex->last_token_type==TOKEN_END||
               lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
               || lex->last_token_type == TOKEN_WHILE){
            printf("'print' statement without expression.\n");
            pop(taxstack);//rm 'X'
            print_stack(taxstack);
            return;
        }
        else{
            printf("'print' statement with illegal expression.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                   lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);//rm 'X'
            print_stack(taxstack);
            return;
        }
        //after 'expression'
        if(!(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            ||lex->last_token_type == TOKEN_END||
              lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
              || lex->last_token_type == TOKEN_WHILE))
        {
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                   lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE));
        }
        return;
    }
    else if(lex->last_token_type == TOKEN_CALL){//F->call id I
        pop(taxstack);
        push(taxstack,53);
=======
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);//rm 'X'
        }
        return; 
    }
    else if(lex->last_token_type == TOKEN_CALL){//F->call id
        pop(taxstack);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        push(taxstack,11);
        push(taxstack,26);
        print_stack(taxstack);
        pop(taxstack); // rm 'call'
        print_stack(taxstack);
        PL0Lex_get_token(lex);
<<<<<<< HEAD
        int tindex = 0;
        int taddr = 0;
        int toffset = 0;
        int tlevel = 0;

        if(lex->last_token_type != TOKEN_IDENTIFIER){
            print_error(lex,ERR_CALL_EXPECT_IDEN);//Expected identifier 
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END ||
                   lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
        }
        else{// after ensure 'id'
            pop(taxstack);
            print_stack(taxstack);

            //trans part
            tindex = indexInTable(lex->last_id,lex->last_level);
            if(tindex!=-1) {
                taddr = token_table[tindex].address;
            }
            else{
                printf("ERROR:token not found in table\n");
                taddr=-1;
            }
            tlevel = token_table[tindex].level;
            if(lex->last_level >=1 && tlevel == (lex->last_level - 1)){
                for(int i=0;i<TXMAX;i++){
                    if(token_table[i].level == lex->last_level && token_table[i].kind == ID_VARIABLE){
                        codes[offset].hasOp = 1;
                        codes[offset].instruction = "LD";
                        codes[offset++].op = token_table[i].address;
                    }
                }
            }
            toffset = offset;
            codes[offset].hasOp = 1;
            codes[offset++].instruction = "PUT";
            //trans part
        
            PL0Lex_get_token(lex);
            if(lex->last_token_type == TOKEN_LPAREN)
                II(lex);
            else if(lex->last_token_type == TOKEN_SEMICOLON){
                pop(taxstack); // rm 'I'
                print_stack(taxstack);
            }
            else{
                print_error(lex,ERR_LEFT_PARENTHESIS_MISS);
                pop(taxstack);//pop 'I'
                print_stack(taxstack);
            }
            if(lex->last_token_type == TOKEN_RPAREN){
                PL0Lex_get_token(lex);// becasue I don't know what 'I' return with. It's )
            }
            if(lex->last_token_type != TOKEN_PERIOD && lex->last_token_type != TOKEN_SEMICOLON){
                //print_error(lex,ERR_SEMICOLON_OR_COMMA_MISS);//Expected ';' or '.'
                print_error(lex,ERR_SEMICOLON_OR_PERIOD);
                while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                                                 lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                                                 lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                                 || lex->last_token_type == TOKEN_WHILE
                ));
                //Ignore until Follow of F, ';' or '.' or 'end'.
            }
            
        }

        //trans part
        codes[offset].hasOp = 1;
        codes[offset].instruction = "JMP";
        codes[offset++].op = taddr;
        codes[toffset].op = offset; // PUT return address

        // 'call id' stmt needs no return-value
        codes[offset].hasOp = 1;
        codes[offset].instruction = "ST";
        codes[offset++].op = 100;

        if(lex->last_level >=1&& tlevel == (lex->last_level - 1)){    //recover values of local variables;
            for(int i=TXMAX-1;i>=0;i--){
                if(token_table[i].level == lex->last_level && token_table[i].kind == ID_VARIABLE){
                    codes[offset].hasOp = 1;
                    codes[offset].instruction = "ST";
                    codes[offset++].op = token_table[i].address;
                }
            }
        }
        //trans part

=======
        if(lex->last_token_type != TOKEN_IDENTIFIER){
            printf("Expected identifier at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
        }
        else{// Process when to return
            PL0Lex_get_token(lex);
            if(lex->last_token_type != TOKEN_PERIOD && lex->last_token_type != TOKEN_SEMICOLON){
                printf("Expected ';' or '.'.\n");
                while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            }
        }
        pop(taxstack);// rm 'id'
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        return;
    }
    else if(lex->last_token_type == TOKEN_BEGIN){//F->begin S end
        pop(taxstack);
        push(taxstack,28);
        push(taxstack,4);
        push(taxstack,27);
        print_stack(taxstack);
        pop(taxstack);//rm 'begin'
        print_stack(taxstack);
<<<<<<< HEAD

        statements(lex);//Anyway go to statements, because there may be legal stmt after il-stmt in stmts
        //PL0Lex_get_token(lex);
        if(lex->last_token_type != TOKEN_END) // stmts reutrn because of '.'
            print_error(lex,ERR_NEED_END_FOR_BEGIN);//Expected 'end' 
        else{//stmts reutrn because of 'end'
            PL0Lex_get_token(lex);
            if(!(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
               || lex->last_token_type==TOKEN_END ||lex->last_token_type == TOKEN_ELIF
               || lex->last_token_type == TOKEN_ELSE|| lex->last_token_type == TOKEN_WHILE)){
                //print_error(lex,ERR_SEMICOLON_OR_COMMA_MISS);//Expected ';' or '.'
                while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                   ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE
                   ));
=======
        statements(lex);//Anyway go to statements, because there may be legal stmt after il-stmt in stmts
        //PL0Lex_get_token(lex);
        if(lex->last_token_type != TOKEN_END) // stmts reutrn because of '.'
            printf("Expected 'end' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
        else{//stmts reutrn because of 'end'
            PL0Lex_get_token(lex);
            if(lex->last_token_type != TOKEN_PERIOD && lex->last_token_type != TOKEN_SEMICOLON){
                printf("Expected ';' or '.'.\n");
                while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            }
        }
        pop(taxstack);//rm 'end'
        print_stack(taxstack);
        return;
    }
    else if(lex->last_token_type == TOKEN_IF){//F->if condition then S
        pop(taxstack);
<<<<<<< HEAD
        push(taxstack,58);//push 'ELSE_STMT'
        push(taxstack,57);//push 'ELIF_STMT'
        push(taxstack,23);//push 'F'
        push(taxstack,31);//push 'then'
        push(taxstack,30);//push 'O'
        push(taxstack,29);//push 'if'
=======
        push(taxstack,23);
        push(taxstack,31);
        push(taxstack,30);
        push(taxstack,29);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        print_stack(taxstack);
        pop(taxstack);//rm 'if'
        print_stack(taxstack);
        PL0Lex_get_token(lex);
<<<<<<< HEAD
        int tindex = 0;
        int taddr = 0;
        int toffset = 0;

=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        if(lex->last_token_type == TOKEN_ODD || lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
                condition(lex);
        }
<<<<<<< HEAD
        else if(lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE){
            printf("missing 'condition'&'then'&'statement' after 'if',line:%d.\n",lex->line_number);
            pop(taxstack);//pop 'O'
            print_stack(taxstack);
        }
        else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_END
            || lex->last_token_type ==TOKEN_SEMICOLON
               || lex->last_token_type == TOKEN_WHILE){
            printf("statement with only 'if',line:%d.\n",lex->line_number);
            pop(taxstack);
            pop(taxstack);
=======
        else if(lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_PERIOD
            || lex->last_token_type == TOKEN_END){
            printf("missing 'condition'&'then'&'statement' after 'if',line:%d.\n",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            pop(taxstack);
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        else if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
                || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
                lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_THEN){
            printf("missing 'condition' after 'if',line:%d.\n",lex->line_number);
            pop(taxstack);//rm 'condition'
            print_stack(taxstack);
        }
        else{
<<<<<<< HEAD
            print_error(lex,ERR_WRONG_BEGIN_OF_COND);//missing 'condition' after 'if'
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                    || lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                    || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_WHILE));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            if(lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE ||
                lex->last_token_type == TOKEN_THEN){
                pop(taxstack);//pop 'O'
            }
            else{
                pop(taxstack);
                pop(taxstack);
                pop(taxstack);
                pop(taxstack);
                pop(taxstack);
                print_stack(taxstack);
                return;
            }
        }
        //before then
   
        //trans part
        codes[offset++].instruction = "NOT";
        toffset = offset;
        codes[offset].hasOp = 1;
        codes[offset++].instruction = "JPC";
        //trans part

        if(lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_PERIOD
            || lex->last_token_type == TOKEN_END || lex->last_token_type == TOKEN_WHILE){
            // condition reutrn because of ';' or '.' or 'end'
            printf("'if' expression with only 'if'&'condition',line:%d.\n",lex->line_number);
            pop(taxstack);
=======
            printf("missing 'condition' after 'if',line:%d.\n",lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            pop(taxstack);
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
<<<<<<< HEAD
        else if(lex->last_token_type == TOKEN_ELSE || lex->last_token_type == TOKEN_ELIF){
            printf("missing &'then'&'statement' after 'if condition',line:%d.\n",lex->line_number);
            pop(taxstack);//pop 'then'
            print_stack(taxstack);
        }
=======
        if(lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_PERIOD
            ||lex->last_token_type == TOKEN_END){
            // condition reutrn because of ';' or '.' or 'end'
            printf("'if' expression without 'then'&'statement',line:%d.\n",lex->line_number);
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }           
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        else if(lex->last_token_type == TOKEN_THEN){
            // condition reutrn because of 'then', or 'then' after 'if'
            pop(taxstack);
            print_stack(taxstack);
            PL0Lex_get_token(lex);
        }
        else if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
                || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
<<<<<<< HEAD
                lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_DO){
            print_error(lex,ERR_NEED_THEN_FOR_IF);//'if' expression without 'then'
            pop(taxstack);//rm 'then'
            print_stack(taxstack);
        }
        else{
            print_error(lex,ERR_NEED_THEN_FOR_IF);
            //printf("Expected 'then' not 'do' at %d:%d,line:%d\n",lex->start,lex->end,lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                   || lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            if(lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE){
                pop(taxstack);//pop 'then'
            }
            else{
                pop(taxstack);
                pop(taxstack);
                pop(taxstack);
                pop(taxstack);
                print_stack(taxstack);
                return;
            }
            //pop(taxstack);
            //return;
        }
        //after then
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
            || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
            lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_DO
            || lex->last_token_type == TOKEN_RETURN || lex->last_token_type == TOKEN_PRINT){
            statement(lex);
            off[count++] = offset;
            codes[offset].hasOp = 1;
            codes[offset++].instruction = "JMP";
        }
        else if(lex->last_token_type == TOKEN_ELIF ||lex->last_token_type == TOKEN_ELSE){
            // condition reutrn because of ';' or '.' or 'end'
            printf("'if' expression without 'statement',line:%d.\n",lex->line_number);
            pop(taxstack);//pop 'THEN_STMT'
            print_stack(taxstack);
        }
        else if(lex->last_token_type == TOKEN_SEMICOLON|| lex->last_token_type == TOKEN_PERIOD
            || lex->last_token_type == TOKEN_END || lex->last_token_type == TOKEN_WHILE){
            printf("'if' expression without 'statement',line:%d.\n",lex->line_number);
            pop(taxstack);
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        else{
            print_error(lex,ERR_WRONG_BEGIN_OF_STATEMENT);//'if' with illegal statement
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                  || lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                  || lex->last_token_type == TOKEN_WHILE));
            if(lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE){
                pop(taxstack);//pop 'THEN_STMT'
            }
            else{
                pop(taxstack);
                pop(taxstack);
                pop(taxstack);
                print_stack(taxstack);
                return;
            }
        }
        //after 'then stmt'     
        //trans part
        codes[toffset].op = offset;
        //trans part
        if(lex->last_token_type == TOKEN_RPAREN) PL0Lex_get_token(lex);
        elif_stmts(lex);
        if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type==TOKEN_END
            ||lex->last_token_type == TOKEN_SEMICOLON|| lex->last_token_type == TOKEN_WHILE){
            pop(taxstack);
            print_stack(taxstack);
        }
        else if(lex->last_token_type == TOKEN_ELSE){
            pop(taxstack);
            push(taxstack,23);
            push(taxstack,60);//push 'else'
            print_stack(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            PL0Lex_get_token(lex);
            if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
               || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
               lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_DO
               || lex->last_token_type == TOKEN_RETURN || lex->last_token_type == TOKEN_PRINT)
                statement(lex);
            else{
                print_error(lex,ERR_WRONG_BEGIN_OF_STATEMENT);//'if' with illegal statement
                while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                                                 lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                                                 || lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                                                 || lex->last_token_type == TOKEN_WHILE));
                if(lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE){
                    pop(taxstack);//pop 'THEN_STMT'
                }
                else{
                    pop(taxstack);
                    pop(taxstack);
                    pop(taxstack);
                    print_stack(taxstack);
                }
            }
        }
        // Above three branch all end in ';' or ',',so return together.
        for(int i=0;i<count;i++){
            if(off[i] != -1){
                codes[off[i]].op = offset;//every branch end in 'jmp to end of if stmt'
            }
        }
        for(int i=0;i<10;i++)
            off[i] = -1;
        count = 0;
=======
                lex->last_token_type == TOKEN_CALL){
            printf("'if' expression without 'then',line:%d.\n",lex->line_number);
            pop(taxstack);//rm 'then'
            print_stack(taxstack);
        }
        else{//condition return with 'do'
            printf("Expected 'then' not 'do' at %d:%d,line:%d\n",lex->start,lex->end,lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);//rm 'then'
            print_stack(taxstack);
            PL0Lex_get_token(lex);
            //pop(taxstack);
            //return;
        }//after then
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER
            || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
            statement(lex);
        }
        else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            || lex->last_token_type ==TOKEN_END){
            printf("'if'  without statement.\n");
            pop(taxstack);
            print_stack(taxstack);
        }
        else{
            printf("'if' with illegal statement.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);
            print_stack(taxstack);
        }
        // Above three branch all end in ';' or ',',so return together.
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        return;
    }
    else if(lex->last_token_type == TOKEN_WHILE){//F->while condition do S
        pop(taxstack);
        push(taxstack,23);
        push(taxstack,33);
        push(taxstack,30);
        push(taxstack,32);
        print_stack(taxstack);
        pop(taxstack);//rm 'while'
        print_stack(taxstack);
        PL0Lex_get_token(lex);
<<<<<<< HEAD
        int start = offset;//the start of 'while' block
        int toffset = 0;//temp storation of "JPC" instr

        //condition judge
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        if(lex->last_token_type == TOKEN_ODD || lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
                condition(lex);
<<<<<<< HEAD

                //trans part
                codes[offset++].instruction = "NOT";
                toffset = offset;
                codes[offset].hasOp = 1;
                codes[offset++].instruction = "JPC";
                //trans part

        }
        else if(lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_PERIOD
            || lex->last_token_type == TOKEN_END
            ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE){
=======
        }
        else if(lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_PERIOD
            || lex->last_token_type == TOKEN_END){
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            printf("missing 'condition'&'do'&'statement' after 'while',line:%d.\n",lex->line_number);
            pop(taxstack);
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        else if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
                || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
                lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_DO){
            printf("missing 'condition' after 'while',line:%d.\n",lex->line_number);
<<<<<<< HEAD
            //'stmt' after 'while',or 'do' after 'while'
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            pop(taxstack);//rm 'condition'
            print_stack(taxstack);
        }
        else{
<<<<<<< HEAD
            print_error(lex,ERR_WRONG_BEGIN_OF_COND);//illegal 'condition' after 'while'
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                   ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE ||lex->last_token_type == TOKEN_DO));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);//pop 'O'
            print_stack(taxstack);
        }
        // 'do' judge
        if(lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_PERIOD
            ||lex->last_token_type == TOKEN_END
              ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE){
            // condition reutrn because of ';' or '.', or the following of 'while' is ';' or ','
            printf("'while' statement without 'do'&'statement',line:%d.\n",lex->line_number);
            pop(taxstack);//rm 'do'
            pop(taxstack);//rm 'F'
=======
            printf("missing 'condition' after 'while',line:%d.\n",lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        if(lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_PERIOD
            ||lex->last_token_type == TOKEN_END){
            // condition reutrn because of ';' or '.', or the following of 'while' is ';' or ','
            printf("'while' statement without 'do'&'statement',line:%d.\n",lex->line_number);
            pop(taxstack);//rm 'do'
            pop(taxstack);//rm 'X'
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            print_stack(taxstack);
            return;
        }           
        else if(lex->last_token_type == TOKEN_DO){
            // condition reutrn because of 'do', or 'do' after 'while'
            pop(taxstack);// rm 'do'
            print_stack(taxstack);
            PL0Lex_get_token(lex);
        }
        else if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
                || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
                lex->last_token_type == TOKEN_CALL)
<<<<<<< HEAD
        {//return with FIRST of 'F', or FIRST of 'F' after 'while'
            print_error(lex,ERR_NEED_DO_FOR_WHILE);//'while' statement without 'do'
=======
        {//return with FIRST of 'X', or FIRST of 'X' after 'while'
            printf("'while' statement without 'do',line:%d.\n",lex->line_number);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            pop(taxstack);//rm 'do'
            print_stack(taxstack);
        }
        else{//condition return with 'then'
            printf("Expected 'do' not 'then',line:%d\n",lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
<<<<<<< HEAD
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                    ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE || lex->last_token_type ==TOKEN_DO));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);//pop 'do'
=======
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);
            //pop(taxstack);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            print_stack(taxstack);
            PL0Lex_get_token(lex);
            //return;
        }//after do.
<<<<<<< HEAD
        //stmt judge
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
            || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
            lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_DO
            || lex->last_token_type == TOKEN_RETURN || lex->last_token_type == TOKEN_PRINT){
            statement(lex);

            //trans part
            codes[offset].instruction = "JMP";
            codes[offset].hasOp = 1;
            codes[offset++].op = start;
            codes[toffset].op = offset;
            //trans part

        }
        else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            ||lex->last_token_type == TOKEN_END
              ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE){
=======
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
            || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
            lex->last_token_type == TOKEN_CALL){
            statement(lex);
        }
        else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            ||lex->last_token_type == TOKEN_END){
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            printf("'while' without 'statement',line:%d\n",lex->line_number);
            pop(taxstack);
            print_stack(taxstack);
        }
        else{
<<<<<<< HEAD
            print_error(lex,ERR_WRONG_BEGIN_OF_STATEMENT);//'while' with illegal statement.
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                   ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE));
                    //Ignore until Follow of F, ';' or '.' or 'end' or 'while'.
            pop(taxstack);
            print_stack(taxstack);
        }
        // Above three branch all end in ';' or ',',so return together.
        return;
    }
    else if(lex->last_token_type == TOKEN_DO){  // do while
        pop(taxstack);
        push(taxstack,30);//push 'coondition'
        push(taxstack,32);//push 'while'
        //push(taxstack,10);//psuh ';'
        push(taxstack,23);//push 'stmt'
        push(taxstack,33);//push 'do'
        print_stack(taxstack);
        pop(taxstack);//rm 'do'
        print_stack(taxstack);
        PL0Lex_get_token(lex);
        //stmt judge
        short tmpoffset = offset;
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
            || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
            lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_DO
            || lex->last_token_type == TOKEN_RETURN || lex->last_token_type == TOKEN_PRINT){
            statement(lex);
        }
        else if(lex->last_token_type == TOKEN_SEMICOLON) {
            printf("missing 'statement' after 'do',line:%d.\n",lex->line_number);
            pop(taxstack);
            print_stack(taxstack);
            PL0Lex_get_token(lex);
        }
        else if(lex->last_token_type == TOKEN_PERIOD
            || lex->last_token_type == TOKEN_END||lex->last_token_type == TOKEN_ELIF
            || lex->last_token_type == TOKEN_ELSE){
            printf("missing 'statement'&';'&'condition' after 'do',line:%d.\n",lex->line_number);
            pop(taxstack);
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        else if(lex->last_token_type == TOKEN_ODD || lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
            printf("missing 'stmt'&';' after 'do',line:%d.\n",lex->line_number);
            //'condition' after 'do'
            pop(taxstack);//rm 'stmt'
            print_stack(taxstack);
        }
        else{
            print_error(lex,ERR_WRONG_BEGIN_OF_STATEMENT);//illegal 'stmt' after 'do'
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                   ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            if(lex->last_token_type== TOKEN_WHILE || lex->last_token_type == TOKEN_SEMICOLON){
                pop(taxstack);//rm 'stmt'
                print_stack(taxstack);
            }
            else{
                pop(taxstack);
                pop(taxstack);
                pop(taxstack);
                print_stack(taxstack);
                return;
            }
        }
        // ';' judge
        /*
        if(lex->last_token_type == TOKEN_SEMICOLON ){
            pop(taxstack);//rm ';'
            print_stack(taxstack);
            PL0Lex_get_token(lex);
        }
        else if(lex->last_token_type == TOKEN_WHILE){
            print_error(lex,ERR_SEMICOLON_MISS);
            pop(taxstack);//rm ';'
            print_stack(taxstack);
        }
        else if(lex->last_token_type == TOKEN_PERIOD
            ||lex->last_token_type == TOKEN_END
              ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE){
            // condition reutrn because of ';' or '.', or the following of 'do' is ';' or ','
            print_error(lex,ERR_SEMICOLON_MISS);
            pop(taxstack);//rm ';'
            pop(taxstack);//rm 'while'
            pop(taxstack);//rm 'O'
            print_stack(taxstack);
            return;
        }
        else{
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                   ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                    ||lex->last_token_type == TOKEN_WHILE));
            //Ignore until Follow of F, ';' or '.' or 'end'.
            if(lex->last_token_type == TOKEN_WHILE){
                pop(taxstack);
                print_stack(taxstack);
            }
            else{
                pop(taxstack);//rm ';'
                pop(taxstack);//rm 'while'
                pop(taxstack);//rm 'O'
                return;
            }
        }*/
        //'while' judge
        if(lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_PERIOD
           ||lex->last_token_type == TOKEN_END ||lex->last_token_type == TOKEN_ELIF
           || lex->last_token_type == TOKEN_ELSE) {
            // condition reutrn because of ';' or '.', or the following of 'do' is ';' or ','
            printf("'do while' statement without 'while'&'condition',line:%d.\n",lex->line_number);
            pop(taxstack);//rm 'while'
            pop(taxstack);//rm 'O'
            print_stack(taxstack);
            return;
        }
        else if(lex->last_token_type == TOKEN_WHILE){
            // condition reutrn because of 'while', or 'while' after 'do'
            pop(taxstack);// rm 'while'
            print_stack(taxstack);
            PL0Lex_get_token(lex);
        }
        else if(lex->last_token_type == TOKEN_ODD || lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN)
        {//return with FIRST of 'O', or FIRST of 'O' after 'while'
            print_error(lex,ERR_NEED_DO_FOR_WHILE);//'while' statement without 'do'
            pop(taxstack);//rm 'do'
            print_stack(taxstack);
        }       
        else{
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                   ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        //after while
        //condition judge
        if(lex->last_token_type == TOKEN_ODD || lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
                condition(lex);
        }
        else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            ||lex->last_token_type == TOKEN_END
              ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
              || lex->last_token_type == TOKEN_WHILE){
            printf("'do while' without 'condition',line:%d\n",lex->line_number);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        else{
            print_error(lex,ERR_WRONG_BEGIN_OF_COND);//'do while' with illegal 'condition'.
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                   ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        codes[offset].instruction = "JPC";
        codes[offset].hasOp = TRUE;
        codes[offset].op = tmpoffset;
        offset++;
        //after condition
        if(!(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            ||lex->last_token_type == TOKEN_END
              ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
              || lex->last_token_type == TOKEN_WHILE))
        {
            print_error(lex,ERR_SEMICOLON_OR_COMMA_MISS);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                   ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                   || lex->last_token_type == TOKEN_WHILE));
        }
        return;
    }
    else if(lex->last_token_type == TOKEN_RETURN){ // return statement
                                               // F -> returnX ;
           pop(taxstack); // pop F
           push(taxstack,35); // push X
           push(taxstack,52); //push return
           print_stack(taxstack);
           pop(taxstack);
           print_stack(taxstack);
           PL0Lex_get_token(lex);

           if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER
              || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN || lex->last_token_type ==TOKEN_CALL){
               expression(lex);
           }
           else{
               print_error(lex,ERR_RETURN_EXPECT_EXPRESSION);
               while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
                    ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                    || lex->last_token_type == TOKEN_WHILE));
               return;
           }
           codes[offset].instruction = "ST";
           codes[offset].hasOp = TRUE;
           codes[offset].op = 300;
           offset++;
           codes[offset].instruction = "ST";
           codes[offset].hasOp = TRUE;
           codes[offset].op = 305;
           offset++;//s[0]->300,s[1]->305


           codes[offset].instruction = "LD";
           codes[offset].hasOp = TRUE;
           codes[offset].op = 300;
           offset++;
           codes[offset].instruction = "LD";
           codes[offset].hasOp = TRUE;
           codes[offset].op = 305;
           offset++;//305->s[0],300->s[1]

           codes[offset].instruction = "JMP";
           codes[offset].hasOp = FALSE;
           offset++;
    }
    return;
}

void elif_stmts(PL0Lex* lex){
    int toffset;

    if(lex->last_token_type == TOKEN_END || lex->last_token_type == TOKEN_PERIOD ||
        lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_ELSE
        || lex->last_token_type == TOKEN_WHILE){
        pop(taxstack);//rm 'ELIF_STMT'
        print_stack(taxstack);
        return;
    }
    pop(taxstack);
    push(taxstack,57);//push 'ELIF_STMTS'
    push(taxstack,23);//push 'F'
    push(taxstack,31);//push 'then'
    push(taxstack,30);//push 'O'
    push(taxstack,59);//push 'elif'
    print_stack(taxstack);
    if(!(lex->last_token_type == TOKEN_ELIF)){
        printf("Illegal first for 'elif' statements,line:%d\n",lex->line_number);
        while(1){ //One illegal statement,ignore until ';'
            PL0Lex_get_token(lex);
            if(lex->last_token_type == TOKEN_ELIF){
                break;
            }
            else if(lex->last_token_type == TOKEN_END || lex->last_token_type == TOKEN_PERIOD ||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_ELSE
                    || lex->last_token_type == TOKEN_WHILE ){
                pop(taxstack);
                pop(taxstack);
                pop(taxstack);
                pop(taxstack);
                pop(taxstack);
                print_stack(taxstack);
                return;
            }
        }
    }
    pop(taxstack);//pop 'elif'
    print_stack(taxstack);
    PL0Lex_get_token(lex);
    //after 'elif'
    if(lex->last_token_type == TOKEN_ODD || lex->last_token_type == TOKEN_IDENTIFIER ||
       lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS ||
       lex->last_token_type == TOKEN_LPAREN){
        condition(lex);

        //trans part
        codes[offset++].instruction = "NOT";
        toffset = offset;
        codes[offset].hasOp = 1;
        codes[offset++].instruction = "JPC";
        //trans part
    }
    else if(lex->last_token_type == TOKEN_ELIF) {
        printf("missing 'condition'&'then'&'statement' after 'elif',line:%d.\n",lex->line_number);
        pop(taxstack);//pop 'O'
        print_stack(taxstack);
    }
    else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_END
            || lex->last_token_type ==TOKEN_SEMICOLON
            || lex->last_token_type == TOKEN_WHILE|| lex->last_token_type == TOKEN_ELSE){
        printf("statement with only 'elif',line:%d.\n",lex->line_number);
        pop(taxstack);
        pop(taxstack);
        pop(taxstack);
        pop(taxstack);
        print_stack(taxstack);
        return;
    }
    else if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
            || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
            lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_THEN){
        printf("missing 'condition' after 'elif',line:%d.\n",lex->line_number);
        pop(taxstack);//rm 'condition'
        print_stack(taxstack);
    }
    else{
        print_error(lex,ERR_WRONG_BEGIN_OF_COND);//missing 'condition' after 'if'
        while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
             lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
             || lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
             || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_WHILE));
        //Ignore until Follow of F, ';' or '.' or 'end'.
        if(lex->last_token_type == TOKEN_ELIF ){
            pop(taxstack);//pop 'O'
        }
        else{
            pop(taxstack);
            pop(taxstack);
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
    }
    //after condition
    if(lex->last_token_type == TOKEN_ELSE ||lex->last_token_type == TOKEN_SEMICOLON
        || lex->last_token_type == TOKEN_PERIOD
       || lex->last_token_type == TOKEN_END || lex->last_token_type == TOKEN_WHILE){
        // condition reutrn because of ';' or '.' or 'end'
        printf("'elif' expression with only 'elif'&'condition',line:%d.\n",lex->line_number);
        pop(taxstack);
        pop(taxstack);
        pop(taxstack);
        print_stack(taxstack);
        return;
    }
    else if( lex->last_token_type == TOKEN_ELIF){
        printf("missing &'then'&'statement' after 'elif condition',line:%d.\n",lex->line_number);
        pop(taxstack);//pop 'then'
        print_stack(taxstack);
    }
    else if(lex->last_token_type == TOKEN_THEN){
        // condition reutrn because of 'then', or 'then' after 'if'
        pop(taxstack);//pop 'then'
        print_stack(taxstack);
        PL0Lex_get_token(lex);
    }
    else if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
            || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
            lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_DO){
        print_error(lex,ERR_NEED_THEN_FOR_IF);//'if' expression without 'then'
        pop(taxstack);//rm 'then'
        print_stack(taxstack);
    }
    else{
        print_error(lex,ERR_NEED_THEN_FOR_IF);
        //printf("Expected 'then' not 'do' at %d:%d,line:%d\n",lex->start,lex->end,lex->line_number);
        while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
             lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
             || lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
             || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_WHILE));
        //Ignore until Follow of F, ';' or '.' or 'end'.
        if(lex->last_token_type == TOKEN_ELIF ){
            pop(taxstack);//pop 'then'
        }
        else{
            pop(taxstack);
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        //pop(taxstack);
        //return;
    }
    //after then
    if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
       || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
       lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_DO
       || lex->last_token_type == TOKEN_RETURN || lex->last_token_type == TOKEN_PRINT){
        statement(lex);

        off[count++] = offset;
        codes[offset].hasOp = 1;
        codes[offset++].instruction = "JMP";

        //trans part
        codes[toffset].op = offset;
        //trans part
    }
    else if(lex->last_token_type == TOKEN_ELIF){
        // condition reutrn because of ';' or '.' or 'end'
        printf("'elif' expression without 'statement',line:%d.\n",lex->line_number);
        pop(taxstack);//pop 'F'
        print_stack(taxstack);
    }
    else if(lex->last_token_type == TOKEN_SEMICOLON|| lex->last_token_type == TOKEN_PERIOD
            || lex->last_token_type == TOKEN_END || lex->last_token_type == TOKEN_WHILE
            ||lex->last_token_type == TOKEN_ELSE){
        printf("'elif' expression without 'statement',line:%d.\n",lex->line_number);
        pop(taxstack);
        pop(taxstack);
        print_stack(taxstack);
        return;
    }
    else{
        print_error(lex,ERR_WRONG_BEGIN_OF_STATEMENT);//'if' with illegal statement
        //printf("Expected 'then' not 'do' at %d:%d,line:%d\n",lex->start,lex->end,lex->line_number);
        while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
             lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END
             || lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
             || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_WHILE));
        //Ignore until Follow of F, ';' or '.' or 'end'.
        if(lex->last_token_type == TOKEN_ELIF){
            pop(taxstack);//pop 'F'
        }
        else{
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
    }//after 'then stmt'
    //before elif_stmts
    if(lex->last_token_type == TOKEN_SEMICOLON|| lex->last_token_type == TOKEN_PERIOD
       || lex->last_token_type == TOKEN_END || lex->last_token_type == TOKEN_WHILE
       ||lex->last_token_type == TOKEN_ELSE){
        pop(taxstack);//pop 'ELIF_STMTS'
        print_stack(taxstack);
        return;
    }

    elif_stmts(lex);
    return;
}


=======
            printf("'while' with illegal statement.line:%d\n",lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);
            print_stack(taxstack);
        }
        // Above three branch all end in ';' or ',',so return together.
        return;
    }
    return;
}

>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
void statements(PL0Lex* lex){ // S 语句序列,S->F;S| EPSILON
    PL0Lex_get_token(lex);
    if(lex->last_token_type == TOKEN_END || lex->last_token_type == TOKEN_PERIOD){
        pop(taxstack);//rm 'S'
        print_stack(taxstack);
        return;
    }
    pop(taxstack);//rm 'S'
    push(taxstack,4);//add 'S'
    push(taxstack,10);//add ';'
    push(taxstack,23);//add 'F'
    print_stack(taxstack);
    while(1){// Until end or find one legal statement
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
            || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
<<<<<<< HEAD
            lex->last_token_type == TOKEN_CALL || lex->last_token_type == TOKEN_DO
            || lex->last_token_type == TOKEN_RETURN|| lex->last_token_type== TOKEN_PRINT){
=======
            lex->last_token_type == TOKEN_CALL){
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            statement(lex);//Connote rm of 'F'
            break;
        }
        else{
<<<<<<< HEAD
            print_error(lex,ERR_WRONG_BEGIN_OF_STATEMENT);//Illegal statement in 'statements'
=======
            printf("Illegal statement in 'statements'.\n");
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            while(1){ //One illegal statement,ignore until ';'
                PL0Lex_get_token(lex);
                if(lex->last_token_type == TOKEN_SEMICOLON){
                    PL0Lex_get_token(lex);
                    break;
                }
                else if(lex->last_token_type == TOKEN_END || lex->last_token_type == TOKEN_PERIOD){
                    pop(taxstack);//rm 'F'
                    pop(taxstack);//rm ';'
                    pop(taxstack);//rm 'S'
                    print_stack(taxstack);
                    return;
                }
            }
        }   
    }
    if(lex->last_token_type == TOKEN_SEMICOLON){
        //print_stack(taxstack);
        pop(taxstack);//rm ';'
        print_stack(taxstack);
        statements(lex);//Connote rm of 'S'
        return;
    }
    else //lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_END)
    {
<<<<<<< HEAD
        print_error(lex,ERR_SEMICOLON_MISS);//expected ';'
=======
        printf("Expected ';'.\n");
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
        pop(taxstack);//rm ';'
        pop(taxstack);//rm 'S' with epsilon
        print_stack(taxstack);
        return;
    }
}
<<<<<<< HEAD

=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
void condition(PL0Lex * lex){ //analysis the condition statement 'O(spell 'eu')'
    if(lex->last_token_type == TOKEN_ODD){
        pop(taxstack);//rm 'O'
        push(taxstack,35);
        push(taxstack,34);
        print_stack(taxstack);
        pop(taxstack);
        print_stack(taxstack);//rm 'odd'
        PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
            expression(lex);
        }
        else{
            printf("'condition' with illegal expression.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
<<<<<<< HEAD
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO
                    ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                    || lex->last_token_type == TOKEN_WHILE));
=======
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    //Ignore until Follow of F, ';' or '.' or 'end' or 'then' or 'do'.
            pop(taxstack);//rm 'X'
            print_stack(taxstack);
            return;
        }
        return;
    }
    else{// O->XQ
        pop(taxstack);//rm 'O'
        push(taxstack,36);
        push(taxstack,35);
        print_stack(taxstack);
        expression(lex);//Connote rm of 'X'
        if(lex->last_token_type==TOKEN_PERIOD||lex->last_token_type == TOKEN_SEMICOLON
            || lex->last_token_type==TOKEN_END || lex->last_token_type == TOKEN_THEN 
            || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_CALL
            || lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
            || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE){
            printf("Warning: condition with only single expression.\n");
            pop(taxstack);
            print_stack(taxstack);//rm 'Q' with epsilon
            return;
        }
        else if(lex->last_token_type==TOKEN_EQU||lex->last_token_type == TOKEN_NEQ
            || lex->last_token_type==TOKEN_LES || lex->last_token_type == TOKEN_LEQ 
            || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ)
        {
<<<<<<< HEAD
            //trans part
            PL0TokenType ttype = lex->last_token_type; // to temporarily store the logic symbol
            Q(lex);//connote rm of 'Q'
            switch (ttype){
                case TOKEN_EQU:codes[offset++].instruction = "EQ";break;
                case TOKEN_NEQ:
                    codes[offset++].instruction = "EQ";
                    codes[offset++].instruction = "NOT";
                    break;
                case TOKEN_LES:codes[offset++].instruction = "GT";break;
                case TOKEN_GTR:codes[offset++].instruction = "LT";break;
                case TOKEN_LEQ:codes[offset++].instruction = "GE";break;
                case TOKEN_GEQ:codes[offset++].instruction = "LE";break;

            }
            //codes[offset++].instruction = "NOT";
            //trans part

=======
            Q(lex);//connote rm of 'Q'
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
            if(lex->last_token_type==TOKEN_EQU||lex->last_token_type == TOKEN_NEQ
            || lex->last_token_type==TOKEN_LES || lex->last_token_type == TOKEN_LEQ 
            || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ)
            {
<<<<<<< HEAD
                printf("Too much logic operation of one condition!\n");
                while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                        lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                        lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO
                      ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                      || lex->last_token_type == TOKEN_WHILE));
=======
                printf("Too much logic operation ofr one condition!\n");
                while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                        lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                        lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                        //Ignore until Follow of F, ';' or '.' or 'end' or 'then' or 'do'.
            }
        }
        else{
            printf("Illegal logic operation.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
<<<<<<< HEAD
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO
                  ||lex->last_token_type == TOKEN_ELIF || lex->last_token_type == TOKEN_ELSE
                  || lex->last_token_type == TOKEN_WHILE));
=======
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
                    //Ignore until Follow of F, ';' or '.' or 'end' or 'then' or 'do'.
            pop(taxstack);//rm 'Q'
            print_stack(taxstack);
        }
        return;
    }
}
void Q(PL0Lex* lex){ //Q 消除左递归
    if(lex->last_token_type == TOKEN_EQU){
        pop(taxstack);//rm 'Q'
        push(taxstack,35);
        push(taxstack,12);
        print_stack(taxstack);
        pop(taxstack);//rm '='
        PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
            expression(lex);
        }
        else{
            printf("Q:'logic operation' + 'expression', with illegal expression.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
                    //Ignore until Follow of F, ';' or '.' or 'end' or 'then' or 'do'.
            pop(taxstack);//rm 'X'
            print_stack(taxstack);
            return;
        }
<<<<<<< HEAD

        //trans part
        codes[offset].hasOp = 0;
        codes[offset].instruction = "EQ";
=======
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
    }
    if(lex->last_token_type == TOKEN_NEQ){
        pop(taxstack);//rm 'Q'
        push(taxstack,35);
        push(taxstack,37);
        print_stack(taxstack);
        pop(taxstack);//rm '!='
        PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
            expression(lex);
        }
        else{
            printf("Q:'logic operation' + 'expression', with illegal expression.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
                    //Ignore until Follow of F, ';' or '.' or 'end' or 'then' or 'do'.
            pop(taxstack);//rm 'X'
            print_stack(taxstack);
            return;
        }
    }
    if(lex->last_token_type == TOKEN_LEQ){
        pop(taxstack);//rm 'Q'
        push(taxstack,35);
        push(taxstack,38);
        print_stack(taxstack);
        pop(taxstack);//rm '<='
        PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
            expression(lex);
        }
        else{
            printf("Q:'logic operation' + 'expression', with illegal expression.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
                    //Ignore until Follow of F, ';' or '.' or 'end' or 'then' or 'do'.
            pop(taxstack);//rm 'X'
            print_stack(taxstack);
            return;
        }
    }
    if(lex->last_token_type == TOKEN_GEQ){
        pop(taxstack);//rm 'Q'
        push(taxstack,35);
        push(taxstack,39);
        print_stack(taxstack);
        pop(taxstack);//rm '>='
        PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
            expression(lex);
        }
        else{
            printf("Q:'logic operation' + 'expression', with illegal expression.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
                    //Ignore until Follow of F, ';' or '.' or 'end' or 'then' or 'do'.
            pop(taxstack);//rm 'X'
            print_stack(taxstack);
            return;
        }
    }
    if(lex->last_token_type == TOKEN_LES){
        pop(taxstack);//rm 'Q'
        push(taxstack,35);
        push(taxstack,40);
        print_stack(taxstack);
        pop(taxstack);//rm '<'
        PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
            expression(lex);
        }
        else{
            printf("Q:'logic operation' + 'expression', with illegal expression.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
                    //Ignore until Follow of F, ';' or '.' or 'end' or 'then' or 'do'.
            pop(taxstack);//rm 'X'
            print_stack(taxstack);
            return;
        }
    }
    if(lex->last_token_type == TOKEN_GTR){
        pop(taxstack);//rm 'Q'
        push(taxstack,35);
        push(taxstack,41);
        print_stack(taxstack);
        pop(taxstack);//rm '>'
        print_stack(taxstack);
        PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
            expression(lex);
        }
        else{
            printf("Q:'logic operation' + 'expression', with illegal expression.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
                    //Ignore until Follow of F, ';' or '.' or 'end' or 'then' or 'do'.
            pop(taxstack);//rm 'X'
            print_stack(taxstack);
            return;
        }
    }
}

