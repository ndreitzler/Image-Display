/*  Name: Nick Dreitzler
    Username: ndreitz
    CUID: C15564443
    Class: ECE 4680
    Professor: Adam Hoover
    Semester: Spring2021
    Filename: convert-to-16bit-RGB.c

    Purpose: To convert a 8-bit grayscale (P5) or 24-bit RGB (P6) image to 16-bit RGB
 */

#include "image.h"

#define RED     0
#define GREEN   1
#define BLUE    2

void convert_8bit_GS_to_16bit_RGB(PPM_image *image, PPM_16bit *new_image);
void convert_24bit_RGB_to_16bit_RGB(PPM_image *image, PPM_16bit *new_image);

/*Purpose: convert 8-bit grayscale PPM image and 24-bit RGB PPM image to
    a 16-bit RGB image in order to display it on a 16-bit display
  Return: pointer to PPM_16bit structure which contains 16-bit RGB image
 */
PPM_16bit *convert_to_16bit_RGB(
    PPM_image *image /*IN - pointer to PPM image, must be 8-bit grayscale or 24-bit RGB*/)
{
    PPM_16bit *new_image = (PPM_16bit *)my_malloc(sizeof(PPM_16bit));
    new_image->COLS = image->COLS;
    new_image->ROWS = image->ROWS;

    //printf("test %d\n", new_image->COLS * new_image->ROWS * 2);

    //There are COLS*ROWS total pixels and 2 bytes per pixel
    new_image->data = (unsigned char *)my_malloc(new_image->COLS * new_image->ROWS * 2);

    //printf("%d\n",new_image->COLS * new_image->ROWS * 2);

    if(!strcmp(image->header,"P5"))
        convert_8bit_GS_to_16bit_RGB(image, new_image);
    else if(!strcmp(image->header,"P6"))
        convert_24bit_RGB_to_16bit_RGB(image, new_image);
    else
    {
        printf("Error: Image header is not P5 (8-bit grayscale) nor P6 (24-bit RGB)\n");
        exit(0);
    }

    //printf("%x\n%x%x\n",image->data[2],new_image->data[4],new_image->data[5]);

    //printf("%d\n",r * c * 2);

    return new_image;
}

/*Purpose: convert 8-bit grayscale PPM image data to a 16-bit RGB image data
 */
void convert_8bit_GS_to_16bit_RGB(
    PPM_image *image,   /*IN  - pointer to 8-bit grayscale PPM image*/
    PPM_16bit *new_image/*OUT - pointer to 16-bit RGB PPM image*/)
{
    int r,c;
    //int index, new_index;
    unsigned char *new_display, display;

    //Loop through pixel data and convert 24-bit values to 16-bit values
    //8 bit grayscale consist of only 8 bits
    //16 bit RGB consists of 5 red bits, 6 green bits, and 5 blue bits
    for(r = 0; r < new_image->ROWS; r++)
    {
       for(c = 0; c < new_image->COLS; c++)
        {
            // index = (r*new_image->COLS+c)*2;
            // new_index = r*image->COLS + c;

            new_display = &(new_image->data[(r*new_image->COLS+c)*2]);
            display = image->data[r*image->COLS + c];

            new_display[0]  = (display & 0xF8) 
                            + (display >> 5);
            new_display[1]  = ((display & 0x1C) << 3)
                            + (display >> 3);

            // printf("%x\n", image->data[r*new_image->COLS + c]);

            // printf("\n");
            // printf("before: %u\n", image->data[0]);
            // printf("after : %u %u\n", new_image->data[0], new_image->data[1]);
        }
    }
}

/*Purpose: convert 24-bit RGB PPM image data to a 16-bit RGB image data
 */
void convert_24bit_RGB_to_16bit_RGB(
    PPM_image *image,   /*IN  - pointer to 24-bit RGB PPM image*/
    PPM_16bit *new_image/*OUT - pointer to 16-bit RGB PPM image*/)
{
    int r,c;
    //int index, new_index;
    unsigned char *new_display, *display;

    //Loop through pixel data and convert 24-bit values to 16-bit values
    //24 bit RGB consist of 8 red bits, 8 green bits, and 8 blue bits
    //16 bit RGB consists of 5 red bits, 6 green bits, and 5 blue bits
    for(r = 0; r < new_image->ROWS; r++)
    {
       for(c = 0; c < new_image->COLS; c++)
        {
            //index = (r*new_image->COLS+c)*2;
            //new_index = (r*image->COLS + c)*3;

            new_display = &(new_image->data[(r*new_image->COLS+c)*2]);
            display = &(image->data[(r*image->COLS + c)*3]);

            new_display[0]  = (display[RED] & 0xF8) 
                            + (display[GREEN] >> 5);
            new_display[1]  = ((display[GREEN] & 0x1C) << 3)
                            + (display[BLUE] >> 3);

        }
    }
}



            // for(i = 7; i >= 0; i--)
            //     printf("%u", ((image->data[r*new_image->COLS + c]) & (1 << i)) >> i);
            // printf("\n");

            // for(i = 7; i >= 0; i--)
            //     printf("%u", ((new_image->data[(r*new_image->COLS+c)*2+c]) & (1 << i)) >> i);

            // for(i = 7; i >= 0; i--)   
            //     printf("%u", ((new_image->data[(r*new_image->COLS+c)*2+c+1]) & (1 << i)) >> i);