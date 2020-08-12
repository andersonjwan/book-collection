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
 * <array>       ::= ARRAY PREPOSITION NUM TYPE
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
          else if(strcmp(lexeme, "int")    == 0 ||
                  strcmp(lexeme, "ints")   == 0 ||
                  strcmp(lexeme, "char")   == 0 ||
                  strcmp(lexeme, "chars")  == 0 ||
                  strcmp(lexeme, "float")  == 0 ||
                  strcmp(lexeme, "floats") == 0) {
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

void
syntax_error(void)
{
  fprintf(stderr, "%d: Syntax Error\n", yylineno);
  return;
}

void
parse_sentence(void)
{
  parse_subject();
  parse_predicate();

  if(match(PERIOD)) {
    advance();
  }
  else {
    syntax_error();
  }
}

void
parse_subject(void)
{
  parse_noun();
}

void
parse_noun(void)
{
  if(match(ID))
    advance();
  else
    syntax_error();
}

void
parse_predicate(void)
{
  if(match(VERB))
    advance();
  else
    syntax_error();

  if(match(ARTICLE))
    advance();
  else
    syntax_error();

  parse_object();
}

void
parse_object(void)
{
  if(match(TYPE)) {
    advance();
  }
  else if(match(POINTER)) {
    parse_pointer();
  }
  else if(match(ARRAY)) {
    parse_array();
  }
  else {
    syntax_error();
  }
}

void
parse_pointer(void)
{
  if(match(POINTER))
    advance();
  else
    syntax_error();

  if(match(ARTICLE))
    advance();
  else
    syntax_error();

  if(match(ARTICLE))
    advance();
  else
    syntax_error();

  parse_object();
}

void
parse_array(void)
{
  if(match(ARRAY))
    advance();
  else
    syntax_error();

  if(match(PREPOSITION))
    advance();
  else
    syntax_error();

  if(match(NUM))
    advance();
  else
    syntax_error();

  if(match(TYPE))
    advance();
  else
    syntax_error();
}

int
main(void)
{
  while(lookahead != EOI) {
    parse_sentence();
  }

  return 0;
}
