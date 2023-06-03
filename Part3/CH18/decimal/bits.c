// CH18:decimal/bits.c
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
int main ( int argc , char * * argv )
{
  unsigned char a = 129;    // decimal 129, hexadecimal 0X81
  unsigned char b = 0XF0;   // decimal 240
  // a = 1000 0001
  // b = 1111 0000
  unsigned char c = a & b;  
  // c = 1000 0000
  printf("%d, %X\n", c, c); // decimal 128, hexadecimal 80 
  unsigned char d = a | b;  
  // d = 1111 0001
  printf("%d, %X\n", d, d); // decimal 241, hexadecomal F1
  unsigned char e = d << 3; 
  // e = 1000 1000
  printf("%d, %X\n", e, e); // decimal 136, hexadecimal 88
  unsigned char f = d >> 2; 
  // f = 0011 1100
  printf("%d, %X\n", f, f); // decimal 60, hexadecomal 3C
  return EXIT_SUCCESS ;
}
