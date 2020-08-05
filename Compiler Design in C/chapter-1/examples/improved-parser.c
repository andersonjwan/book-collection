#include <stdio.h>
#include "improved-parser.h"
#include "lex.h"

void
statements(void)
{
  while(!match(EOI)) {
    expression();

    if(match(SEMI)) {
      advance();
    }
    else {
      fprintf(stderr, "%d: Expected semicolon\n", yylineno);
    }
  }
}

void
expression(void)
{
  if(!legal_lookahead(NUM_ID, LPAREN, 0)) {
    return;
  }

  term();
  while(match(PLUS)) {
    advance();
    term();
  }
}

void
term(void)
{
  if(!legal_lookahead(NUM_ID, LPAREN, 0)) {
    return;
  }

  factor();
  while(match(TIMES)) {
    advance();
    factor();
  }
}

void
factor(void)
{
  if(!legal_lookahead(NUM_ID, LPAREN, 0)) {
    return;
  }

  if(match(NUM_ID)) {
    advance();
  }
  else if(match(LPAREN)) {
    advance();
    expression();

    if(match(RPAREN)) {
      advance();
    }
    else {
      fprintf(stderr, "%d: Unmatched parenthesis\n", yylineno);
    }
  }
  else {
    fprintf(stderr, "%d: Number of Identifier expected\n", yylineno);
  }
}

#include <stdarg.h>

#define MAXFIRST 16
#define SYNCH    SEMI

int
legal_lookahead(int first_arg, ...)
{
  va_list args;

  int     tok;
  int     lookaheads[MAXFIRST], *p = lookaheads, *current;
  int     error_printed = 0;
  int     rval          = 0;

  va_start(args, first_arg);

  if(!first_arg) {
    if(match(EOI)) {
      rval = 1;
    }
  }
  else {
    ++p;
    *p = first_arg;

    while((tok = va_arg(args, int)) && p < &lookaheads[MAXFIRST]) {
      ++p;
      *p = tok;
    }

    while(!match(SYNCH)) {
      for(current = lookaheads; current < p; ++current) {
        if(match(*current)) {
          rval = 1;
          goto exit;
        }
      }

      if(!error_printed) {
        fprintf(stderr, "Line %d: Syntax Error\n", yylineno);
        error_printed = 1;
      }

      advance();
    }
  }

 exit:
  va_end(args);
  return rval;
}
