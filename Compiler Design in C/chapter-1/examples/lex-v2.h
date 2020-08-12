#ifndef LEX_V2_H
#define LEX_V2_H

/* unicode ascii values end at 255 */
#define ERROR      256 // ERROR
#define EOI        257 // END OF INPUT
#define SEMICOLON  258 // ;
#define PLUS       259 // +
#define MINUS      260 // '-'
#define MULT       261 // '*'
#define DIVIDE     262 // '/'
#define LPAREN     263 // '('
#define RPAREN     264 // ')'
#define NUM        265 // [0-9]*
#define ID         266 // [Aa-Zz]*
#define EQUALS     267 // '='

extern char *yytext;
extern int   yylen;
extern int   yylineno;

/* forward declaration(s) */
int  lex(void);
int  match(int);
void advance(void);

#endif
