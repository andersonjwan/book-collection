#include <stdio.h>
#include <ctype.h>
#include "lex.h"

/*
 * !(*current)           => (*current) != 1 or (*current) == '\0' or
 *                       => (*current) == 0
 *
 * !(gets(input_buffer)) => gets(input_buffer) == NULL
 *
 * (*current)            => (*current) != '\0' or (*current) != 0
 */

char    *yytext   = "";    /* lexeme - not '\0' terminated */
int      yylen    = 0;     /* lexeme length */
int      yylineno = 0;     /* input line number */

int
lex(void)
{
  static char input_buffer[128]; // input buffer persists through calls
  char *current;

  current = yytext + yylen; /* skip current lexeme */

  while(1) {
    while(!(*current)) {
      // current character is '\0'
      current = input_buffer; // current = first character in line

      if(!fgets(input_buffer, 127, stdin)) {
        /* no characters left to read on line */
        *current = '\0';
        return EOI;
      }

      // ignore whitespace at the beginning of the line
      while(isspace(*current)) {
        ++current; // increment the pointer to the next character
      }
    }

    for( ; (*current); ++current) {
      /* get the next token on the line */
      yytext = current; // yytext = start of token
      yylen  = 1;

      switch(*current) {
      case EOF: return EOI    ;
      case ';': return SEMI   ;
      case '+': return PLUS   ;
      case '*': return TIMES  ;
      case '(': return LPAREN ;
      case ')': return RPAREN ;

      /* ignore whitespace */
      case '\n' : ++yylineno; break;
      case '\t' :
      case ' '  : break;

      default:
        if(!isalnum(*current)) {
          /* NOT a digit or a letter */
          fprintf(stderr, "Ignoring Illegal Input <%c>\n", *current);
        }
        else {
          while(isalnum(*current)) {
            ++current;
          }

          yylen = current - yytext; // current = character after token
          return NUM_ID;
        }

        break;
      }
    }
  }
}

static int Lookahead = -1;

int
match(int token)
{
  if(Lookahead == -1) {
    /* first call */
    Lookahead = lex();
  }

  return token == Lookahead; // 1 if equivalent, otherwise 0
}

void
advance(void)
{
  /* advance the Lookahead to the next input symbol */
  Lookahead = lex();
}
