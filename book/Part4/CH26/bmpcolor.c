// CH26:bmpcolor.c
#include "bmpfunc.h"
void BMP_color(BMP_Image *img, int clr) // clr: 0- blue, 1- green, 2- red
// selected color is kept, the other two colors are set to zero
{
  int pxl;
  for (pxl = clr; pxl < (img -> data_size); pxl ++)
    {
      // set the other color components to zero
      if ((pxl % 3) != clr) { img -> data[pxl] = 0; }
    }
}
