#include <stdio.h>
#include <string.h>

#define STACK 8  // maximum number of pushback characters

int  pb_buffer[STACK];
int *pb_iter = &pb_buffer[STACK]; // points to the end (top) of the stack

#define get(stream) ((pb_iter <  &pb_buffer[STACK]) ? *(pb_iter++) : getc(stream))
#define unget(c)    ((pb_iter <= &pb_buffer[0]) ? -1           : (*(--pb_iter) = (c)))

void
ungets(char *start, int n)
{
  /* push-back the last n characters of the string by working
   * backwards through the string.
   */

  char *iter = start + strlen(start);

  while((--iter) >= start && (--n) >= 0) {
    if(unget(*iter) == -1) {
      fprintf(stderr, "Pushback Stack Overflow\n");
    }
  }
}

int
main(void)
{
  ungets("TEST", 3);

  for(int i = 0; i < STACK; ++i) {
    if(pb_buffer[i]) {
      printf("%c @ %d\n", pb_buffer[i], i);
    }
  }

  for(int i = 0; i < 4; ++i) {
    printf("GOT: %c\n", get(stdin));
  }

  for(int i = 0; i < STACK; ++i) {
    if(pb_buffer[i]) {
      printf("%c @ %d\n", pb_buffer[i], i);
    }
  }

  printf("complete...\n");
  return 0;
}
