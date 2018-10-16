#ifndef __PL0_LEX_H__
#define __PL0_LEX_H__

#include "../common/common.h"
#define NRW			11	/* Number of reserved words */
#define NSYM		16	/* Number of symbols */
#define MAX_NUM_LEN	9	/* Maximum length of a number, set to 9 to fit in range of C (-2147483648 to 2147483647) */
#define MAX_ID_LEN	10	/* Maximum length of an identifier */
#define MAX_TOKEN_LEN  10  //Maximum length

struct _tPL0Compiler;

typedef enum _tPL0TokenType {
	TOKEN_NULL,
	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,
	TOKEN_SYMBOL,	/* Below are accepted symbols */
	TOKEN_PLUS,		/* + */
	TOKEN_MINUS,	/* - */
	TOKEN_TIMES,	/* * */
	TOKEN_SLASH,	/* / */
	TOKEN_EQU,  	/* = */
	TOKEN_NEQ,  	/* <> */
	TOKEN_LES,  	/* < */
	TOKEN_LEQ,  	/* <= */
	TOKEN_GTR,  	/* > */
	TOKEN_GEQ,  	/* >= */
	TOKEN_LPAREN,	/* ( */
	TOKEN_RPAREN,	/* ) */
	TOKEN_COMMA,	/* , */
	TOKEN_SEMICOLON,/* ; */
	TOKEN_PERIOD,	/* . */
	TOKEN_BECOMES,	/* := */
	TOKEN_RESWORDS, /* Below are reserved words */
	TOKEN_VAR,
	TOKEN_CONST,
	TOKEN_PROCEDURE,
	TOKEN_BEGIN,
	TOKEN_END,
	TOKEN_IF,
	TOKEN_THEN,
	TOKEN_DO,
	TOKEN_WHILE,
	TOKEN_CALL,
	TOKEN_ODD,
} PL0TokenType;

extern const char * TOKEN_RESERVED_WORDS[NRW];
extern const char * TOKEN_SYMBOLS[NSYM];
typedef struct _tPL0Lex {
	/* Parent return pointer */
	struct _tPL0Compiler * compiler;
	
	/* For output */
	PL0TokenType last_token_type;
	char last_id[MAX_ID_LEN + 1];
	int last_num;


	/** --------------------------
	 * TODO: Your variables here
	 */
	 int line_number; //to record which line of the code is scanning.
	 int start, end;  //to record the start and end index of the last token.
	 int offset;	// temp variable for offset in line
	 int iter;	//array 'token' index
	 char token[MAX_TOKEN_LEN + 1];  //to store the last token

} PL0Lex;

PL0Lex * PL0Lex_create(struct _tPL0Compiler * parent);
BOOL PL0Lex_destroy(PL0Lex * lex);
BOOL get_token(PL0Lex * lex);
BOOL PL0Lex_get_token(PL0Lex * lex);
void analysis(const char * word, PL0Lex * lex);
int is_reservedword(const char * word);
int is_symbol(const char * word);
BOOL is_id(const char* word);
BOOL is_num(const char * word);


#endif /* pl0_lex.h */
