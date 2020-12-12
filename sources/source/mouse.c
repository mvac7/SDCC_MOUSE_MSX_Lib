/* -----------------------------------------------------------------------------
 Mouse MSX SDCC Library (fR3eL Project)
 version: 1.4 (11/12/2020) 
 Authors: first version by Ramones
          adapted to SDCC by Andrear
          new versions by mvac7
          
 History of versions:
   v1.0 (2007) by Ramones
   v1.1 (2011) by Andrear
   v1.2 (08/08/2012) - Commented button control code. Use the STRIG function   
                       from the SDCC JOYSTICK Library
                     - Commented the code that calls the GTPAD function of the
                       BIOS, so that it works in MSX-DOS.
   v1.3 (24/01/2016) - The CheckMouse function performs the complete check and 
                       returns the resulting value.
   v1.4 (11/12/2020) - Converted to C language. Coordinates are passed to C 
                       variables instead of fixed positions in memory.
----------------------------------------------------------------------------- */

#include "../include/mouse.h"
#include "../include/msxSystemVars.h"
#include "../include/msxBIOS.h"


#define XSAVE 0xFAFE  //Light pen X coordinate read from the device
#define YSAVE 0xFB00  //Light pen Y coordinate read from the device


char Mouse_port;
signed char Mouse_X;
signed char Mouse_Y;

//char Mouse_button1;  mousebutton1;
//char Mouse_button2;   mousebutton2;



/* -----------------------------------------------------------------------------
 CheckMouse
 
 Description:
    Check if there is a mouse connected to any of the ports.	

 Input    : -- 
 Output   : [char] Mouse Port
----------------------------------------------------------------------------- */
char CheckMouse(void) __naked
{
__asm       
    push  IX
       
    ld    B,#60
CHECKBCL1:
    push  BC
        
    ;check port A
    ld		A,#1
    ld		(_Mouse_port),A			
    
    ld		B,#12
    call	mousereaddir
    
    ld		A,(_Mouse_X)
    cp		#1
    jr		NZ,checkBie
    
    ld		A,(_Mouse_Y)
    cp		#1
    jr		NZ,checkBie
    
    ;check port B
    ld		A,#2
    ld		(_Mouse_port),A
    
    ld		B,#16
    call	mousereaddir
    ld		A,(_Mouse_X)
    cp		#1
    jr		NZ,checkBie
    
    ld		A,(_Mouse_Y)
    cp		#1
    jr		NZ,checkBie
    
    ; not found a mouse
    pop   BC
    
    halt
    djnz  CHECKBCL1
    				
    xor		A
    ld		(_Mouse_port),A
    jr    checkBue2

checkBie:
    pop   BC

checkBue2:        
    ld    A,(_Mouse_port)  				
    ld    L,A
    				
    pop   IX
    
    ret
  
__endasm;
}
				


/* -----------------------------------------------------------------------------
 MouseRead
 
 Description:
    Mouse reading.

 Input    : -- 
 Output   : --
----------------------------------------------------------------------------- */
void MouseRead(void) __naked
{		
__asm		
    xor		a
    ld		(_Mouse_X),a
    ld		(_Mouse_Y),a
    
;	ld		(mousebutton1),a
;	ld		(mousebutton2),a
    
    ld		a,(_Mouse_port)
    or		a
    ret		z
    
    ld		b,#12
    cp		#1
    jr		z,mousereaddir
    ld		b,#16
				
;mouseread0:
    ;call	mousereaddir
    ;ld		a,(_Mouse_port)
    ;jp		mousereadbutton
				
				
mousereaddir:
    ld		a,b
    push	bc
    call	gtpadown			; Primera (Request)
    pop		bc
    				
    inc		b
    ld		a,b    
    push	bc
    call	gtpadown			; X
    ld		(_Mouse_X),a
    pop		bc
    
    inc		b
    ld		a,b
    call	gtpadown			; Y								
    ld		(_Mouse_Y),a
    
    ret

;mousereadbutton:
;				push	af
;				call	GTTRIG
;				ld		(mousebutton1),a				
;				pop		af
;				inc		a
;				inc		a
;				call	GTTRIG
;				ld		(mousebutton2),a
;				ret


				
; ------------------------
; GTPADOWN
; Llama a GTPAD BIOS
; o gtpadown segun sistema
; -------------------------		

; the gtapadmsx1 routine is used in all cases so that it works both in ROM 
; applications and in MSX-DOS.		

gtpadown:
;    ld		b,a
;    ld		a,(msxmodel)
;    or		a
;    ld		a,b
;    jr		z,gtpadmsx1
;    jp		GTPAD		
		
    
    
; ------------------------
; GTPADMSX1
; Rutina GTPAD con SOLO
; Raton para MSX1
; (que no contiene en BIOS)
; A: 12,13 14 para port 1
; A: 16,17,18 para port 2
; -------------------------

gtpadmsx1:
    ld		b,a
    cp		#12
    ld		a,#0xFF
    ret		c
    ld		a,b
    				
    ld		e,#0x0f      
    ld 		bc,#0x00bf   
    ld      hl,#0x10ef   
    
    cp     #0x0c        
    jr     z,gtpadmsx1_348C    
    ld     bc,#0x40ff   
    ld     hl,#0x20df   
    cp     #0x10        
    jr     z,gtpadmsx1_348C    
    and    #0x03        
    sub    #0x02        
    ld     a,(#XSAVE)  
    ret    m          
    ld     a,(#YSAVE)  
    ret    z          
    xor    a          
    ret               

gtpadmsx1_348C: 				
    di                
    call   gtpadmsx1_3502    
    call   gtpadmsx1_351D     
    push   af         
    call   gtpadmsx1_3508      
    call   gtpadmsx1_3514      
    push   af         
    call   gtpadmsx1_3502      
    call   gtpadmsx1_351A     
    push   af         
    call   gtpadmsx1_3508      
    call   gtpadmsx1_351A     
    push   af         
    call   gtpadmsx1_3502      
    call   gtpadmsx1_351A      
    push   af         
    call   gtpadmsx1_3508      
    call   gtpadmsx1_3514      
    push   af         
    call   gtpadmsx1_3502      
    call   gtpadmsx1_352D      
    call   gtpadmsx1_3508      
    call   gtpadmsx1_352D     
    call   gtpadmsx1_3502      
    ei                
    pop    af         
    pop    hl         
    pop    de         
    pop    bc         
    xor    #0x08        
    sub    #0x02        
    cp     #0x0d        
    jr     c,gtpadmsx1_34E0  
    pop    af         
    call   gtpadmsx1_34FA      
    ld     (#YSAVE),a  
    pop    af         
    call   gtpadmsx1_34FA      
    jr     gtpadmsx1_34F4     


gtpadmsx1_34E0:                
    ld     a,d        
    add    a,a        
    add    a,a        
    add    a,a        
    add    a,a        
    or     h          
    neg               
    ld     (#YSAVE),a  
    pop    af         
    pop    de         
    add    a,a        
    add    a,a        
    add    a,a        
    add    a,a        
    or     b          
    neg               

gtpadmsx1_34F4: 				
    ld     (#XSAVE),a  
    ld     a,#0xff      
    ret               

gtpadmsx1_34FA: 				
    xor    #0x08        
    bit    3,a        
    ret    z          
    or     #0xf0        
    ret           
   
gtpadmsx1_3502: 			
    call   gtpadmsx1_3525     
    and    l          
    jr     gtpadmsx1_350C      
				
gtpadmsx1_3508:					
    call   gtpadmsx1_3525      
    or     h          

gtpadmsx1_350C:                  
    push   af         
    ld     a,e        
    out    (#0xa0),a    
    pop    af         
    out    (#0xa1),a    
    ret               
				
gtpadmsx1_3514: 				
    call   gtpadmsx1_352D      
    call   gtpadmsx1_352D      

gtpadmsx1_351A: 				
    call   gtpadmsx1_352D     

gtpadmsx1_351D: 				 
    ld     a,#0x0e      
    call   gtpadmsx1_3526      
    and    #0x0f        
    ret               

gtpadmsx1_3525:                 
    ld     a,e        

gtpadmsx1_3526:                
    out    (#0xa0),a    
    in     a,(#0xa2)    
    and    c          
    or     b          
    ret               

gtpadmsx1_352D:                  
    ex     (sp),hl    
    ex     (sp),hl    
    ex     (sp),hl    
    ex     (sp),hl    
    ret

__endasm;
}