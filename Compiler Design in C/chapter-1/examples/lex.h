#ifndef LEX_H
#define LEX_H

#define EOI       0     /*  end of input      */
#define SEMI      1     /*     ;              */
#define PLUS      2     /*     +              */
#define TIMES     3     /*     *              */
#define LPAREN    4     /*     (              */
#define RPAREN    5     /*     )              */
#define NUM_ID    6     /* [0-9]* or [Aa-Zz]* */

extern char *yytext;
extern int   yylen;
extern int   yylineno;

/* forward declarations */
int lex(void);
int match(int token);
void advance(void);

#endif
