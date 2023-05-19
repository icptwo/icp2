// CH27:main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "occur.h"
#include "encode.h"
#include "decode.h"
#include "tree.h"
int main(int argc, char * * argv)
{
  if (argc != 5) { return EXIT_FAILURE; }
  // argv[1]: "c"- compress, "d"- decompress
  // argv[2]: input file path
  // argv[3]: input file name
  // argv[4]: output path
  // The output is stored in the file with name argv[2].out
  // This program generates intermediate files:
  // argv[3].tree- post-order of the compression tree
  // argv[3].book- code book
  // argv[3].text- text mode of the file
  int func = 0; // 0: invalid, 1: compress, 2: decompress
  if (strcmp(argv[1], "c") == 0) { func = 1; }
  if (strcmp(argv[1], "d") == 0) { func = 2; }
  if (func == 0) { return EXIT_FAILURE;}
  int namelength = strlen(argv[3]) + strlen(argv[4]);
  char * treename = malloc(sizeof(char) * (namelength + 10));
  char * bookname = malloc(sizeof(char) * (namelength + 10));
  char * textname = malloc(sizeof(char) * (namelength + 10));
  strcpy(treename, argv[4]);
  strcat(treename, argv[3]);
  strcpy(bookname, treename);
  strcpy(textname, treename);
  strcat(treename, ".tree");
  strcat(bookname, ".book");
  strcat(textname, ".text");
  printf("%s %s %s\n", treename, bookname, textname);
 #ifdef TEST_MAIN
  if (func == 1)
    {
      CharOccur chararr[NUMCHAR];
      int total = countOccur(argv[2], chararr);
      if (total == 0) // nothing in the file
	{ return EXIT_FAILURE; } 
      TreeNode * tree = buildTree(chararr);
      if (tree == NULL)
	{ return EXIT_FAILURE; }
      char * codeBook[NUMCHAR] = {NULL};
      buildCodeBook(tree, codeBook);
      printCodeBook(codeBook);
      encode(argv[2], argv[2], tree, codeBook);
      destroyCodeBook(codeBook);
    }
  if (func == 2)
    {
      FILE * infptr = fopen(argv[2], "r");
      if (infptr == NULL) { return EXIT_FAILURE; }
      TreeNode * tree = buildTree(infptr);
      if (tree == NULL) { return EXIT_FAILURE; }
      int length;
      if (fread(& length, sizeof(int), 1, infptr) != 1)
	{ printf("wrong format\n"); }
      // printf("length = %d\n", length);
      unsigned char newline;
      fread(& newline, sizeof(unsigned char), 1, infptr);
      if (newline != '\n') 
	{ printf("wrong format\n"); }
      decode(infptr, argv[2], length, tree);
      fclose (infptr);
    }      
  Tree_destroy(tree);
#endif  
  return EXIT_SUCCESS;
}
