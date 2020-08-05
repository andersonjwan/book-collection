#ifndef IMPROVED_PARSER_H
#define IMPROVED_PARSER_H

void statements(void);
void expression(void);
void term(void);
void factor(void);

int legal_lookahead(int, ...);

#endif
