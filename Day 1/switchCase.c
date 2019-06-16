#include <stdio.h>
#include <stdlib.h>


int main()
{
  char alphabet;
  printf("Select a character: ");
  scanf("%c", &alphabet);
  switch(alphabet)
  {
    case 'A':
    printf("You selected apples\n");
    break;
    case 'B':
    printf("You selected bananas\n");
    break;
    case 'G':
    printf("You selected grapes\n");
    break;
    case 'O':
    printf("You selected oranges\n");
    break;
    default:
    printf("No fruit selected\n");
    break;
  }
  return 0;
}