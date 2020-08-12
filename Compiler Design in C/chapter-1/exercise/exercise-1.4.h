#ifndef EXERCISE_4_H
#define EXERCISE_4_H

/* Tokens */
#define EOI         256 // end of input
#define ID          257 // [Aa - Zz]*
#define VERB        258 // "is"
#define TYPE        259 // "int", "char", "float", etc.
#define POINTER     260 // "pointer"
#define ARRAY       261 // "array"
#define PREPOSITION 262 // "of"
#define ARTICLE     263 // "a", "an", "to"
#define PERIOD      264 // '.'
#define NUM         265 // [0-9]*
#define ERROR       266 // ERROR

extern char *yytext;
extern int   yylen;
extern int   yylineno;

/* forward declaration(s) */
int  lex(void);
int  match(void);
void advance(void);
#endif
