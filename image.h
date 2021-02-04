/*  Name: Nick Dreitzler
    Username: ndreitz
    CUID: C15564443
    Class: ECE 4680
    Professor: Adam Hoover
    Semester: Spring2021
    Filename: image.h
 */

//Guard
#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 80

//Macro to free allocated data and set pointer to null
#define FREE(x)                                         \
do {                                                    \
    free(x);                                            \
    x = NULL;                                           \
} while(0)

//Macro to free PPM_image struct
#define FREE_PPM(x)                                     \
do {                                                    \
    free(x->data);                                      \
    x->data = NULL;                                     \
    free(x);                                            \
    x = NULL;                                           \
} while(0)

//Macro to close file and set pointer to null
#define FCLOSE(x)                                       \
do {                                                    \
    fclose(x);                                          \
    x = NULL;                                           \
} while(0)

/*Macro to open a file and print error/exit if it fails
    Inputs:
        x - OUT file pointer
        y - IN  filename
        c - IN  mode
 */
#define FOPEN(x, y, c)                                  \
do {                                                    \
    x = fopen(y, c);                                    \
    if(x == NULL)                                       \
    {                                                   \
        printf("%s failed to open for %s\n", y, c);     \
        exit(-1);                                       \
    }                                                   \
} while(0)

typedef struct PPM_image {
    char header[BUFF_SIZE]; /*P5 if grayscale, P6 if RGB*/
    int COLS;   /*number of columns in image*/
    int ROWS;   /*number of rows in image*/
    int BYTES;  /*max size of pixel*/
    int num_bytes; /*total number of bytes in image*/
    unsigned char *data; /*image data*/
} PPM_image;

typedef struct PPM_16bit{
    int COLS;
    int ROWS;
    unsigned char *data;
} PPM_16bit;

PPM_image *load_image(char *filename);
void *my_malloc(int bytes);
PPM_16bit *convert_to_16bit_RGB(PPM_image *image);

#endif