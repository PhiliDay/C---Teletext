#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <wand/magick_wand.h>
#include <ctype.h>

struct indiCol{
  int red;
  int blue;
  int green;
};

int main(int argc,char **argv)
{

char *rgbVal;
int imageWidth, imageHeight, x, y, i, length;
char character;
char image[i];
int cnt;
int comma;

MagickBooleanType status;
MagickWand *magick_wand;

PixelWand *colour = NewPixelWand();
MagickBooleanType array[LENGTH][WIDTH];
memset(array, 0, sizeof(MagickBooleanType)*1000);


/*Reading the image*/
  MagickWandGenesis();
  magick_wand=NewMagickWand();
status = MagickReadImage(magick_wand,"red.png");

if(status != MagickTrue){
  printf("Image hasnt been red\n");
}

/*Get width and height */
imageWidth = MagickGetImageWidth(magick_wand);
imageHeight = MagickGetImageHeight(magick_wand);

/*Resizing the image*/
while(imageWidth > LENGTH && imageHeight > WIDTH){
    imageWidth = imageWidth/HALF;
    imageHeight = imageHeight/HALF;
  }

/*Retrieving the RGB values*/
for(x = 0; x < imageHeight; x++){
  for(y = 0; y < imageWidth; y++){
    array[x][y] = MagickGetImagePixelColor(magick_wand, x, y, colour);
    rgbVal = PixelGetColorAsString(colour);
    printf("%s", rgbVal);
  }
}

/*    Write the image then destroy it  */

  status=MagickWriteImages(magick_wand,argv[2],MagickTrue);

  magick_wand=DestroyMagickWand(magick_wand);
  MagickWandTerminus();
  return(0);
}
