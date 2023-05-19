// CH27:binary:compress:compress.c
// #include "compress.h"
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
#define ENCODEMODE 0
#define DECODEMODE 1
void printFrequencyLatex(CharFreq * frequencies);
void buildCodeBookHelper(TreeNode * tn, int * * codebook, int * row, int col)
{
  if (tn == NULL) { return; }
  // is it a leaf node?
  TreeNode * lc = tn -> left;
  TreeNode * rc = tn -> right;
  if ((lc == NULL) && (rc == NULL))
    {
      // finish one code
      codebook[*row][0] = tn -> value;
      (* row) ++;
      return;
    }
  if (lc != NULL)
    {
      // populate this column of the entire subtree
      int numRow = Tree_leaf(lc);
      int ind;
      for (ind = * row; ind < (* row) + numRow; ind ++)
	{ codebook[ind][col] = 0; }
      buildCodeBookHelper(lc, codebook, row, col + 1);
    }
  if (rc != NULL)
    {
      int numRow = Tree_leaf(rc);
      int ind;
      for (ind = * row; ind < (* row) + numRow; ind ++)
	{ codebook[ind][col] = 1; }
      buildCodeBookHelper(rc, codebook, row, col + 1);
    }    
}
void buildCodeBook(TreeNode * root, int * * codebook)
{
  int row = 0;
  // column start at 1 because [0] stores the character
  buildCodeBookHelper(root, codebook, & row, 1); 
}
void printCodeBook(int * * codebook, int numRow)
{
  int row;
  for (row = 0; row < numRow; row ++)
    {
      // print the character
      printf("%c: ", codebook[row][0]);
      int col = 1;
      while (codebook[row][col] != -1)
	{
	  printf("%d ", codebook[row][col]);
	  col ++;
	}
      printf("\n");
    }
}
int compress(char * infile, char * outfile, int * * codebook, int * mapping)
{
  FILE * infptr = fopen(infile, "r");
  if (infptr == NULL) { return 0; }
  FILE * outfptr = fopen(outfile, "a"); // append
  if (outfptr == NULL)
    {
      fclose (outfptr);
      return 0;
    }
  unsigned char whichbit = 0;
  unsigned char curbyte = 0;
  while (! feof(infptr))
    {
      int onechar = fgetc(infptr);
      if (onechar != EOF)
	{
	  int ind = mapping[onechar];
	  int ind2 = 1;
	  while (codebook[ind][ind2] != -1)
	    {
	      writeBit(outfptr, (codebook[ind][ind2] == 1),
		       & whichbit, & curbyte);
	      // fprintf(outfptr, "%d", codebook[ind][ind2]);
	      ind2 ++;
	    }
	}
    }
  padZero(outfptr, & whichbit, & curbyte);
  fclose(infptr);
  fclose(outfptr);
  return 1;
}
// if endec is 0: encode, if it is 1: decode
// encoded and decode must flip the order of the two subtrees
static ListNode * MergeListNode(ListNode * head, int endec)
{
  ListNode * second = head -> next;
  // second must not be NULL, otherwise, will not enter
  ListNode * third  = second -> next;
  // third may be NULL
  // get the tree nodes of the first two list nodes
  TreeNode * tn1 = head -> tnptr;
  TreeNode * tn2 = second -> tnptr;
  // remove the first two nodes
  free (head);
  free (second);
  head = third;
  TreeNode * mrg;
  if (endec == ENCODEMODE)
    { mrg = Tree_merge(tn1, tn2); }
  else
    { mrg = Tree_merge(tn2, tn1); }
  ListNode * ln = ListNode_create(mrg);
  if (endec == ENCODEMODE)
    { head = List_insert(head, ln, SORTED); }
  else
    { head = List_insert(head, ln, STACK); }
  return head;
}
// merge the top two list nodes until only one list node 
static TreeNode * list2Tree(ListNode * head)
{
  // merge the top two list nodes until only one list node 
  while ((head -> next) != NULL)
    {
      List_print(head); printf("-----------\n");
      head = MergeListNode(head, ENCODEMODE);
    }
  List_print(head);  
  // the linked list is no longer needed
  TreeNode * root = head -> tnptr;
  // the linked list is no longer needed
  free (head);
  return root;
}
int encode(char * infile, char * outfile)
{
  CharFreq frequencies[NUMLETTER];
  // set the array elements to zero
  bzero(frequencies, sizeof(CharFreq) * NUMLETTER);
  unsigned int numChar = countFrequency(infile, frequencies);
  if (numChar == 0) { return 0; }
  // printFrequency(frequencies);
  sortFrequency(frequencies);
  // printFrequency(frequencies);
  ListNode * head = List_build(frequencies);
  if (head == NULL) { return 0; } // the article is empty
  TreeNode * root = list2Tree(head);
  // build the code book
  // get the number of leaf nodes
  int numRow = Tree_leaf(root);
  // get the tree's height
  int numCol = Tree_height(root);
  // numCol should add 1 to accommodate the ending -1
  numCol ++;
  // create a 2D array and initialize the codes to -1
  int * * codebook = malloc(sizeof(int*) * numRow);
  int row;
  for (row = 0; row < numRow; row ++)
    {
      codebook[row] = malloc(sizeof(int) * numCol);
      int col;
      // initialize to -1
      for (col = 0; col < numCol; col ++) { codebook[row][col] = -1; }
    }
  buildCodeBook(root, codebook);
  printCodeBook(codebook, numRow);
  // mapping from ASCII to the indexes of the code book
  int mapping[NUMLETTER];
  int ind;
  for (ind = 0; ind < NUMLETTER; ind ++)
    {
      mapping[ind] = -1; // initialized to invalid index
      int ind2;
      for (ind2 = 0; ind2 < numRow; ind2 ++)
	{
	  if (codebook[ind2][0] == ind) { mapping[ind] = ind2; }
	}
    }
  for (ind = 0; ind < NUMLETTER; ind ++)
    {
      if (mapping[ind] != -1) { printf("%c:%d\n", ind, mapping[ind]); }
    }
  Tree_header(root, numChar, outfile);
  compress(infile, outfile, codebook, mapping);
  // release memory
  for (ind = 0; ind < numRow; ind ++) { free (codebook[ind]); }
  free (codebook);
  Tree_destroy(root);
  return 1;
}
static TreeNode * readHeader(FILE * infptr)
{
  int done = 0;
  unsigned char whichbit = 0;
  unsigned char curbyte  = 0;
  unsigned char onebit   = 0;
  ListNode * head = NULL;
  // decreasing to ensure the list is a stack
  while (done == 0)
    {
      readBit(infptr, & onebit, & whichbit, & curbyte);
      if (onebit == 1)
	{
	  // a leaf node, get 7 move bits
	  int bitcount;
	  unsigned char value = 0;
	  for (bitcount = 0; bitcount < 7; bitcount ++)
	    {
	      value <<= 1; // shift left by one
	      readBit(infptr, & onebit, & whichbit, & curbyte);
	      value |= onebit;
	    }
	  // push a tree node into the list
	  TreeNode * tn = TreeNode_create(value, 0); 
	  ListNode * ln = ListNode_create(tn);
	  head = List_insert(head, ln, STACK);
	}
      else
	{
	  if (head == NULL)
	    { printf("ERROR, head should not be NULL\n"); }
	  if ((head -> next) == NULL)
	    { done = 1; } // the tree has been completely built
	  else
	    { head = MergeListNode(head, DECODEMODE); }
	}
    }
  // unnecessary to read the remaining unused bits
  TreeNode * root = head -> tnptr;
  // the linked list is no longer needed
  free (head);
  return root;
}
int decode(char * infile, char * outfile)
{
  FILE * infptr = fopen(infile, "r");
  if (infptr == NULL) { return 0; }
  TreeNode * root = readHeader(infptr);
  Tree_print(root, 0);
  // read the number of characters
  unsigned int numChar = 0;
  fread(& numChar, sizeof(unsigned int), 1, infptr);
  printf("numChar = %d\n", numChar);
  // read '\n'
  unsigned char newline;
  fread(& newline, sizeof(unsigned char), 1, infptr);
  if (newline != '\n') { printf("ERROR!\n"); }
  unsigned char whichbit = 0;
  unsigned char onebit = 0;      
  unsigned char curbyte = 0;
  FILE * outfptr = fopen(outfile, "w");
  while (numChar != 0)
    {
      TreeNode * tn = root;
      while ((tn -> left) != NULL)
	{
	  // tn is not a leaf node
	  readBit(infptr, & onebit, & whichbit, & curbyte);	  
	  if (onebit == 0) { tn = tn -> left; }
	  else { tn = tn -> right; }	    
	}
      // tn is a leaf node
      printf("%c", tn -> value);
      fprintf(outfptr, "%c", tn -> value);
      numChar --;
    }
  Tree_destroy(root);
  fclose(infptr);
  fclose(outfptr);
  return 1;
}
