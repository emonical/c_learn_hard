#include <stdio.h>

int main(int argc, char *argv[])
{

  int i = argc;

  int num_states = 4;

  char * states[] = {
    "California",
    "Oregon",
    "Washington",
    "Texas" 
  };

  int sentinel = num_states;

  while (i > 0)
  {
    printf("arg %d: %s\n", i, argv[i]);
    i--;
    if (sentinel > 0)
    {
      states[sentinel - 1] = argv[i];
      sentinel--;
    }
  }

  i = num_states;

  while(i > 0)
  {
    printf("state %d: %s\n", i, states[i - 1]);
    i--;
  } 

  return 0;
}
