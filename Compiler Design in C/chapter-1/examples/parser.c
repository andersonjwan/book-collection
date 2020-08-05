#include <stdio.h>
#include "parser.h"
#include "lex.h"

void
statements(void)
{
  /*
   * statements ::= expression; |
   *                expression; statements
   */

  expression();

  if(match(SEMI)) {
    advance();
  }
  else {
    fprintf(stderr, "%d: Expected semicolon\n", yylineno);
  }

  if(!match(EOI)) {
    statements();
  }
}

void
expression(void)
{
  /*
   * expression ::= term expression'
   */

  term();
  expression_prime();
}

void
expression_prime(void)
{
  /*
   * expression_prime ::= + term expression' |
   *                      epsilon
   */

  if(match(PLUS)) {
    advance();
    term();
    expression_prime();
  }
  else {
    // epsilon
    return;
  }
}

void
term(void)
{
  /*
   * term ::= factor term'
   */

  factor();
  term_prime();
}

void
term_prime(void)
{
  /*
   * term_prime ::= * factor term' |
   *                epsilon
   */

  if(match(TIMES)) {
    advance();
    factor();
    term_prime();
  }
  else {
    // epsilon
    return;
  }
}

void
factor(void)
{
  /*
   * factor ::= NUM_ID |
   *            (expression)
   */

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
    fprintf(stderr, "%d: Number or Identifier expected\n", yylineno);
  }
}
