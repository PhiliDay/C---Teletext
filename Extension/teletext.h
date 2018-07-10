#include <math.h>
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ARGS 2
#define LENGTH 25
#define WIDTH 40
#define BEGINBLAST 63
#define ENDBLAST 96
#define SCREENW 18
#define SCREENH 18
#define ON 1
#define OFF 0
#define WWIDTH 750
#define WHEIGHT 600
#define ASCII 128
#define GOTOCOLOUR 16
#define SINGLE 12
#define DOUBLE 13
#define BLACKBACKGROUND 28
#define NEWBACKGROUND 29
#define SPACE 32
#define ESCAPE 2
#define SEPERATED 26
#define CONTIGUOUS 25
#define HOLD 30
#define RELEASE 31
#define BASE 32
#define BLOCK 127
#define DELAY 5
#define HALF 2


/*Colours*/
#define BLACK 28
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7
#define REDG 17
#define GREENG 18
#define YELLOWG 19
#define BLUEG 20
#define MAGENTAG 21
#define CYANG 22
#define WHITEG 23
#define GRAPHICS2 25
#define CON 255
#define COFF 0

/*Sixel*/
#define LIT 1
#define HEIGHTSIZE SCREENH/3
#define WIDTHSIZE SCREENW/2
#define SMALLERPIXEL 2
#define BOTR 64
#define BOTL 16
#define MIDR 8
#define MIDL 4
#define TOPR 2
#define TOPL 1

/* Font stuff */
typedef unsigned short fntrow;
#define FNTWIDTH 16
#define FNTHEIGHT 18
#define FNTCHARS 96
#define FNT1STCHAR 32

/*Double Height*/
#define TOP 1
#define BOTTOM 2
#define STRETCH 2
#define NORMAL 1



enum graphics {Alphanumeric, Graphics1} Graphics;
enum type {Contiguous, Seperated} Type;
enum height {Single, Double} Height;
enum held {Unheld, Hold} Held;

struct rect {
   int topl;
   int topr;
   int midl;
   int midr;
   int botl;
   int botr;
};
typedef struct rect Rect;


struct code{
unsigned char teletext;
int Graphics;
int foreground;
int background;
int Type;
int Height;
int doubleHeight;
int Held;
int Unheld;
int recent;
int topBottom;
int previous;

Rect sixel;

};
typedef struct code Code;

struct SDL_Simplewin {
  SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
   SDL_Texture *display;
};
typedef struct SDL_Simplewin SDL_Simplewin;

void readMainFile(char *file,Code ceefax[LENGTH][WIDTH]);
void readFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *file);
void printCeefax(Code ceefax[LENGTH][WIDTH]);
void createCeefax(Code ceefax[LENGTH][WIDTH]);
Code currentCode(Code c, Code *before);
void pickColour(SDL_Simplewin *sw, int colour );
Code newLine(Code c, Code *before);

void myDrawBackground(SDL_Simplewin *sw, int colour, int x, int y, int mult);
void myDrawForeground(SDL_Simplewin *sw, Code c, int x, int j, int y, int i, int mult);
void myDrawChar(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], Code c, int ox, int oy, int mult);
void drawBottom(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], Code c, int ox, int oy, int mult);
void myDrawTop(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], Code c, int ox, int oy, int mult);

Code checkALL(Code c, Code *before);
Code changeType(Code c, Code *previous);
Code changeGraphics(Code c, Code *previous);
Code changeHeight(Code c, Code *previous);
Code changeForeground(Code c, int *previousFore);
Code changeBackground(Code c, int *previousB, int previousFore);
Code changeHeld(Code c, Code *before);

void mySDLInit(SDL_Simplewin *sw);
void Neill_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b);
void Neill_SDL_UpdateScreen(SDL_Simplewin *sw);
void Neill_SDL_Events(SDL_Simplewin *sw);

void changingTopBottom(Code ceefax[LENGTH][WIDTH], int i, int j);
void drawHeight(Code ceefax[LENGTH][WIDTH], int i, int j, int holdFlag, fntrow fontdata[FNTCHARS][FNTHEIGHT], SDL_Simplewin *sw, Code holdValue);
void letsDoGraphics(Code ceefax[LENGTH][WIDTH], int i, int j, int holdFlag, SDL_Simplewin *sw, Code *holdValue);
void selectingHeightMode(Code ceefax[LENGTH][WIDTH], int i, int j);
void DrawRect(SDL_Simplewin *sw, Code c, int x, int y);
Code makeGraphics(Code old, int code);
void createSixel(SDL_Simplewin *sw, int x, int y, int colour, int type);
Code initializeSixels(Code c);
