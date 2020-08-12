#include <stdio.h>
#include "lex-v2.h"

void print_token(int);

int
main(void)
{
  int token;
  do {
    token = lex();
    print_token(token);
  }
  while(token != EOI);

  return 0;
}

void
print_token(int token)
{
  fprintf(stdout, "LEXEME: '%0.*s' (", yylen, yytext);

  switch(token) {
  case ERROR:     fprintf(stdout, "ERROR");     break;
  case EOI:       fprintf(stdout, "EOI");       break;
  case SEMICOLON: fprintf(stdout, "SEMICOLON"); break;
  case PLUS:      fprintf(stdout, "PLUS");      break;
  case MINUS:     fprintf(stdout, "MINUS");     break;
  case MULT:      fprintf(stdout, "MULT");      break;
  case DIVIDE:    fprintf(stdout, "DIVIDE");    break;
  case LPAREN:    fprintf(stdout, "LPAREN");    break;
  case RPAREN:    fprintf(stdout, "RPAREN");    break;
  case NUM:       fprintf(stdout, "NUM");       break;
  case ID:        fprintf(stdout, "ID");        break;
  default:
    fprintf(stdout, "UNRECOGNIZED TOKEN: %d", token);
    break;
  }

  fprintf(stdout, ")\n");
  return;
}
