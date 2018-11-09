#include <stdio.h>
#include <stdlib.h>
#include "../common/common.h"
#include "pl0_tax.h"
#include <string.h>


const char* lexLabel[] = {"P","B","D",".","S","C","V","R","const","A",";","id","=","num","W",",",
                          "V","var","E","H","R","procedure","S","F","M",":=","call","begin",
                          "end","if","O","then","while","do","odd","X","Q","!=","<=",">=",
                          "<",">","T","G","+","-","*","/","Y","Z","(",")"};
stack* taxstack ;
int table_index = 0;
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

/*void condition(PL0Lex * lex) {//tiaojian
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
}*/

void expression(PL0Lex * lex) {//表达shi X,产生式：X->TG
	//printf("analysis the expression\n");

	pop(taxstack);//rm 'X'
	push(taxstack,43);//G
	push(taxstack,42);//T
	print_stack(taxstack);



	if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
	    term(lex);//'T'
	    if(lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS) G(lex);//'G'
        else if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
            pop(taxstack);
            print_stack(taxstack);
            return;
		}
		else printf("X.follow error!\n");
	}
	else{}//some error ...    
        return;
}

void term(PL0Lex * lex) {//xiang,T->YZ
	//printf("analysis the term\n");

	pop(taxstack);//rm T
	push(taxstack,49);//Z
	push(taxstack,48);//Y
	print_stack(taxstack);
	//pop(taxstack);
	//print_stack(taxstack);

	if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
        	factor(lex);//'Y'
        	if(lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH) {
                Z(lex);//'Z'
            }
            else  if(lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS 
                || lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ 
                || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ 
                || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ 
                || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD 
                || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO 
                || lex->last_token_type == TOKEN_RPAREN)
            {
                pop(taxstack);
                print_stack(taxstack); // pop Z
            }
	}
	else{}//some error...
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
		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
		    term(lex);//'T'
            if(lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS) {
                G(lex);//'G'
            }

            if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
                pop(taxstack);
                print_stack(taxstack);
                return;
			}
			else printf("G.follow error!\n");
		}
	}

	else if(lex->last_token_type == TOKEN_MINUS){//G->-TG
		pop(taxstack);//rm 'G'
		push(taxstack,43);//G
		push(taxstack,42);//T
		push(taxstack,45);//-
		print_stack(taxstack);


		PL0Lex_get_token(lex);
		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
		    term(lex);//'T'
            if(lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS) {
                G(lex);//'G'
            }

            if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
                pop(taxstack);
                print_stack(taxstack);
                return;
			}
			else printf("G.follow error!\n");
		}
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


		PL0Lex_get_token(lex);
		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
        		factor(lex);//'Y'

            if(lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH) {
                Z(lex);//'Z'
            }

            if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
                pop(taxstack);
                print_stack(taxstack);
                return;
            }
			else printf("Z.follow error!\n");
		}
	}
	else if(lex->last_token_type == TOKEN_SLASH){//Z->/YZ
        pop(taxstack);//rm 'Z'
        push(taxstack,49);//Z
        push(taxstack,48);//Y
        push(taxstack,46);//*
        print_stack(taxstack);


        PL0Lex_get_token(lex);
		if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
		    factor(lex);//'Y'
            if(lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH) {
                Z(lex);//'Z'
            }
            if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
                pop(taxstack);
                print_stack(taxstack);
                return;
			}
			else printf("Z.follow error!\n");
		}
	}
	return;
}

void factor(PL0Lex * lex) {//yinzi
	//printf("analysis the factor\n");
	if(lex->last_token_type == TOKEN_IDENTIFIER){//Y->id
		pop(taxstack);//rm 'Y'
		push(taxstack,11);//id
		print_stack(taxstack);
		pop(taxstack);//rm 'id'
		print_stack(taxstack);
		PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
            return;
        } else printf("Y.FOLLOW.ERROR\n");
	}
	else if(lex->last_token_type == TOKEN_NUMBER){//Y->num
		pop(taxstack);//rm 'Y'
		push(taxstack,13);//num
		print_stack(taxstack);
		pop(taxstack);
		print_stack(taxstack);
		PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
            return;
        } else printf("Y.FOLLOW.ERROR\n");
	}
	else if(lex->last_token_type == TOKEN_MINUS){//Y->-X
		pop(taxstack);//rm 'Y'
		push(taxstack,35);//X
		push(taxstack,45);//-
		print_stack(taxstack);
		pop(taxstack);
		print_stack(taxstack);
		PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN) {
            expression(lex);//'X'
        }
        else{}
        if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
            return;
        } else printf("Y.FOLLOW.ERROR\n");
	}
	else if(lex->last_token_type == TOKEN_LPAREN){//Y->(X)
		pop(taxstack);//rm 'Y'
		push(taxstack,51);//)
		push(taxstack,35);//X
		push(taxstack,50);//(
		print_stack(taxstack);
		pop(taxstack);
		print_stack(taxstack);

		PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN) {
            expression(lex);//'X'
        }
        else{}
		PL0Lex_get_token(lex);//)
        if(lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_PLUS || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_NEQ || lex->last_token_type == TOKEN_LES || lex->last_token_type == TOKEN_LEQ || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ || lex->last_token_type == TOKEN_SEMICOLON ||  lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO || lex->last_token_type == TOKEN_TIMES || lex->last_token_type == TOKEN_SLASH || lex->last_token_type == TOKEN_RPAREN) {
            return;
        } else printf("Y.FOLLOW.ERROR\n");
	}

	PL0Lex_get_token(lex);
}



void W(PL0Lex* lex){
    if(lex->last_token_type == TOKEN_COMMA){
        int tmp = pop(taxstack); // W -> ,A
        push(taxstack,9);
        push(taxstack,15);
        print_stack(taxstack);
        tmp = pop(taxstack); //reduce ,
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
                //pop(taxstack);
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
            printf("missing ',' or ';' at line %d\n",lex->line_number);
            pop(taxstack); //pop H
            do{
                PL0Lex_get_token(lex);
            }while (lex->last_token_type!=TOKEN_SEMICOLON);
            PL0Lex_get_token(lex);
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

void procedure_declaration(PL0Lex* lex){ // procedure id ; B ;
    lex->last_level ++;
    if(lex->last_token_type == TOKEN_IDENTIFIER){
        //Table * tmptable = malloc(sizeof(Table));
        //strcpy(tmptable->name,lex->last_id);
        //tmptable->level = lex->last_level;
        table_append(lex,ID_PROCEDURE);
        pop(taxstack); // reduce id
        print_stack(taxstack);
        PL0Lex_get_token(lex);
        if(lex->last_token_type==TOKEN_SEMICOLON){
            pop(taxstack); // reduce ;
            print_stack(taxstack);
            PL0Lex_get_token(lex);
            if(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
               && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
               lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE){
                printf("at the beginning of program block, it must be 'const' or 'var' or 'procedure' or  'identifier' or 'call' or 'if' or 'begin' or 'while'\n ");
                do{
                    PL0Lex_get_token(lex);
                }while(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
                       && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
                       lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE);
                block(lex);
                PL0Lex_get_token(lex);
                if(lex->last_token_type==TOKEN_SEMICOLON){
                    pop(taxstack); // reduce ;
                    print_stack(taxstack);
                }
                else{
                    pop(taxstack);
                    printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
                }
            }
            else{
                block(lex);
                PL0Lex_get_token(lex);
                if(lex->last_token_type==TOKEN_SEMICOLON){
                    pop(taxstack); // reduce ;
                    print_stack(taxstack);
                }
                else{
                    pop(taxstack);
                    printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
                }
            }
        }
        else{
            printf("There must be a ';' follow identifier at line %d \n",lex->line_number);
            pop(taxstack); //pop ;
            while (lex->last_token_type!=TOKEN_SEMICOLON){
                PL0Lex_get_token(lex);
            }
            if(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
               && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
               lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE) {
                do{
                    PL0Lex_get_token(lex);
                }while(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
                       && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
                       lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE);
                print_stack(taxstack);
                block(lex);
                PL0Lex_get_token(lex);
                if(lex->last_token_type==TOKEN_SEMICOLON){
                    pop(taxstack); // reduce ;
                    print_stack(taxstack);
                }
                else{
                    pop(taxstack);
                    printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
                }
            }
            else{
                print_stack(taxstack);
                block(lex);
                PL0Lex_get_token(lex);
                if(lex->last_token_type==TOKEN_SEMICOLON){
                    pop(taxstack); // reduce ;
                    print_stack(taxstack);
                }
                else{
                    pop(taxstack);
                    printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
                }
            }

        }
    }
    else{
        printf("There must be an identifier follow 'procedure' at line %d\n ",lex->line_number);
        while(lex->last_token_type!=TOKEN_SEMICOLON){
            PL0Lex_get_token(lex);
        }
        pop(taxstack); //pop id
        pop(taxstack); //pop ;
        PL0Lex_get_token(lex);
        if(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
           && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
           lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE) {
            do{
                PL0Lex_get_token(lex);
            }while(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
                   && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
                   lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE);
            print_stack(taxstack);
            block(lex);
            PL0Lex_get_token(lex);
            if(lex->last_token_type==TOKEN_SEMICOLON){
                pop(taxstack); // reduce ;
                print_stack(taxstack);
            }
            else{
                pop(taxstack);
                printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
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
                printf("There must be an ';' at the end of procedure declaration at line %d\n",lex->line_number);
            }
        }
    }
    lex -> last_level --;
}
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
            push(taxstack,10);
            print_stack(taxstack);
            pop(taxstack); // R -> procedure id;B;
            push(taxstack,10);
            push(taxstack,1); //push B
            push(taxstack,10); // push ;
            push(taxstack,11); // push id
            push(taxstack,21); // push procedure
            print_stack(taxstack);
            pop(taxstack); //reduce procedure
            print_stack(taxstack);
            PL0Lex_get_token(lex);
            procedure_declaration(lex);
            PL0Lex_get_token(lex);
        }
        else{ // then should determine if it is in the FIRST of F, then it has an error
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
        lex->last_token_type == TOKEN_CALL){
            statement(lex);
    }
    else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON){
        printf("Warning: block without statement.\n");//No legal statement after declaration
    }
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
    if(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
    && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
    lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE){
        printf("at the beginning of program, it must be 'const' or 'var' or 'procedure' or  'identifier' or 'call' or 'if' or 'begin' or 'while'\n ");
        do{
            PL0Lex_get_token(lex);
        }while(lex->last_token_type != TOKEN_CONST && lex->last_token_type != TOKEN_VAR && lex->last_token_type!=TOKEN_PROCEDURE
               && lex->last_token_type!=TOKEN_IDENTIFIER && lex->last_token_type!=TOKEN_CALL && lex -> last_token_type!=TOKEN_IF&&
               lex->last_token_type!=TOKEN_BEGIN && lex->last_token_type!=TOKEN_WHILE);
    }
    pop(taxstack); // pop P
    push(taxstack,3); // push .
    push(taxstack,1); //push B
    print_stack(taxstack);
    block(lex); //B
    //PL0Lex_get_token(lex);
    while(PL0Lex_get_token(lex) && (lex->last_token_type!=TOKEN_PERIOD));//Ignore until period(in case illegal stmt)
    if(lex->last_token_type==TOKEN_PERIOD){
        pop(taxstack); // pop .
        printf("analysis end1");
    }
    else{
        printf("there must an '.' in the program block end \n");
    }
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
        PL0Lex_get_token(lex);
        if(lex->last_token_type != TOKEN_BECOMES){
            printf("Expected ':=' at %d:%d,line:%d.\n",lex->start,lex->end,lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);
            pop(taxstack);
            return;
        }
        pop(taxstack);//rm ':='
        print_stack(taxstack);
        PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_NUMBER
            || lex->last_token_type == TOKEN_MINUS || lex->last_token_type == TOKEN_LPAREN){
            expression(lex); //expression must return with ';' or '.'
        }
        else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            || lex->last_token_type==TOKEN_END){
            printf("'become' statement without expression.\n");
            pop(taxstack);//rm 'X'
        }
        else{
            printf("'become' statement with illegal expression.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);//rm 'X'
        }
        return; 
    }
    else if(lex->last_token_type == TOKEN_CALL){
        pop(taxstack);
        push(taxstack,11);
        push(taxstack,26);
        print_stack(taxstack);
        pop(taxstack); // rm 'call'
        print_stack(taxstack);
        PL0Lex_get_token(lex);
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
        return;
    }
    else if(lex->last_token_type == TOKEN_BEGIN){
        pop(taxstack);
        push(taxstack,28);
        push(taxstack,4);
        push(taxstack,27);
        print_stack(taxstack);
        pop(taxstack);//rm 'begin'
        print_stack(taxstack);
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
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            }
        }
        pop(taxstack);//rm 'end'
        return;
    }
    else if(lex->last_token_type == TOKEN_IF){
        pop(taxstack);
        push(taxstack,23);
        push(taxstack,31);
        push(taxstack,30);
        push(taxstack,29);
        print_stack(taxstack);
        pop(taxstack);//rm 'if'
        print_stack(taxstack);
        PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_ODD || lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
                condition(lex);
        }
        else if(lex->last_token_type == TOKEN_THEN){
            printf("'if' expression without 'condition'.\n");
            pop(taxstack);//rm 'O'
            print_stack(taxstack);
        }
        else if(lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_PERIOD
            || lex->last_token_type == TOKEN_END){
            printf("'if' without 'condition','then'&'statement'.\n");
            pop(taxstack);
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        else{
            printf("'if' with illegal 'condition'.\n");
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
            // condition reutrn because of ';' or '.' or 'end'
            printf("'if' expression without 'then'.\n");
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }           
        else if(lex->last_token_type == TOKEN_THEN){
            // condition reutrn because of 'then', or 'then' after 'if'
            pop(taxstack);
            print_stack(taxstack);
        }    
        else{//condition return with 'do'
            printf("Expected 'then' not 'do' at %d:%d,line:%d\n",lex->start,lex->end,lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        PL0Lex_get_token(lex);//after then
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
        return;
    }
    else if(lex->last_token_type == TOKEN_WHILE){
        pop(taxstack);
        push(taxstack,23);
        push(taxstack,33);
        push(taxstack,30);
        push(taxstack,32);
        print_stack(taxstack);
        pop(taxstack);//rm 'while'
        print_stack(taxstack);
        PL0Lex_get_token(lex);
        if(lex->last_token_type == TOKEN_ODD || lex->last_token_type == TOKEN_IDENTIFIER || 
            lex->last_token_type == TOKEN_NUMBER || lex->last_token_type == TOKEN_MINUS || 
            lex->last_token_type == TOKEN_LPAREN){
                condition(lex);
        }
        else if(lex->last_token_type == TOKEN_DO){
            printf("'while' expression without 'condition'.\n");
            pop(taxstack);//rm 'O'
            print_stack(taxstack);
        }
        else if(lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type == TOKEN_PERIOD
            || lex->last_token_type == TOKEN_END){
            printf("'while' without 'condition','do'&'statement'.\n");
            pop(taxstack);
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        else{
            printf("'while' with illegal 'condition'.\n");
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
            // condition reutrn because of ';' or '.'
            printf("'if' expression without 'do'.\n");
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }           
        else if(lex->last_token_type == TOKEN_DO){
            // condition reutrn because of 'do', or 'do' after 'while'
            pop(taxstack);
            print_stack(taxstack);
        }    
        else{//condition return with 'then'
            printf("Expected 'do' not 'then' at %d:%d,line:%d\n",lex->start,lex->end,lex->line_number);
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END));
                    //Ignore until Follow of F, ';' or '.' or 'end'.
            pop(taxstack);
            pop(taxstack);
            print_stack(taxstack);
            return;
        }
        PL0Lex_get_token(lex);//after do.
        if(lex->last_token_type == TOKEN_IDENTIFIER || lex->last_token_type == TOKEN_BEGIN
            || lex->last_token_type == TOKEN_IF || lex->last_token_type == TOKEN_WHILE ||
            lex->last_token_type == TOKEN_CALL){
            statement(lex);
        }
        else if(lex->last_token_type == TOKEN_PERIOD || lex->last_token_type == TOKEN_SEMICOLON
            ||lex->last_token_type == TOKEN_END){
            printf("'while' without statement.\n");
            pop(taxstack);
            print_stack(taxstack);
        }
        else{
            printf("'while' statement with illegal statement.\n");
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
            lex->last_token_type == TOKEN_CALL){
            statement(lex);//Connote rm of 'F'
            break;
        }
        else{
            printf("Illegal statement in 'statements'.\n");
            while(1){ //One illegal statement
                PL0Lex_get_token(lex);
                if(lex->last_token_type == TOKEN_SEMICOLON){
                    PL0Lex_get_token(lex);
                    break;
                }
                else if(lex->last_token_type == TOKEN_END || lex->last_token_type == TOKEN_PERIOD){
                    pop(taxstack);//rm 'F'
                    pop(taxstack);//rm 'M'
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
        printf("Expected ';'.\n");
        pop(taxstack);//rm ';'
        pop(taxstack);//rm 'S' with epsilon
        print_stack(taxstack);
        return;
    }
}
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
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
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
            || lex->last_token_type == TOKEN_DO){
            printf("Warning: condition with only single expression.\n");
            pop(taxstack);
            print_stack(taxstack);//rm 'Q' with epsilon
            return;
        }
        else if(lex->last_token_type==TOKEN_EQU||lex->last_token_type == TOKEN_NEQ
            || lex->last_token_type==TOKEN_LES || lex->last_token_type == TOKEN_LEQ 
            || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ)
        {
            Q(lex);//connote rm of 'Q'
            if(lex->last_token_type==TOKEN_EQU||lex->last_token_type == TOKEN_NEQ
            || lex->last_token_type==TOKEN_LES || lex->last_token_type == TOKEN_LEQ 
            || lex->last_token_type == TOKEN_GTR || lex->last_token_type == TOKEN_GEQ)
            {
                printf("Too much logic operation ofr one condition!\n");
                while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                        lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                        lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
                        //Ignore until Follow of F, ';' or '.' or 'end' or 'then' or 'do'.
            }
        }
        else{
            printf("Illegal logic operation.\n");
            while(PL0Lex_get_token(lex) && !(lex->last_token_type==TOKEN_PERIOD||
                    lex->last_token_type == TOKEN_SEMICOLON || lex->last_token_type==TOKEN_END||
                    lex->last_token_type == TOKEN_THEN || lex->last_token_type == TOKEN_DO));
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

