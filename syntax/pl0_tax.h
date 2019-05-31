<<<<<<< HEAD
#ifndef __PL0_TAX_H__
#define __PL0_TAX_H__

#include "../lex/pl0_lex.h"
#define TXMAX				500 		// max length of token table
#define MAXADDRESS 	32767		// max address
#define MAXSTACKSIZE 200


/*variables for token table*/
//int table_index = 0;

extern const char* lexLabel[];
/* P in 0, B in 1, D in 2, . in 3, S in 4, C in 5, V in 6, R in 7, const in 8, A in 9, ; in 10, id in 11
  = in 12, num in 13, W in 14, , in 15, V in 16, var in 17, E in 18 H in 19, R in 20, procedure in 21
  S in 22, F in 23, M in 24, := in 25, call in 26, begin in 27, end in 28, if in 29, O in 30, then in 31,
  while in 32, do in 33, odd in 34, X in 35, Q in 36, != in 37, <= in 38, >= in 39, < in 40, > in 41,
  T in 42, G in 43, + in 44, - in 45, * in 46 , / in 47, Y in 48, Z in 49, ( in 50, ) in 51,
  return in 52,I in 53,J in 54,K in 55,
 	THEN_STMT in 56, ELIF_STMT in 57, ELSE_STMTS in 58, elif in 59, else in 60,print in 61*/
//extern const char* instructions[];
typedef struct{
    int Stack[MAXSTACKSIZE];
    int length;
}stack;
/*struct for token table*/
typedef struct {
	char name[MAX_ID_LEN + 1];
	int kind;
	int value;
	short level;
	short address;
} Table;

/*definition for token table*/
Table token_table[TXMAX];

/*identifier type*/
enum idtype {
	ID_CONSTANT,
	ID_VARIABLE,
	ID_PROCEDURE
};


/*operations for token table*/
void table_append(PL0Lex * lex, int kind);

/*functions for syntax analysis*/
void elif_stmts(PL0Lex * lex);
void statement(PL0Lex * lex); //analysis the statement F
void condition(PL0Lex * lex); //analysis the condition statement O
void expression(PL0Lex * lex); //analysis the expression  X
void term(PL0Lex * lex); //analysis the term T
void factor(PL0Lex * lex); //analysis the factor
void program_block(PL0Lex * lex); //analysis the program block
void const_declaration(PL0Lex * lex);
void variable_declaration(PL0Lex* lex);
void procedure_declaration(PL0Lex* lex);
void const_pro(PL0Lex* lex);
void variable_pro(PL0Lex* lex);
void block(PL0Lex* lex);
void W(PL0Lex* lex);
void H(PL0Lex* lex);
void I(PL0Lex* lex);
void J(PL0Lex* lex);
void K(PL0Lex* lex);
void II(PL0Lex* lex);
void JJ(PL0Lex* lex);
void KK(PL0Lex* lex);
void statements(PL0Lex* lex); // S 语句序列
void M(PL0Lex* lex); // M 消除左递归
void Q(PL0Lex* lex); //Q 消除左递归
void G(PL0Lex* lex); //G
void Y(PL0Lex* lex); //因子
void Z(PL0Lex* lex);
int top(stack* s);
int pop(stack* s);
void push(stack* s, int element);
void print_stack(stack* s);
void initializestack(stack* s);
void destroystack(stack* s);
BOOL is_defined(const char* id,int kind);
int indexInTable(const char* id,short level); // return -1 if not find, otherwise return the index of the element in the  table
void generate_code();

=======
#ifndef __PL0_TAX_H__
#define __PL0_TAX_H__

#include "../lex/pl0_lex.h"
#define TXMAX				500 		// max length of token table
#define MAXADDRESS 	32767		// max address
#define MAXSTACKSIZE 200

/*variables for token table*/
//int table_index = 0;

extern const char* lexLabel[];
/* P in 0, B in 1, D in 2, . in 3, S in 4, C in 5, V in 6, R in 7, const in 8, A in 9, ; in 10, id in 11
  = in 12, num in 13, W in 14, , in 15, V in 16, var in 17, E in 18 H in 19, R in 20, procedure in 21
  S in 22, F in 23, M in 24, := in 25, call in 26, begin in 27, end in 28, if in 29, O in 30, then in 31,
  while in 32, do in 33, odd in 34, X in 35, Q in 36, != in 37, <= in 38, >= in 39, < in 40, > in 41,
  T in 42, G in 43, + in 44, - in 45, * in 46 , / in 47, Y in 48, Z in 49, ( iin 50, ) in 51*/
typedef struct{
    int Stack[MAXSTACKSIZE];
    int length;
}stack;
/*struct for token table*/
typedef struct {
	char name[MAX_ID_LEN + 1];
	int kind;
	int value;
	short level;
	short address;
} Table;

/*definition for token table*/
Table token_table[TXMAX];

/*identifier type*/
enum idtype {
	ID_CONSTANT,
	ID_VARIABLE,
	ID_PROCEDURE
};


/*operations for token table*/
void table_append(PL0Lex * lex, int kind);

/*functions for syntax analysis*/
void statement(PL0Lex * lex); //analysis the statement F
void condition(PL0Lex * lex); //analysis the condition statement O
void expression(PL0Lex * lex); //analysis the expression  X
void term(PL0Lex * lex); //analysis the term T
void factor(PL0Lex * lex); //analysis the factor
void program_block(PL0Lex * lex); //analysis the program block
void const_declaration(PL0Lex * lex);
void variable_declaration(PL0Lex* lex);
void procedure_declaration(PL0Lex* lex);
void block(PL0Lex* lex);
void W(PL0Lex* lex);
void H(PL0Lex* lex);
void statements(PL0Lex* lex); // S 语句序列
void M(PL0Lex* lex); // M 消除左递归
void Q(PL0Lex* lex); //Q 消除左递归
void G(PL0Lex* lex); //G
void Y(PL0Lex* lex); //因子
void Z(PL0Lex* lex);
int top(stack* s);
int pop(stack* s);
void push(stack* s, int element);
void print_stack(stack* s);
void initializestack(stack* s);
void destroystack(stack* s);
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
#endif //pl0_tax.h