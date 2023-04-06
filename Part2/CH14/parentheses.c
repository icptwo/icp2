// CH14:parentheses.c
#include <stdio.h>
#include <stdlib.h>
void generate(char * parentheses, int num, int left, int right)
{
  // num: total number of pairs
  // left: how many left parentheses have been used
  // right: how many right parentheses have been used
  int ind = left + right;
  if (left == num)   // use up all '('
    {
      for (int i = 0; i < ind; i ++) { printf("%c", parentheses[i]); }
      // use all remaining ')'
      for (int i = right; i < num; i ++) { printf(")");	}	
      printf("\n");
      return;
    }
  // case 1: add '('. always possible because left < num 
  parentheses[ind] = '(';
  generate(parentheses, num, left + 1, right);
  // case 2: check whether ')' can be added
  // allowed only if left > right
  if (left > right)
    {
      parentheses[ind] = ')';
      generate(parentheses, num, left, right + 1);
    }
}
int main(int argc, char * * argv)
{
  if (argc < 2) { return EXIT_FAILURE; }
  int num = (int) strtol(argv[1], NULL, 10);   // num: how many pairs
  if (num < 1)  { return EXIT_FAILURE; }
  char * parentheses = malloc(sizeof (* parentheses) * num * 2);
  generate(parentheses, num, 0, 0);
  free (parentheses);
  return EXIT_SUCCESS;
}
