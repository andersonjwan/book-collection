/* Simple Lexical Analyzer v2.0
 *
 * Notes: This lexical analyzer is a replicated
 *        base from 'lex.c' with a implementation of
 *        separate tokens from NUM's and ID's.
 */

#include <stdio.h>
#include <ctype.h>

#include "lex-v2.h"

char *yytext   = ""; // current lexeme
int   yylen    = 0;
int   yylineno = 0;

int
lex(void) {
  static char buffer[128]; // max line length: 128 chars
  char *current;

  current = yytext + yylen; // point to pos after lexeme

  while(1) {
    while(!(*current)) {
      // read line into buffer
      current = buffer; // reset current to point to start of line

      if(!fgets(buffer, 127, stdin)) {
        /* EOF (Ctrl-D) returned */
        *current = '\0';
        return EOI;
      }
    }

    while(isspace(*current)) {
      ++current;
    }

    /* tokenize lexical units */
    while((*current)) {
      yytext = current;
      yylen = 1;

      switch(*current) {
      case EOF: return EOI;
      case ';': return SEMICOLON;
      case '+': return PLUS;
      case '-': return MINUS;
      case '*': return MULT;
      case '/': return DIVIDE;
      case '(': return LPAREN;
      case ')': return RPAREN;

        /* ignore whitespace */
      case '\n': ++yylineno; break;
      case '\t':
      case ' ' : break;

      default:
        if(isdigit(*current)) {
          while(isdigit(*current)) {
            ++current;
          }

          yylen = current - yytext;
          return NUM;
        }
        else if(isalpha(*current)) {
          while(isalpha(*current)) {
            ++current;
          }

          yylen = current - yytext;
          return ID;
        }
        else {
          yylen = 1;
          return ERROR;
        }

        break;
      }

      ++current;
    }
  }
}

static int lookahead = -1;

int
match(int token)
{
  if(lookahead == -1) {
    lookahead = lex();
  }

  return (token == lookahead);
}

void
advance(void)
{
  lookahead = lex();
}
