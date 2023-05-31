// CH10:palindrome.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main(int argc, char * * argv)
{
  if (argc != 2) { return EXIT_FAILURE; }
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL) { return EXIT_FAILURE; }
  int rtv = fseek(fptr, 0, SEEK_END); // go to the end of the file
  long length = ftell(fptr); // find the length of the file
  long pos = 0;
  bool palindrome = true;
  while ((palindrome == true) && (pos < (length / 2)))
    {
      fseek(fptr, pos, SEEK_SET); // go to the beginning
      int ch1 = fgetc(fptr);
      fseek(fptr, - (pos + 1), SEEK_END); // go to the end
      int ch2 = fgetc(fptr);
      if (ch1 != ch2) { palindrome = false; }
      pos ++;
    }
  if (palindrome == false) { printf("not palindrome\n"); }
  else { printf("palindrome\n"); }
  fclose (fptr);
  return EXIT_SUCCESS;
}
