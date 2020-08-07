/*
 * Grammar English to C;
 *
 * sentence ::= ID is a TYPE.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* token types */
enum Tokens {EOI = 0, ID, NUM, VERB, PERIOD, ARTICLE, TYPE};

/* forward declarations */
char *yytext   = "";
char  yylen    = 0;
char  yylineno = 0;

int
lexer(void)
{
  static char buffer[256];
  char *current;

  current = yytext + yylen;

  while(1) {
    while(!(*current)) {
      current = buffer;

      if(!fgets(buffer, 255, stdin)) {
        *current = '\0';
        return EOI;
      }

      // ignore whitespace at the beginning of line
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
      case '\n' : ++yylineno; break;
      case '\t' :
      case ' '  : break;

      default:
        if(isdigit(*current)) {
          while(isdigit(*current)) {
            ++current;
          }

          return NUM;
        }
        else if(isalpha(*current)) {
          while(isalpha(*current)) {
            ++current;
          }

          yylen = current - yytext;

          if(strncmp("is", yytext, yylen) == 0) {
            return VERB;
          }
          else if(strncmp("a",  yytext, yylen) == 0 ||
                  strncmp("an", yytext, yylen) == 0) {
            return ARTICLE;
          }
          else if(strncmp("int",   yytext, yylen) == 0 ||
                  strncmp("char",  yytext, yylen) == 0 ||
                  strncmp("float", yytext, yylen) == 0 ||
                  strncmp("pointer", yytext, yylen) == 0) {
            return TYPE;
          }
          else {
            return ID;
          }
        }
        else {
          fprintf(stderr, "Ignoring Illegal Character: <%c>\n", *current);
        }
      }
    }
  }
}

static int lookahead = -1;

int
match(int token) {
  if(lookahead == -1) {
    lookahead = lexer();
  }

  return token == lookahead;
}

void
advance(void)
{
  lookahead = lexer();
}

void
sentence(void)
{

  while(!match(EOI)) {
    if(match(ID)) {
      advance();

      if(match(VERB)) {
        advance();

        if(match(ARTICLE)) {
          advance();

          if(match(TYPE)) {
            advance();
          }
          else {
            fprintf(stderr, "%d: Expected TYPE.\n", yylineno);
          }
        }
        else {
          fprintf(stderr, "%d: Expected ARTICLE.\n", yylineno);
        }
      }
      else {
        fprintf(stderr, "%d: Expected VERB.\n", yylineno);
      }
    }
    else {
      fprintf(stderr, "%d: Expected Identifier.\n", yylineno);
    }

    if(match(PERIOD)) {
      advance();
    }
    else {
      fprintf(stderr, "%d: Expected PERIOD.\n", yylineno);
    }
  }
}

int
main(void)
{
  sentence();
  return 0;
}
