/*  Name: Nick Dreitzler
    Username: ndreitz
    CUID: C15564443
    Class: ECE 4680
    Professor: Adam Hoover
    Semester: Spring2021
    Filename: lab1-X.c

    Purpose: To display a grayscale (P5) or RGB (P6) image using X
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "image.h"

int main(int argc, char **argv)
{
	Display				*Monitor;
	Window				ImageWindow;
	GC					ImageGC;
	XWindowAttributes	Atts;
	XImage				*Picture;
	PPM_image 			*image;
	PPM_16bit			*image_16bit;

	if(argc != 2)
	{
		printf("Usage:  ./lab1-X [PPM filename]\n");
		exit(0);
	}

	image = load_image(argv[1]);

	image_16bit = convert_to_16bit_RGB(image);

	Monitor=XOpenDisplay(NULL);
	if (Monitor == NULL)
	{
		printf("Unable to open graphics display\n");
		exit(0);
	}

	ImageWindow = XCreateSimpleWindow(Monitor,RootWindow(Monitor,0),
		50,10,						/* x,y on screen */
		image_16bit->COLS, image_16bit->ROWS,	/* width, height */
		2, 							/* border width */
		BlackPixel(Monitor,0),
		WhitePixel(Monitor,0));

	ImageGC = XCreateGC(Monitor,ImageWindow,0,NULL);

	XMapWindow(Monitor,ImageWindow);
	XFlush(Monitor);
	while(1)
	{
		XGetWindowAttributes(Monitor,ImageWindow,&Atts);
		if (Atts.map_state == IsViewable /* 2 */)
			break;
	}

	Picture = XCreateImage(Monitor,DefaultVisual(Monitor,0),
			DefaultDepth(Monitor,0),
			ZPixmap,	/* format */
			0,		/* offset */
			(char *)image_16bit->data,/* the data */
			image_16bit->COLS,image_16bit->ROWS,	/* size of the image data */
			16,		/* pixel quantum (8, 16 or 32) */
			0);		/* bytes per line (0 causes compute) */

	printf("test\n");

	XPutImage(Monitor,ImageWindow,ImageGC,Picture,
			0,0,0,0,	/* src x,y and dest x,y offsets */
			image_16bit->COLS,image_16bit->ROWS);	/* size of the image data */

	XFlush(Monitor);
	sleep(3);
	//getchar();
	XCloseDisplay(Monitor);

	
	FREE_PPM(image);
	FREE_PPM(image_16bit);
}

