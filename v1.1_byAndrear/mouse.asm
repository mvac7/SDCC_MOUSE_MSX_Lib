; -------------------------------
; *** MOUSE SUBROUTINES ***
; * (c) Ramones 2007      *
; * adaptada a SDCC por Andrear
; -------------------------------

GTPAD   = #0x00DB
GTTRIG  = #0x00D8
initmem = #0xF87F ;0xE000
mouse   = initmem
mousex  = mouse+1
mousey  = mousex+1
mousebutton1 = mousey+1
mousebutton2 = mousebutton1+1
msxmodel     = mousebutton2+1

.area _CODE


; -------------------------------
; CHECKMOUSE
; comprueba si hay un mouse 
; conectado en alguno de los 
; puertos	
; Llamar en varias interrupciones
; -------------------------------        
_checkmouse::

				ld		a,#1
				ld		(mouse),a			
				
				ld		b,#12
				call	mousereaddir
				
				ld		a,(mousex)
				cp		#1
				ret		nz
				ld		a,(mousey)
				cp		#1
				ret		nz
				
				ld		a,#2
				ld		(mouse),a
				
				ld		b,#16
				call	mousereaddir
				ld		a,(mousex)
				cp		#1
				ret		nz
				ld		a,(mousey)
				cp		#1
				ret		nz
				xor		a
				ld		(mouse),a
				ret
				

; -----------------
; MOUSEREAD
; Lectura del raton
; -----------------

_mouseread::		
		
				xor		a
				ld		(mousex),a
				ld		(mousey),a
				ld		(mousebutton1),a
				ld		(mousebutton2),a
		
				ld		a,(mouse)
				or		a
				ret		z
				
				ld		b,#12
				cp		#1
				jr		z,mouseread0
				ld		b,#16
				
mouseread0:
				call	mousereaddir
				ld		a,(mouse)
				jp		mousereadbutton
				
				
mousereaddir:
				ld		a,b
				push	bc
				call	gtpadown			; Primera (Request)
				pop		bc
								
				inc		b
				ld		a,b
				
				push	bc
				call	gtpadown			; X
				ld		(mousex),a
				pop		bc
				inc		b
				ld		a,b
				call	gtpadown			; Y								
				ld		(mousey),a
				ret

mousereadbutton:
				push	af
				call	GTTRIG
				ld		(mousebutton1),a				
				pop		af
				inc		a
				inc		a
				call	GTTRIG
				ld		(mousebutton2),a
				ret
				
		

; ------------------------
; GTPADOWN
; Llama a gtpad bios
; o gtpadown segun sistema
; -------------------------		
		
gtpadown:
				ld		b,a
				ld		a,(msxmodel)
				or		a
				ld		a,b
				jr		z,gtpadmsx1
				jp		GTPAD
				
		
		
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
				ld     hl,#0x10ef   

				cp     #0x0c        
				jr     z,gtpadmsx1_348C    
				ld     bc,#0x40ff   
				ld     hl,#0x20df   
				cp     #0x10        
				jr     z,gtpadmsx1_348C    
				and    #0x03        
				sub    #0x02        
				ld     a,(#0xfafe)  
				ret    m          
				ld     a,(#0xfb00)  
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
				call	 gtpadmsx1_3508      
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
				ld     (#0xfb00),a  
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
				ld     (#0xfb00),a  
				pop    af         
				pop    de         
				add    a,a        
				add    a,a        
				add    a,a        
				add    a,a        
				or     b          
				neg               

gtpadmsx1_34F4: 				
				ld     (#0xfafe),a  
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