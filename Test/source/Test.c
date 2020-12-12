/* =============================================================================
   Test
   v1.1 (12 December 2020)
   Description:
     Test mouse MSX SDCC Library
      
   History of versions:
     - v1 (29/Ene/2016)
============================================================================= */

#include "../include/newTypes.h"
#include "../include/textmode.h"
#include "../include/mouse.h"
#include "../include/msxSystemVars.h"
#include "../include/msxBIOS.h"



#define  HALT __asm halt __endasm   //wait for the next interrupt




void test();


byte inkey();
void WAIT(uint cicles);



// constants  ------------------------------------------------------------------


const char text01[] = "Test mouse MSX SDCC Lib";
const char text02[] = "v1.1 (12/Dec/2020)";



// Functions -------------------------------------------------------------------


//
void main(void)
{
    
  test();

  

//EXIT MSXDOS
/*  screen(0);
    
__asm
 	ld b,4(ix)
	ld c,#0x62
	call 5 
__endasm;*/
//end EXIT

  return;
}



/* =============================================================================
One character input (waiting)
============================================================================= */
byte inkey() __naked
{
__asm   
   call CHGET
   ld   L,A
   ret
__endasm;
}




// Generates a pause in the execution of n interruptions.
// PAL: 50=1second. ; NTSC: 60=1second. 
void WAIT(uint cicles)
{
  uint i;
  for(i=0;i<cicles;i++) HALT;
  return;
}



// TEST ###############################################################
void test()
{
  char A=0;
  signed int posX=0;
  signed int posY=0;
  //signed char moux,mouy;
  
  COLOR(LIGHT_GREEN,DARK_GREEN,DARK_GREEN);      
  SCREEN0();
  WIDTH(40);
  
  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02);
  
  LOCATE(0,4);
  PRINT(">Test CheckMouse()=");
  
  A = CheckMouse();
  PrintNumber(A);
  
  LOCATE(1,6);
  switch (A) 
  {
    case 0:
      PRINT("Not found a mouse"); 
      break;
    case 1:
      PRINT("OK. Found at A port");  
      break;
    case 2:
      PRINT("OK. Found at B port");  
      break;
    default:
      PRINT("This Isn't Ok. :("); //Here is something that is not working.  
  }
  
  
  if (A>0)
  {
    LOCATE(0,9);
    PRINT(">Test MouseRead()");
    LOCATE(5,11);
    PRINT("Mouse X:");
    LOCATE(5,13);
    PRINT("Mouse Y:");
    
    while(1)
    {
      HALT;
      
      MouseRead();
      
      posX=posX+Mouse_X;
      posY=posY+Mouse_Y;
      
      if (posX<0) posX=0;
      if (posX>255) posX=255;
      if (posY<0) posY=0;
      if (posY>191) posY=191;      
      
      LOCATE(13,11);
      PrintFNumber(posX,32,3);      
      
      LOCATE(13,13);
      PrintFNumber(posY,32,3);
       
    }
  }
  
  
  
  LOCATE(10,18);
  PRINT("Press a key to exit");
  inkey();
 
  return;
}




