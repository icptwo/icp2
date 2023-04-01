// CH27:binary:compress:compress.c
#include "compress.h"
#include "bits.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMCHAR 128
TreeNode * buildTree(CharOccur * chararr)
{
  ListNode * head = NULL;
  int ind;
  // build the initial tree
  for (ind = 0; ind < NUMCHAR; ind ++)
    {
      CharOccur * optr = & chararr[ind];
      if ((optr -> occur) != 0)
	{ head = List_insertChar(head, optr -> ascii, optr -> occur); }
    }
  List_print(head);
  // printf("----------------\n");
  // merge the trees
  while ((head -> next) != NULL)
    {
      TreeNode * tree1 = head -> tnptr;
      TreeNode * tree2 = (head -> next) -> tnptr;
      TreeNode * tp  = Tree_merge(tree1, tree2);
      ListNode * p = head;
      ListNode * q = head -> next;
      head = List_insertTree(q -> next, tp);
      free (p);
      free (q);
    }
  List_print(head);
  TreeNode * tree = head -> tnptr;
  free (head);
  return tree;
}
void codeBookHelper(TreeNode * tree, char * * codeBook,
		    char * code, int ind)
{
  if (tree == NULL) { return; }
  if ((tree -> left) == NULL) // leaf node
    {
      char ascii = tree -> ascii;
      codeBook[(int) ascii] = malloc(sizeof(char) * (ind + 1));
      int digit;
      for (digit = 0; digit < ind; digit ++)
	{ codeBook[(int) ascii][digit] = code[digit] + '0'; }
      codeBook[(int) ascii][ind] = '\0'; // end string
      return;
    }
  code[ind] = 0;
  codeBookHelper(tree -> left, codeBook, code, ind + 1);
  code[ind] = 1;
  codeBookHelper(tree -> right, codeBook, code, ind + 1);  
}
void buildCodeBook(TreeNode * tree, char * * codeBook)
{
  int height = Tree_height(tree); // this is the longest code
  char * code = malloc(sizeof(char) * height);
  codeBookHelper(tree, codeBook, code, 0);
  free (code);
}
void printCodeBook(char * * codeBook)
{
  int ind;
  for (ind = 0; ind < NUMCHAR; ind ++)
    {
      if (codeBook[ind] != NULL)
	{ printf("%c: %s\n", ind, codeBook[ind]); }
    }
}
void destroyCodeBook(char * * codeBook)
{
  int ind;
  for (ind = 0; ind < NUMCHAR; ind ++)
    {
      if (codeBook[ind] != NULL) { free (codeBook[ind]); }
    }
}
void encode(char * infile, char * outfile,
	    TreeNode * tree, char * * codeBook)
{
  FILE * inptr = fopen(infile, "r");
  if (inptr == NULL) { return; }
  FILE * outptr = fopen(outfile, "w");
  if (outptr == NULL) { return; }
  // save the tree in the output file
  Tree_save(tree, outptr);
  // find the length of the file
  fseek(inptr, 0, SEEK_END);
  int length = ftell(inptr);
  // save the file length in the output file
  fwrite(& length, sizeof(int), 1, outptr);
  // no need to pad zero
  unsigned char newline = '\n';
  fwrite(& newline, sizeof(unsigned char), 1, outptr);
  // convert the letters from the input and save in the output file
  fseek(inptr, 0, SEEK_SET); // go back to the beginning of the file
  int count = 0;
  unsigned char whichbit = 0;
  unsigned char curbyte  = 0;
  while (! feof(inptr))
    {
      int ch = fgetc(inptr);
      if (ch != EOF)
	{
	  int iter;
	  for (iter = 0; iter < strlen(codeBook[ch]); iter ++)
	    {
	      writeBit(outptr, codeBook[ch][iter] - '0',
		       & whichbit, & curbyte);
	    }
	  count ++;
	}
    }
  if (count != length)
    { printf("count = %d, length = %d\n", count, length); }
  padZero(outptr, & whichbit, & curbyte);
  fclose (inptr);
  fclose (outptr);
}
int main(int argc, char * * argv)
{
  if (argc != 3) { return EXIT_FAILURE; }
  // argv[1]: input file name
  // argv[2]: output file name
  CharOccur chararr[NUMCHAR];
  int total = countOccur(argv[1], chararr);
  if (total == 0) { return EXIT_FAILURE; } // nothing in the file
  TreeNode * tree = buildTree(chararr);
  if (tree == NULL) { return EXIT_FAILURE; }
  char * codeBook[NUMCHAR] = {NULL};
  buildCodeBook(tree, codeBook);
  printCodeBook(codeBook);
  encode(argv[1], argv[2], tree, codeBook);
  destroyCodeBook(codeBook);
  Tree_destroy(tree);
  return EXIT_SUCCESS;
}
