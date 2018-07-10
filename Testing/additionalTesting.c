#include "teletext.h"

int main(void)
{
  FILE* filePointer;
  unsigned char testceefax[LENGTH][WIDTH];
  int i=0, j=0;

  filePointer = fopen("testFile.m7", "w");

  if(filePointer == NULL){
    fprintf(stderr, "Cannot open file\n");
    exit(1);
  }

  memset(testceefax, 0, sizeof(unsigned char)*(LENGTH*WIDTH));

  testceefax[1][0] = REDG;    /*RED*/
  testceefax[1][1] = BLOCK; /*PRINTS RED BLOCKS FOR FOUR CELLS*/
  testceefax[1][2] = BLOCK;
  testceefax[1][3] = BLOCK;
  testceefax[1][4] = BLOCK;

  testceefax[1][5] = GREENG; /*GREEN GRAPHICS*/
  testceefax[1][6] = BLOCK;
  testceefax[1][7] = BLOCK;
  testceefax[1][8] = BLOCK;
  testceefax[1][9] = BLOCK;
  testceefax[1][10] = BLOCK;

  testceefax[1][11] = BLUEG; /*BLUE GRAPHICS*/
  testceefax[1][12] = BLOCK;
  testceefax[1][13] = BLOCK;
  testceefax[1][14] = BLOCK;
  testceefax[1][15] = BLOCK;

  testceefax[2][0] = RED;    /*RED - PRINTS RED TEXT*/
  testceefax[2][1] = 82; /*R*/
  testceefax[2][2] = 69; /*E*/
  testceefax[2][3] = 68; /*D*/

  testceefax[2][5] = GREEN;    /*GREEN - PRINTS GREEN TEXT*/
  testceefax[2][6] = 71; /*G*/
  testceefax[2][7] = 82; /*R*/
  testceefax[2][8] = 69; /*E*/
  testceefax[2][9] = 69; /*E*/
  testceefax[2][10] = 78; /*N*/

  testceefax[2][11] = BLUE; /*BLUE*/
  testceefax[2][12] = 66;
  testceefax[2][13] = 76;
  testceefax[2][14] = 85;
  testceefax[2][15] = 69;

  testceefax[1][16] = DOUBLE; /*Prints blue double height*/
  testceefax[1][17] = 68; /*D*/
  testceefax[1][18] = 79; /*O*/
  testceefax[1][19] = 85; /*U*/
  testceefax[1][20] = 66; /*B*/
  testceefax[1][21] = 76; /*L*/
  testceefax[1][22] = 69; /*E*/
  testceefax[2][16] = DOUBLE;
  testceefax[2][17] = 68; /*D*/
  testceefax[2][18] = 79; /*O*/
  testceefax[2][19] = 85; /*U*/
  testceefax[2][20] = 66; /*B*/
  testceefax[2][21] = 76; /*L*/
  testceefax[2][22] = 69; /*E*/


 /*Prints Green and Red double height*/
  testceefax[1][23] = GREEN;
  testceefax[1][24] = NEWBACKGROUND;
  testceefax[1][25] = RED;
  testceefax[1][26] = DOUBLE;
  testceefax[1][27] = 68; /*D*/
  testceefax[1][28] = 79; /*O*/
  testceefax[1][29] = 85; /*U*/
  testceefax[1][30] = 66; /*B*/
  testceefax[1][31] = 76; /*L*/
  testceefax[1][32] = 69; /*E*/
  testceefax[1][34] = NEWBACKGROUND; /*shows that background continues until black background*/
  testceefax[2][23] = RED;
  testceefax[2][24] = NEWBACKGROUND;
  testceefax[2][25] = GREEN;
  testceefax[2][26] = DOUBLE;
  testceefax[2][27] = 68; /*D*/
  testceefax[2][28] = 79; /*O*/
  testceefax[2][29] = 85; /*U*/
  testceefax[2][30] = 66; /*B*/
  testceefax[2][31] = 76; /*L*/
  testceefax[2][32] = 69; /*E*/
  testceefax[2][33] = BLACKBACKGROUND; /*changes colour of background*/


  /*Testing Graphics - changing colour*/
  testceefax[4][0] = CONTIGUOUS;
  testceefax[4][1] = MAGENTAG;
  testceefax[4][2] = 32;
  testceefax[4][3] = 42;
  testceefax[4][4] = SEPERATED;
  testceefax[4][5] = 44;
  testceefax[4][6] = 45;

  testceefax[4][8] = GREENG;
  testceefax[4][9] = 46;
  testceefax[4][10] = 47;
  testceefax[4][11] = 48;
  testceefax[4][12] = 49;
  testceefax[4][13] = 50;

  testceefax[4][14] = CYANG;
  testceefax[4][15] = 50;
  testceefax[4][16] = 51;
  testceefax[4][17] = 52;
  testceefax[4][18] = 53;
  testceefax[4][19] = 54;


  /*TESTING GRAPHICS - seperated*/
  testceefax[5][0] = CYANG;
  testceefax[5][1] = SEPERATED;
  testceefax[5][2] = 32;
  testceefax[5][3] = 42;
  testceefax[5][4] = 43;
  testceefax[5][5] = 44;
  testceefax[5][6] = 45;

  testceefax[5][7] = MAGENTAG;
  testceefax[5][8] = SEPERATED;
  testceefax[5][9] = 46;
  testceefax[5][10] = 47;
  testceefax[5][11] = 48;
  testceefax[5][12] = 49;
  testceefax[5][13] = 50;

  testceefax[5][14] = GREENG; /*Goes to contiguous when graphics mode is found*/
  testceefax[5][15] = 50;
  testceefax[5][16] = 51;
  testceefax[5][17] = 52;
  testceefax[5][18] = 53;
  testceefax[5][19] = 54;

  /*Single to double to single*/

  testceefax[7][10] = MAGENTA;
  testceefax[7][11] = DOUBLE;
  testceefax[7][12] = 68; /*D*/
  testceefax[7][13] = 79; /*O*/
  testceefax[7][14] = 85; /*U*/
  testceefax[7][15] = 66; /*B*/
  testceefax[7][16] = 76; /*L*/
  testceefax[7][17] = 69; /*E*/
  testceefax[8][10] = WHITE;
  testceefax[8][11] = DOUBLE;
  testceefax[8][12] = 68; /*D*/
  testceefax[8][13] = 79; /*O*/
  testceefax[8][14] = 85; /*U*/
  testceefax[8][15] = 66; /*B*/
  testceefax[8][16] = 76; /*L*/
  testceefax[8][17] = 69; /*E*/

  testceefax[7][19] = SINGLE;
  testceefax[7][20] = 68; /*D*/
  testceefax[7][21] = 79; /*O*/
  testceefax[7][22] = 85; /*U*/
  testceefax[7][23] = 66; /*B*/
  testceefax[7][24] = 76; /*L*/
  testceefax[7][25] = 69; /*E*/
  testceefax[8][18] = RED;
  testceefax[8][19] = SINGLE;
  testceefax[8][20] = 68; /*D*/
  testceefax[8][21] = 79; /*O*/
  testceefax[8][22] = 85; /*U*/
  testceefax[8][23] = 66; /*B*/
  testceefax[8][24] = 76; /*L*/
  testceefax[8][25] = 69; /*E*/

  testceefax[7][27] = DOUBLE;
  testceefax[7][28] = 68; /*D*/
  testceefax[7][29] = 79; /*O*/
  testceefax[7][30] = 85; /*U*/
  testceefax[7][31] = 66; /*B*/
  testceefax[7][32] = 76; /*L*/
  testceefax[7][33] = 69; /*E*/
  testceefax[8][26] = GREEN;
  testceefax[8][27] = DOUBLE;
  testceefax[8][28] = 68; /*D*/
  testceefax[8][29] = 79; /*O*/
  testceefax[8][30] = 85; /*U*/
  testceefax[8][31] = 66; /*B*/
  testceefax[8][32] = 76; /*L*/
  testceefax[8][33] = 69; /*E*/

  /*Background and Graphics*/
  testceefax[10][0] = NEWBACKGROUND;
  testceefax[10][1] = BLUEG;
  testceefax[10][2] = 32;
  testceefax[10][3] = 42;
  testceefax[10][4] = 43;
  testceefax[10][5] = 44;
  testceefax[10][6] = 45;

  testceefax[10][7] = NEWBACKGROUND;
  testceefax[10][8] = GREENG;
  testceefax[10][9] = 46;
  testceefax[10][10] = 47;
  testceefax[10][11] = 48;
  testceefax[10][12] = 49;
  testceefax[10][13] = 50;

  testceefax[10][14] = NEWBACKGROUND;
  testceefax[10][15] = YELLOWG;
  testceefax[10][16] = 51;
  testceefax[10][17] = 52;
  testceefax[10][18] = 53;
  testceefax[10][19] = 54;
  testceefax[10][20] = BLACKBACKGROUND;

  testceefax[11][25] = CONTIGUOUS;
  testceefax[11][26] = BLUEG;
  testceefax[11][27] = 53;
  testceefax[11][28] = 53;
  testceefax[11][29] = 53;
  testceefax[11][30] = 53;
  testceefax[11][31] = 53;
  testceefax[11][32] = 53;

  testceefax[12][0] = 35; /*Shows that the contiguous turns off on new line*/
  testceefax[12][1] = 33;
  testceefax[12][2] = 34;

  testceefax[15][15] = WHITEG; /*Proves blastthrough text works*/
  testceefax[15][16] = BLOCK;
  testceefax[15][17] = 66;
  testceefax[15][18] = BLOCK;
  testceefax[15][19] = 76;
  testceefax[15][20] = BLOCK;
  testceefax[15][21] = 65;
  testceefax[15][22] = BLOCK;
  testceefax[15][23] = 83;
  testceefax[15][24] = BLOCK;
  testceefax[15][25] = 84;
  testceefax[15][26] = BLOCK;
  testceefax[15][27] = 84;
  testceefax[15][28] = BLOCK;
  testceefax[15][29] = 72;
  testceefax[15][30] = BLOCK;
  testceefax[15][31] = 82;
  testceefax[15][32] = BLOCK;
  testceefax[15][33] = 79;
  testceefax[15][34] = BLOCK;
  testceefax[15][35] = 85;
  testceefax[15][36] = BLOCK;
  testceefax[15][37] = 71;
  testceefax[15][38] = BLOCK;
  testceefax[15][39] = 72;
  testceefax[16][0]  = 73;

  testceefax[19][34] = 22; /*Enables blastthrough text in graphics mode*/
  testceefax[19][35] = DOUBLE; /*D*/
  testceefax[19][36] = BLOCK; /*O*/
  testceefax[19][37] = BLOCK; /*U*/
  testceefax[19][38] = 65; /*B*/
  testceefax[19][39] = BLOCK; /*L*/
  testceefax[20][34] = 22;
  testceefax[20][35] = DOUBLE; /*D*/
  testceefax[20][36] = 39; /*O*/
  testceefax[20][37] = BLOCK; /*U*/
  testceefax[20][38] = 65; /*B*/
  testceefax[20][39] = BLOCK; /*L*/

  testceefax[16][34] = BLUEG; /*Showing held graphics doesnt work*/
  testceefax[16][35] = 85; /*D*/
  testceefax[16][36] = HOLD; /*O*/
  testceefax[16][37] = 85; /*U*/
  testceefax[16][38] = 66; /*B*/
  testceefax[16][39] = 76; /*L*/
  testceefax[17][0] = 69; /*E*/
  testceefax[17][34] = 69;
  testceefax[17][35] = 68; /*D*/
  testceefax[17][36] = 79; /*O*/
  testceefax[17][37] = 85; /*U*/
  testceefax[17][38] = 66; /*B*/
  testceefax[17][39] = 76; /*L*/
  testceefax[18][0] = 69; /*E*/
  testceefax[18][1] = RELEASE;





  for(i = 0; i < LENGTH; i++){
    for(j = 0; j < WIDTH; j++){
    fwrite(&testceefax[i][j], sizeof(unsigned char), 1, filePointer);
    }
  }
      fclose(filePointer);
  return 0;

}
