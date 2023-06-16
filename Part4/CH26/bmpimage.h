// CH26:bmpimage.h
#ifndef _BMPIMAGE_H
#define _BMPIMAGE_H
#include "bmpheader.h"
typedef struct
{
  BMP_Header header; // not a pointer
  unsigned int data_size;
  unsigned int width;
  unsigned int height;
  unsigned int bytes_per_pixel; 
  unsigned char * data; // a pointer
} BMP_Image;
#endif
