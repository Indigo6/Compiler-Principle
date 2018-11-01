#include <stdio.h>
#include <stdlib.h>
#include "../common/common.h"
#include "pl0_tax.h"
#include <string.h>

extern stack * taxstack;
/*operations for token table*/
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
			break;
		case ID_VARIABLE:
			token_table[table_index].level = lex->last_level;
			break;
		case ID_PROCEDURE:
			token_table[table_index].level = lex->last_level;
			break;
	} //switch
	table_index += 1;
} //table_append

void initializestack(stack* s){
    for(int i = 0; i < MAXSTACKSIZE;i++){
        s->Stack[i] = -1;  // because index of lebel tabel can not be minus
    }
    s->length = -1;
}
void destroystack(stack* s){
    free(s);
}

int top(stack* s){
    if(s->length < 0){
        printf("Stack is empty!");
        return -1;
    }else{
    return s->Stack[s->length];
 }
}

int pop(stack* s){
    if(s->length < 0){
        printf("Stack is empty!");
        return -1;
    }
    else{
        return s->Stack[s->length--];
    }
}

void push(stack* s, int element){
    if(s->length+1 == MAXSTACKSIZE){
        printf("Stack is full!");
    }
    else{
        s->Stack[++s->length] = element;
    }
}
void print_stack(stack* s){
    for(int i = 0; i< s->length;i++){
        printf("%s ",lexLabel[s->Stack[i]]);
    }
    printf("\n");
}
/*functions for syntax analysis*/
void statement(PL0Lex * lex) {//语句
	printf("analysis the statement\n");
}

void condition(PL0Lex * lex) {//tiaojian
	printf("analysis the condition expression\n");
	if(lex->last_token_type == TOKEN_ODD){//line 1，read odd
		PL0Lex_get_token(lex);
		expression(lex);
	}
	else{//line 2， read expression
		PL0Lex_get_token(lex);
		expression(lex);
		PL0Lex_get_token(lex);
		if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ){
			PL0Lex_get_token(lex);
			expression(lex);
		}
		else printf("compare symbols needed!\n");
	}
}

void expression(PL0Lex * lex) {//表达shi
	printf("analysis the expression\n");
}

void term(PL0Lex * lex) {//xiang
	printf("analysis the term\n");
}

void factor(PL0Lex * lex) {//yinzi
	printf("analysis the factor\n");
	if(lex->last_token_type == TOKEN_MINUS){//line 3
		PL0Lex_get_token(lex);
		expression(lex);
	}
	else if(lex->last_token_type == TOKEN_LPAREN){//line 4
		PL0Lex_get_token(lex);
		expression(lex);
		PL0Lex_get_token(lex);
		if(lex->last_token_type != TOKEN_RPAREN) printf("RPAREN ')' needed!\n");
	}
	else if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER){//line 1&2
		//DO SOMETHING?	
	}
	else{
		printf("illegal factor!\n");	
	}
}



void W(PL0Lex* lex){
    if(lex->last_token_type == TOKEN_COMMA){
        int tmp = pop(taxstack); // W -> ,A
        push(taxstack,9);
        push(taxstack,15);
        print_stack(taxstack);
        tmp = pop(taxstack); //reduce ,
        const_declaration(lex);
    }
    else{//W ->;
        int tmp = pop(taxstack);
        push(taxstack,10);
        print_stack(taxstack);
    }
}
void const_declaration(PL0Lex * lex) { //A
	if (lex->last_token_type == TOKEN_IDENTIFIER) {
	    int tmp = pop(taxstack);
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
				printf("found ':=' when expecting '='\n at line %d",lex->line_number);
			tmp = pop(taxstack); //reduce =
			print_stack(taxstack);
			PL0Lex_get_token(lex);
			if (lex->last_token_type == TOKEN_NUMBER) {
				table_append(lex, ID_CONSTANT);
				tmp = pop(taxstack);
				print_stack(taxstack); // reduce number
				PL0Lex_get_token(lex);
				if(lex->last_token_type!=TOKEN_COMMA && lex->last_token_type!=TOKEN_SEMICOLON){
                    printf("missing ',' or ';' at line %d\n",lex->line_number);
                    pop(taxstack); // pop W
                    print_stack(taxstack);
                    return;
				}
				else{
				    W(lex);
				    //PL0Lex_get_token(lex);
				}
			} else {
				printf("there must be a number to follow '=' at line %d\n",lex->line_number);
				pop(taxstack); //pop num
				pop(taxstack); // pop W
                pop(taxstack);
                do{  // like gcc , skip all token until ";"
                    PL0Lex_get_token(lex);
                }while(lex->last_token_type!=TOKEN_SEMICOLON);
                print_stack(taxstack);
                return;
			}
		} else {
			printf("there must be an '=' to follow the identifier at line %d\n",lex->line_number);
            pop(taxstack);//pop =
            pop(taxstack); //pop num
            pop(taxstack); //pop W
            do{
                PL0Lex_get_token(lex);
            }while(lex->last_token_type!=TOKEN_SEMICOLON);
            print_stack(taxstack);
            return;
		}
	} else {
		printf("There must be an identifier to follow 'const' at line %d\n",lex->line_number);
		pop(taxstack);//pop A
		do{
		    PL0Lex_get_token(lex);
		}while(lex->last_token_type!=TOKEN_SEMICOLON);
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
        pop(taxstack); //reduce id
        print_stack(taxstack);
        PL0Lex_get_token(lex);
        if(lex->last_token_type!=TOKEN_COMMA && lex->last_token_type!=TOKEN_SEMICOLON){
            printf("missing ',' or ';' at line %d\n",lex->line_number);
            pop(taxstack); //pop H
            print_stack(taxstack);
            return;
        }
        else{
            H(lex);
        }
    }
    else{
        printf("There must be an identifier to follow 'var' at line %d\n",lex->line_number);
        pop(taxstack); // pop E
        do{
            PL0Lex_get_token(lex);
        }while(lex->last_token_type!=TOKEN_SEMICOLON);
        print_stack(taxstack);
    }
}//variable_declaration

void program_block(PL0Lex * lex) {
	printf("analysis the program block\n");
	// PL0Lex * lex = (PL0Lex *) calloc(1, sizeof(PL0Lex));
	// PL0Lex_get_token(lex);
	push(taxstack,0); // p
	print_stack(taxstack);
    int tmp = pop(taxstack);// pop P
    push(taxstack,1);// p->B
    print_stack(taxstack);
    pop(taxstack); //pop B
    push(taxstack,23);
    push(taxstack,2);
    print_stack(taxstack); // B -> DF
	do{//D
		if (lex->last_token_type == TOKEN_CONST) {
		    push(taxstack, 5); // D -> CD
		    print_stack(taxstack);
		    tmp = pop(taxstack);
		    push(taxstack,9); // C -> constA
		    push(taxstack,8);
		    print_stack(taxstack);
		    tmp = pop(taxstack); // reduce const
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
		        tmp = pop(taxstack); //V -> var E
		        push(taxstack,18);
		        push(taxstack,17);
		        print_stack(taxstack);
		        tmp = pop(taxstack);//reduce var
		        print_stack(taxstack);
			    PL0Lex_get_token(lex);
			    variable_declaration(lex);
			    /*while (lex->last_token_type == TOKEN_COMMA){
			        PL0Lex_get_token(lex);
			        varible_declaration(lex);
			    }*/
			} else if(lex -> last_token_type == TOKEN_PROCEDURE){ //D->RD

		}
		else{
		    //D -> epsilon
		    tmp = pop(taxstack); // D reduced by epsilon
		    print_stack(taxstack);
            break;
		}
	} while(TRUE);//while(lex->last_token_type == TOKEN_CONST || lex->last_token_type == TOKEN_VAR || lex->last_token_type == TOKEN_PROCEDURE);
} //program_block
