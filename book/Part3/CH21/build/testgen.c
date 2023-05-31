// CH21:build/testgen.c
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include "tree.h"
int main(int argc, char * * argv)
{
  // argv[1]: number of nodes
  // argv[2]: inorder output
  // argv[3]: postorder output
  // argv[4]: preorder output
  // argv[5] (optional): seed
  if (argc < 4) { return EXIT_FAILURE; }
  int numnode = (int) strtol(argv[1], NULL, 10);
  if (numnode <= 0) { return EXIT_FAILURE; }
  int randseed = time(NULL);
  if (argc == 6) { randseed = (int) strtol(argv[5], NULL, 10); }
  srand(randseed);
  TreeNode * tn = NULL;
  while (numnode > 0)
    {
      int val = rand() % 10000;
      // printf("insert %d\n", val);
      tn = insertNode(tn, val);
      numnode --;
    }
  inOrder(tn, argv[2]);
  postOrder(tn, argv[3]);
  preOrder(tn, argv[4]);
  printTree(tn);
  destroyTree(tn);
  return EXIT_SUCCESS;
}
