#include <stdio.h>
#include "args.h"
#include "name.h"
#include "lex.h"

void statements(void);
void factor(char *tmpvar);
void term(char *tmpvar);
void expression(char *tmpvar);

void
statements(void)
{
  char *tmpvar;

  while(!match(EOI)) {
    expression(tmpvar = new_name());
    free_name(tmpvar);

    if(match(SEMI)) {
      advance();
    }
    else {
      fprintf(stderr, "%d: Expected semicolon.\n", yylineno);
    }
  }
}

void
expression(char *tmpvar)
{
  char *tmpvar_02;

  term(tmpvar);

  while(match(PLUS)) {
    advance();

    term(tmpvar_02 = new_name());

    printf("    %s += %s\n", tmpvar, tmpvar_02);
    free_name(tmpvar_02);
  }
}

void
term(char *tmpvar)
{
  char *tmpvar_02;

  factor(tmpvar);

  while(match(TIMES)) {
    advance();

    factor(tmpvar_02 = new_name());

    printf("    %s *= %s\n", tmpvar, tmpvar_02);
    free_name(tmpvar_02);
  }
}

void
factor(char *tmpvar)
{
  if(match(NUM_ID)) {
    printf("    %s = %0.*s\n", tmpvar, yylen, yytext);
    advance();
  }
  else if(match(LPAREN)) {
    advance();
    expression(tmpvar);

    if(match(RPAREN)) {
      advance();
    }
    else {
      fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
    }
  }
  else {
    fprintf(stderr, "%d: Number or Identifier expected.\n", yylineno);
  }
}
