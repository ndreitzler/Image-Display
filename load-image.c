/*  Name: Nick Dreitzler
    Username: ndreitz
    CUID: C15564443
    Class: ECE 4680
    Professor: Adam Hoover
    Semester: Spring2021
    Filename: load-image.c

    Purpose: To load a grayscale (P5) or RGB (P6) image into memory
 */

#include "image.h"

PPM_image *load_image(char *filename)
{
  FILE		  *fpt;
  PPM_image *image = (PPM_image *)my_malloc(sizeof(PPM_image));
  int        type = 0; /*1 if grayscale, 3 if RGB, 0 if neither*/
  int		     i;

  /* open image for reading */
  FOPEN(fpt, filename, "r");

	/* read image image->header (simple 8-bit greyscale PPM only) */
  i = fscanf(fpt,"%s %d %d %d ", image->header, &(image->COLS), &(image->ROWS), &(image->BYTES));

  /*if grayscale: type = 1, because 1 byte per pixel
    if RGB: type = 3, because 3 bytes per pixel
    otherwise: gs = 0, invalid type
   */
  if(!strcmp(image->header,"P5"))
    type = 1;
  else if(!strcmp(image->header,"P6"))
    type = 3;

  if (i != 4  ||  image->BYTES != 255  ||  type == 0)
  {
    printf("%s is not an 8-bit PPM greyscale (P5) or RGB (P6) image\n",filename);
    FCLOSE(fpt);
    exit(0);
  }

  //total number of bytes in the image
  image->num_bytes = image->ROWS*image->COLS*type;

	/* allocate dynamic memory for image */
  image->data = (unsigned char *)my_malloc(image->num_bytes*sizeof(unsigned char));

	/* read image data from file */
  fread(image->data,1,image->num_bytes,fpt);
  FCLOSE(fpt);


  // //write image to test file
  // FOPEN(fpt, "test.ppm", "w");

  // sprintf(buff, "%s %d %d %d\n", image->header,image->COLS,image->ROWS,image->BYTES);
  // fwrite(buff, sizeof(char), strlen(buff), fpt);

  // fwrite(image->data, sizeof(unsigned char), image->num_bytes, fpt);

  // FCLOSE(fpt);

  return image;
  // FREE(image);
}

/*Purpose: to malloc the given number of bytes and verify that
  malloc succeeded.
  Input: bytes - IN the number of bytes to malloc
  Return: a void pointer to malloced data.
 */
void *my_malloc(int bytes)
{
  void *ptr = malloc(bytes);
  
  if(ptr == NULL)
  {
    printf("Unable to allocate %d bytes of memory\n", bytes);
    exit(0);
  }

  return ptr;
}

