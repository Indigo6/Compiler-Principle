#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "common/common.h"
#include "lex/pl0_lex.h"

void show_help(const char * arg0)
{
	printf("Usage: %s <src>\n\n", arg0);
}

int main(int argc, char * argv[])
{
	/* Parse arguments */
	if (argc != 2)
	{
		show_help(argv[0]);
		exit(-1);
	}
	fin = fopen(argv[1], "rb");
	if (!fin)
	{
		printf("Fatal: Cannot open file for reading: %s\n", argv[1]);
		exit(-1);
	}

	/* Start */
	printf("=== This is the program for PL/0 testing ===\n");
	
	/* Setup */
	compiler = PL0Compiler_create();

	/* Lexical Analysis */
	printf("--- Lexical Analysis testing ---\n");
	PL0Lex * lex = compiler->lex;
	while (PL0Lex_get_token(lex))
	{
		//assert(lex->last_token_type != TOKEN_NULL);
		assert(lex->last_token_type != TOKEN_RESWORDS);
		assert(lex->last_token_type != TOKEN_SYMBOL);
		if (lex->last_token_type == TOKEN_NULL)
		{
			printf("error in line %d, %d-%d\n",lex->line_num,lex->start,lex->end);
		}
		else if (lex->last_token_type == TOKEN_IDENTIFIER)
		{
			printf("Identifier:    %-10s %d:%d-%d\n",lex->last_id,lex->line_num,lex->start,lex->end);
		}
		else if (lex->last_token_type == TOKEN_NUMBER)
		{
			printf("Number:        %-10d %d:%d-%d\n",lex->last_num,lex->line_num,lex->start,lex->end);
		}
		else if (lex->last_token_type > TOKEN_RESWORDS)
		{
			printf("Reserved word: %-10s %d:%d-%d\n",TOKEN_RESERVED_WORDS[lex->last_token_type - TOKEN_RESWORDS - 1],lex->line_num,lex->start,lex->end);
		}
		else
		{
			printf("Symbol:        %-10s %d:%d-%d\n",TOKEN_SYMBOLS[lex->last_token_type - TOKEN_SYMBOL - 1],lex->line_num,lex->start,lex->end);
		}
	}

	printf("--- Lexical Analysis testing end. ---\n");

	/* Cleanup */
	fclose(fin);
	PL0Compiler_destroy(compiler);

	/* Finish */
	printf("=== Normal end for testing. ===\n");
	return 0;
}
