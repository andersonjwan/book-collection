#include <stdio.h>
#include "name.h"
#include "retval.h"
#include "lex.h"

void
statements(void)
{
  char *tmpvar;

  while(!match(EOI)) {
    tmpvar = expression();

    if(match(SEMI)) {
      advance();
    }
    else {
      fprintf(stderr, "%d: Expected semicolon\n", yylineno);
    }
  }
}

char *
expression(void)
{
  char *tmpvar_01, *tmpvar_02;

  tmpvar_01 = term();

  while(match(PLUS)) {
    advance();
    tmpvar_02 = term();

    printf("    %s += %s\n", tmpvar_01, tmpvar_02);
    free_name(tmpvar_02);
  }

  return tmpvar_01;
}

char *
term(void)
{
  char *tmpvar_01, *tmpvar_02;

  tmpvar_01 = factor();

  while(match(TIMES)) {
    advance();
    tmpvar_02 = factor();

    printf("    %s *= %s\n", tmpvar_01, tmpvar_02);
    free_name(tmpvar_02);
  }

  return tmpvar_01;
}

char *
factor(void)
{
  char *tmpvar;

  if(match(NUM_ID)) {
    printf("    %s = %0.*s\n", tmpvar = new_name(), yylen, yytext);
    advance();
  }
  else if(match(LPAREN)) {
    advance();
    tmpvar = expression();

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

  return tmpvar;
}
