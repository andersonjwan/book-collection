#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "exercise-1.4.h"

/* English to Declarations Grammar
 *
 * <sentence>    ::= <subject> <predicate> .
 * <subject>     ::= <noun>
 * <predicate>   ::= VERB ARTICLE <object>
 * <noun>        ::= ID
 * <object>      ::= TYPE | <pointer> | <array>
 * <pointer>     ::= POINTER ARTICLE ARTICLE <object>
 * <array>       ::= ARRAY <preposition> NUM TYPE
 * <preposition> ::= OF
 */

char *yytext   = "";
int   yylen    = 0;
int   yylineno = 0;

int
lex(void)
{
  static char buffer[256];
  char *current;

  current = yytext + yylen;

  while(1) {
    while(!(*current)) {
      current = buffer;

      if(!fgets(buffer, 256, stdin)) {
        *current = '\0';
        return EOI;
      }

      /* ignore whitespace */
      while(isspace(*current)) {
        ++current;
      }
    }

    for( ; (*current); ++current) {
      yytext = current;
      yylen = 1;

      switch(*current) {
      case EOF: return EOI;
      case '.': return PERIOD;

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

          char lexeme[256];
          strncpy(lexeme, yytext, yylen);
          lexeme[yylen] = '\0';

          /* tokenize word */
          if(strcmp(lexeme, "is") == 0) {
            return VERB;
          }
          else if(strcmp(lexeme, "int")   == 0 ||
                  strcmp(lexeme, "char")  == 0 ||
                  strcmp(lexeme, "float") == 0) {
            return TYPE;
          }
          else if(strcmp(lexeme, "pointer")  == 0 ||
                  strcmp(lexeme, "pointers") == 0) {
            return POINTER;
          }
          else if(strcmp(lexeme, "array") == 0) {
            return ARRAY;
          }
          else if(strcmp(lexeme, "of") == 0) {
            return PREPOSITION;
          }
          else if(strcmp(lexeme, "a")  == 0 ||
                  strcmp(lexeme, "an") == 0 ||
                  strcmp(lexeme, "to") == 0) {
            return ARTICLE;
          }
          else {
            return ID;
          }
        }
        else {
          return ERROR;
        }
      }
    }
  }
}

int
main(void)
{
  int token;

  do {
    token = lex();
    printf("LEXEME: %0.*s (%d)\n", yylen, yytext, token);
  }
  while(token != EOI);

  return 0;
}
