// CH27:main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
// #include "occur.h"
// #include "encode.h"
// #include "decode.h"
// #include "tree.h"
int main(int argc, char * * argv)
{
  if (argc != 5) { return EXIT_FAILURE; }
  // argv[1]: "c"- compress, "d"- decompress
  // argv[2]: input file path (including directory and file name)
  // argv[3]: output file directory (without file name)
  // argv[4]: input file name (without directory)
  int func = 0; // 0: invalid, 1: compress, 2: decompress
  if (strcmp(argv[1], "c") == 0) { func = 1; }
  if (strcmp(argv[1], "d") == 0) { func = 2; }
  if (func == 0) { return EXIT_FAILURE;}
  // The output is stored in the file with name argv[4]/argv[3].out
  // This program save progress in argv[4]/argv[3].progress
  int namelength = strlen(argv[3]) + strlen(argv[4]);
  char * outputname = malloc(sizeof(char) * (namelength + 10));
  char * progressname = malloc(sizeof(char) * (namelength + 10));
  strcpy(outputname, argv[3]);
  strcat(outputname, argv[4]);
  strcpy(progressname, outputname);
  strcat(outputname, ".out");
  strcat(progressname, ".progress");
  // FILE * pfptr = fopen(progressname, "w");
  // if (pfptr == NULL) { return EXIT_FAILURE; }
  // printf("fopen(%s)\n", progressname);
  int rtv; // return value
  if (func == 1)
    { rtv = compress(argv[2], outputname, progressname); }
  /*
  if (func == 2)
    { rtv = decompress(argv[2], outputname, progressname); }
  */
  // fclose (pfptr);
  free (outputname);
  free (progressname);
  if (rtv == 0) { return EXIT_FAILURE; }
  return EXIT_SUCCESS;
}
