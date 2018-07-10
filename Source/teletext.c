#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "teletext.h"

int main(int argc, char *argv[])
{
  Code ceefax[LENGTH][WIDTH];

  if (argc != ARGS){
    fprintf(stderr,"Not enough arguments!\n");
    exit(1);
  }

  readMainFile(argv[1], ceefax);
  createCeefax(ceefax);
  printCeefax(ceefax);

  return 0;
}

void readMainFile(char *file,Code ceefax[LENGTH][WIDTH])
{
  FILE* filePointer;
  size_t counter;
  int i, j;

  filePointer = fopen(file, "rb");

  if(filePointer == NULL){
    fprintf(stderr, "Cannot open file\n");
    exit(1);
  }

  for(i = 0; i < LENGTH; i++){
    for(j = 0; j < WIDTH; j++){
      counter = fread(&ceefax[i][j].teletext, sizeof(unsigned char), 1, filePointer);
        if(counter != 1){
          fprintf(stderr, "Unable to read file\n");
          exit(1);
        }

        /*Sets all the control codes to less than 128*/
         if(ceefax[i][j].teletext > ASCII){
            ceefax[i][j].teletext -= ASCII;
         }
    }
  }
  fclose(filePointer);
}

void readFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *file)
{
   FILE* filePointer;
   size_t counter;

   filePointer = fopen(file, "rb");

   if(!filePointer){
      fprintf(stderr, "Can't open Font file %s\n", file);
      exit(1);
    }

   counter = fread(fontdata, sizeof(fntrow), FNTCHARS*FNTHEIGHT, filePointer);

   if(counter != FNTCHARS*FNTHEIGHT){
      fprintf(stderr, "Can't read Font file\n");
      exit(1);
   }
   fclose(filePointer);
}

void printCeefax(Code ceefax[LENGTH][WIDTH])
{
  int i, j;
  int holdFlag = 0;
  Code holdValue;

  SDL_Simplewin sw;
  fntrow fontdata[FNTCHARS][FNTHEIGHT];

  mySDLInit(&sw);
  readFont(fontdata, "m7fixed.fnt");

   for(i=0;i<LENGTH;i++){
      for(j=0;j<WIDTH;j++){

        /*Creates flags for the hold mode*/
       if(ceefax[i][j].teletext == HOLD){
          holdFlag = ON;
        }
        if(ceefax[i][j].teletext == RELEASE){
          holdFlag = OFF;
        }

        if(holdFlag == ON){
          /*Use GOTOCOLOUR to get the correct colours*/
          holdValue.background = ceefax[i][j].teletext-GOTOCOLOUR;
        }

        /*Implementing the height functions*/
        changingTopBottom(ceefax, i, j);
        drawHeight(ceefax, i, j, holdFlag, fontdata, &sw, holdValue);

        /*Draws the graphics - in Held and Release Mode*/
        if(ceefax[i][j].Graphics == Graphics1){
          /*Make sure the graphics does not print for the blast through codes*/
          if(ceefax[i][j].teletext < BEGINBLAST
             || ceefax[i][j].teletext >= ENDBLAST){
                if(holdFlag == ON){
                   DrawRect(&sw, holdValue, j * SCREENW, i * SCREENH);
                }
                else if(holdFlag == OFF){
                  ceefax[i][j] = makeGraphics(ceefax[i][j], ceefax[i][j].teletext);
                  DrawRect(&sw, ceefax[i][j], j * SCREENW, i * SCREENH);
                }
         }
       }
     }
     Neill_SDL_UpdateScreen(&sw);
     SDL_Delay(DELAY);
   }
   while(!sw.finished){
      Neill_SDL_Events(&sw);
   }
   SDL_DestroyWindow(sw.win);
   SDL_Quit();
}

void createCeefax(Code ceefax[LENGTH][WIDTH])
{
   int i, j;
   Code before;

   for(i=0;i<LENGTH;i++){
      for(j=0;j<WIDTH;j++){
         ceefax[i][j] = initializeSixels(ceefax[i][j]);

      /*Making the default line settings */
      if(j == 0){
         ceefax[i][j] = newLine(ceefax[i][j], &before);
      }
      /*Updates different modes*/
      ceefax[i][j] = currentCode(ceefax[i][j], &before);
      }
   }
}

Code initializeSixels(Code c)
{
  c.sixel.botl = OFF;
  c.sixel.botr = OFF;
  c.sixel.topl = OFF;
  c.sixel.topr = OFF;
  c.sixel.midl = OFF;
  c.sixel.midr = OFF;

  return c;
}

Code newLine(Code c, Code *before)
{
  /*Creating default settings for a new line*/
   before->background = c.background = BLACK;
   before->foreground = c.foreground = WHITE;
   before->Height = c.Height = Single;
   before->Graphics = c.Graphics = Alphanumeric;
   before->Type = c.Type = Contiguous;
   before->Held = c.Held = Unheld;

   printf("\n");
   return c;
}

Code currentCode(Code c, Code *before)
{
  c.Held = before->Held;
  c.Graphics = before->Graphics;
  c.Height = before->Height;
  c.Type = before->Type;

  /*Updating the different modes*/
  c = changeForeground(c, &before->foreground);
  c = changeBackground(c, &before->background, before->foreground);
  c = changeHeight(c, before);
  c = changeGraphics(c, before);
  c = changeType(c, before);

  return c;
}

void pickColour(SDL_Simplewin *sw, int colour)
{
  /*CON = 255 (full colour), COFF = 0 (no colour)*/
   switch (colour) {
      case RED:                    /* R   G  B */
         Neill_SDL_SetDrawColour(sw, CON, COFF, COFF);
         break;
      case GREEN:
         Neill_SDL_SetDrawColour(sw, COFF, CON, COFF);
         break;
      case YELLOW:
         Neill_SDL_SetDrawColour(sw, CON, CON, COFF);
         break;
      case BLUE:
         Neill_SDL_SetDrawColour(sw, COFF, COFF, CON);
         break;
      case MAGENTA:
         Neill_SDL_SetDrawColour(sw, CON, COFF, CON);
         break;
      case CYAN:
         Neill_SDL_SetDrawColour(sw, COFF, CON, CON);
         break;
      case WHITE:
         Neill_SDL_SetDrawColour(sw, CON, CON, CON);
         break;
      case BLACK:
         Neill_SDL_SetDrawColour(sw, COFF, COFF, COFF);
         break;
   }
}

void myDrawBackground(SDL_Simplewin *sw, int colour, int x, int y, int mult)
{
  int i, j;

  /*Depending on double or single height, *mult is used to determine the FNTHEIGHT*/
   for(i=0;i<FNTHEIGHT*mult;i++){
      for(j=0;j<FNTWIDTH*2;j++){
         pickColour(sw, colour);
         SDL_RenderDrawPoint(sw->renderer, (x + j), (y + i));
      }
   }
}

void myDrawForeground(SDL_Simplewin *sw, Code c, int x, int j, int y, int i, int mult)
{
  pickColour(sw, c.foreground);

  SDL_RenderDrawPoint(sw->renderer, x + j, y + (i*mult+1));
  SDL_RenderDrawPoint(sw->renderer, x + j, y + (i*mult));
}

void myDrawChar(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], Code c, int ox, int oy, int mult)
{
   int x, y;

   myDrawBackground(sw, c.background, ox, oy, mult);

   for(x = 0; x < FNTHEIGHT; x++){
      for(y = 0; y < FNTWIDTH; y++){
         if(fontdata[(c.teletext-FNT1STCHAR)][x] >> (FNTWIDTH - 1 - y) & 1){
            if(c.Graphics == Graphics1){
               /*Set all graphics to a space where graphics should be!*/
               if(c.teletext <= BEGINBLAST || c.teletext >= ENDBLAST){
                  c.teletext = SPACE;
               }
               else{
                  /*Print the blastthrough text*/
                myDrawForeground(sw, c, ox, y, oy, x, mult);
               }
            }
            /*Draw the foreground only if in alphanumeric mode*/
            if(c.Graphics == Alphanumeric){
               myDrawForeground(sw, c, ox, y, oy, x, mult);
            }
         }
      }
   }
}

void myDrawTop(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], Code c, int ox, int oy, int mult)
{
  int x, y;

   myDrawBackground(sw, c.background, ox, oy, mult);

   /*Divide the character in half*/

   for(x = 0; x < FNTHEIGHT/HALF; x++){
      for(y = 0; y < FNTWIDTH; y++){
          if(fontdata[(c.teletext-FNT1STCHAR)][x] >> (FNTWIDTH - 1 - y) & 1){
           myDrawForeground(sw, c, ox, y, oy, x, mult);
         }
      }
  }
}

void drawBottom(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], Code c, int ox, int oy, int mult)
{
 int x, y, bottomHeight = FNTHEIGHT;

   myDrawBackground(sw, c.background, ox, oy, mult);
   /*Bottom is similar to drawing top but you need to move the characters to the top half of the line*/
   bottomHeight /= HALF; /*Divide the FNTHEIGHT by 2*/
   x = bottomHeight; /*Reshuffle the x axis to draw higher on line*/
   bottomHeight += x;
   oy -= FNTHEIGHT;

   for(; x < bottomHeight; x++){
      for(y = 0; y < FNTWIDTH; y++){
         if(fontdata[(c.teletext-FNT1STCHAR)][x] >> (FNTWIDTH - 1 - y) & 1){
            myDrawForeground(sw, c, ox, y, oy, x, mult);
         }
      }
   }
}


/*SIXEL FUNCTIONS*/
void createSixel(SDL_Simplewin *sw, int x, int y, int colour, int type)
{
   SDL_Rect rectangle;
   int rectanglewidthw = WIDTHSIZE, rectanglewidthh = HEIGHTSIZE;

  /*Seperated mode - make a smaller pixel*/
   if(type == Seperated){
      rectanglewidthw = rectanglewidthw-SMALLERPIXEL;
      rectanglewidthh = rectanglewidthh-SMALLERPIXEL;
   }

  /*Making the sixels using SDL_Rect */
  rectangle.x = x;
  rectangle.y = y;
  rectangle.w = rectanglewidthw;
  rectangle.h = rectanglewidthh;

  /*Pick the colour for the specific pixel*/

  pickColour(sw, colour);
  SDL_RenderFillRect(sw->renderer, &rectangle);

}

void DrawRect(SDL_Simplewin *sw, Code c, int x, int y)
{
  /*If the sixel is on, draw the sixel - depending on position needed, the x and y locations
  are set to the specific place to be draw in the cell*/

  if(c.sixel.botr == LIT){
    createSixel(sw, x + WIDTHSIZE, y + (2*HEIGHTSIZE), c.foreground, c.Type);
  }
  if(c.sixel.botl == LIT){
    createSixel(sw, x, y + (2*HEIGHTSIZE), c.foreground, c.Type);
  }
  if(c.sixel.midr == LIT){
    createSixel(sw, x + WIDTHSIZE, y + HEIGHTSIZE, c.foreground, c.Type);
  }
  if(c.sixel.midl == LIT){
    createSixel(sw, x, y + HEIGHTSIZE, c.foreground, c.Type);
  }
  if(c.sixel.topr == LIT){
    createSixel(sw, x + WIDTHSIZE, y, c.foreground, c.Type);
  }
  if(c.sixel.topl == LIT){
    createSixel(sw, x, y, c.foreground, c.Type);
  }
}

Code makeGraphics(Code c, int code)
{
   int teletext = code - BASE;

   /*The code recieved is divided by the required value to turn it on
   - any remainder is used to determine the rest of the lit sixels*/

   c.sixel.botr = teletext /BOTR;
      teletext = teletext % BOTR;
   c.sixel.botl = teletext / BOTL;
      teletext = teletext % BOTL;
   c.sixel.midr = teletext / MIDR;
      teletext = teletext % MIDR;
   c.sixel.midl = teletext / MIDL;
      teletext = teletext % MIDL;
   c.sixel.topr = teletext / TOPR;
      teletext = teletext % TOPR;
   c.sixel.topl = teletext / TOPL;
      teletext = teletext % TOPL;

   return c;
}

/*UPDATE MODE - setting the previous mode and current mode*/
void changingTopBottom(Code ceefax[LENGTH][WIDTH], int i, int j)
{
   if(ceefax[i][j].Height == ON){
      if(ceefax[i][j].Height  == ON && ceefax[i-1][j].Height == ON){

   /*If the character above is double height, only draw the bottom,
   every time else draw the top*/
         ceefax[i][j].topBottom = BOTTOM;
      }
      else{
         ceefax[i][j].topBottom = TOP;
      }
  }
}

void drawHeight(Code ceefax[LENGTH][WIDTH], int i, int j, int holdFlag, fntrow fontdata[FNTCHARS][FNTHEIGHT], SDL_Simplewin *sw, Code holdValue)
{

  /*Draws the top or the bottom */
  if(ceefax[i][j].topBottom == BOTTOM){
    drawBottom(sw, fontdata, ceefax[i][j], j * SCREENH, i * SCREENW, STRETCH);
  }
  if(ceefax[i][j].topBottom == TOP){
    myDrawTop(sw, fontdata, ceefax[i][j], j * SCREENH, i * SCREENW, STRETCH);
  }
  if(ceefax[i][j].Height == OFF){
      if(holdFlag == ON){
      /*Draws the previous character*/
         myDrawChar(sw, fontdata, holdValue, j * SCREENH, i * SCREENW, NORMAL);
      }
         else{
            /*Draws normal characters*/
            myDrawChar(sw, fontdata, ceefax[i][j], j * SCREENH, i * SCREENW, NORMAL);
         }
      }
}

Code changeType(Code c, Code *before)
{
  if(c.teletext == CONTIGUOUS){
    before->Type = c.Type = Contiguous;
  }
  else if(c.teletext == SEPERATED){
    before->Graphics = c.Graphics = Graphics1;
    before->Type = c.Type = Seperated;
  }

  return c;
}

Code changeGraphics(Code c, Code *before)
{
  if(c.teletext >= REDG && c.teletext <= WHITEG){
    before->Graphics = c.Graphics = Graphics1;
    /*Need to set to contiguous mode for default*/
    before->Type = c.Type = Contiguous;
  }

  if(c.teletext >= RED && c.teletext <= WHITE){
    before->Graphics = c.Graphics = Alphanumeric;
  }

  return c;
}

Code changeHeight(Code c, Code *before)
{
  if(c.teletext == SINGLE){
    before->Height = c.Height = Single;
  }
  if (c.teletext == DOUBLE){
     before->Height = c.Height = Double;
  }
  return c;
}


Code changeForeground(Code c, int *beforeFore)
{
   if(c.teletext >= RED && c.teletext <= WHITE){
      c.foreground = c.teletext;
   }
   else if(c.teletext >= REDG && c.teletext <= WHITEG){
   /*Minus the distance from graphics colour to text colour so that
   it is the correct type of colour*/
      c.foreground = c.teletext - GOTOCOLOUR;
   }
   else{
      /*Keep the previous foreground*/
      c.foreground = *beforeFore;
   }

   /*Set the colour for the next cell to use*/
   *beforeFore = c.foreground;

   return c;
}

Code changeBackground(Code c , int *beforeB, int beforeFore)
{
   if(c.teletext == BLACKBACKGROUND){
      c.background = BLACK;
   }
   else if (c.teletext == NEWBACKGROUND){
   /*Change to the previous foreground*/
      c.background = beforeFore;
   }
   else{
   /*else continue to keep the previous background*/
      c.background = *beforeB;
   }
   /*Set the colour for the next cell to use*/
   *beforeB = c.background;

   /*Takes away control code from screen*/
   if(c.teletext <= SPACE){
      c.foreground = c.background;
   }
   return c;
}

Code changeSeperated(Code c, Code *before)
{
   if(c.teletext == SEPERATED){
      before->Graphics = c.Graphics = Graphics;
      before->Type = c.Type = Seperated;
   }
   return c;
}

/*NEILLS FUNCTIONS*/
void mySDLInit(SDL_Simplewin *sw)
{
    sw->finished = 0;
    assert(sw->finished == 0);

   sw->win= SDL_CreateWindow("Teletext",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          WWIDTH, WHEIGHT,
                          SDL_WINDOW_SHOWN);
   if(sw->win == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Window:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   sw->renderer = SDL_CreateRenderer(sw->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

  SDL_SetRenderDrawBlendMode(sw->renderer,SDL_BLENDMODE_BLEND);
  sw->display = SDL_CreateTexture(sw->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WWIDTH, WHEIGHT);


  SDL_SetRenderTarget(sw->renderer, sw->display);


  SDL_SetRenderDrawColor(sw->renderer, COFF, COFF, COFF, CON);
  SDL_RenderClear(sw->renderer);
}

void Neill_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b)
{
   SDL_SetRenderDrawColor(sw->renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

void Neill_SDL_UpdateScreen(SDL_Simplewin *sw)
{
   SDL_SetRenderTarget(sw->renderer, NULL);
   SDL_RenderCopy(sw->renderer, sw->display, NULL, NULL);
   SDL_RenderPresent(sw->renderer);
   SDL_SetRenderTarget(sw->renderer, sw->display);
}

void Neill_SDL_Events(SDL_Simplewin *sw)
{
   SDL_Event event;
   while(SDL_PollEvent(&event))
   {
       switch (event.type){
          case SDL_QUIT:
          case SDL_MOUSEBUTTONDOWN:
             sw->finished = 1;
       }
    }
}
