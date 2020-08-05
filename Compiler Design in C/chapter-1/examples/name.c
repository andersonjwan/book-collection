#include <stdlib.h>

char *Names[] = { "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7" };
char **Name_iter = Names;

char *
new_name(void)
{
  if(Name_iter >= &Names[sizeof(Names) / sizeof(*Names)]) {
    fprintf(stderr, "%d: Expression too complex\n", yylineno);
    exit(1);
  }

  return *(++Name_iter);
}

void
freename(char *s)
{
  if(Name_iter > Names) {
    --Name_iter;
    *(Name_iter) = s;
  }
  else {
    fprintf(stderr, "%d: (Internal Error) Name stack underflow\n", yylineno);
  }
}
