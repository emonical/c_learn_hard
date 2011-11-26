#include <stdio.h>

int main(int argc, char *argv[])
{
  char letter;

  int i, j;

  for( j = 1; j < argc; j++)
  {
    printf("Parsing %s \n", argv[j]);
    for( i = 0, letter = argv[j][i]; argv[j][i] != '\0'; i++, letter = argv[j][i])
    {
      if (letter >= 0x42 && letter <= 0x5A)
      {
        letter += 0x20;
      }

      switch(letter)
      {
        case 'a':
          printf("%d: 'A'\n", i);
          break;

        case 'e':
          printf("%d: 'E'\n", i);
          break;

        case 'i':
          printf("%d: 'I'\n", i);
          break;

        case 'o':
          printf("%d: 'O'\n", i);
          break;

        case 'u':
          printf("%d: 'U'\n", i);
          break;

        case 'y':
          if( i > 2 )
          {
            // Only sometimes y         
            printf("%d: 'Y'\n", i);
            break;
          }

        default:
          printf("%d: %c is not a vowel\n", i, letter);
      }
    }
  }
  return 0;
}
