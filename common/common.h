#ifndef __COMMON_H__
#define __COMMON_H__
<<<<<<< HEAD
=======

>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
#include <stdio.h>

struct _tPL0Lex;

typedef struct _tPL0Compiler {
	struct _tPL0Lex * lex;
} PL0Compiler;


typedef enum BOOLEAN {
	FALSE,
	TRUE,
} BOOL;


<<<<<<< HEAD

/* Global variables */
extern FILE * fin;
extern FILE * fout;
extern PL0Compiler * compiler;


=======
/* Global variables */
extern FILE * fin;
extern PL0Compiler * compiler;

>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
/* Functions */
PL0Compiler * PL0Compiler_create();
BOOL PL0Compiler_destroy(PL0Compiler * compiler);

#endif /* common.h */
