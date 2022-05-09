//BLINK PINA1 23
#define __SFR_OFFSET 0x20
#include "avr/io.h"

.global START

START:
    LDI R23, 0xFF       
    STS DDRA, R23       // OUTPUT
    LDI R23, 0x00       
    STS DDRF, R23       //INPUT
    STS TCCR1A, R23    
    RCALL BLINK      

BLINK: 
      LDI R23, 0x01     // 000001 ON
      OUT 0x02, R23     // PORTA
      LDI R22, 0x01     // 1*250
      RCALL LOOP25    
          
      LDI R23, 0x22     //100010 OFF
      OUT 0x02, R23     //PORTA
      LDI R22, 0x01     //1*250
      RCALL LOOP25                
      NOP
   
//SUB DELAY DE 250 MS 
DELAY_250:
      LDI R25, 25
LOOP_250:
      CALL DELAY
      DEC R25
      BRNE LOOP_250
      RET
    
LOOP25:
      RCALL DELAY_250
      DEC R22
      BRNE LOOP25
      RET

//DELAY OFICIAL DE 10 MS PREESCALADO A 64
//OCUPAMOS EL TIMER DE 16 BITS     
DELAY:
      LDI  R21, 0XF6
      STS  TCNT1H, R21
      LDI  R21, 0X3C        // DELAY DE 10 MS -> 63036
      STS  TCNT1L,R21
      LDI  R21, 0x03        //TIMER NORMAL CON 64 PRESC
      STS  TCCR1B, R21    
AGAIN: 
      LDS  R21, TIFR1
      SBRS  R21, 0
      RJMP  AGAIN
      CLR   R21
      STS   TCCR1B, R21
      LDI   R21,0X01
      STS   TIFR1, R21
      RET
