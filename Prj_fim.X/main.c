#include <pic18f4520.h>
#include "config.h"
#include "bits.h"
#include "lcd.h"
#include "adc.h"
#include "keypad.h"
#include "ssd.h"
#include "io.h"
#include "pwm.h"

void main(void) {
 unsigned long int cont=0;
 unsigned int s, tecla, i;
 int v, volume,dis;
 volatile unsigned int j;
 
 TRISD=0x00;
 PORTD=0x00;
 
 s=1;
 lcdInit();
 kpInit();
 adcInit();
 pwmInit();
 
    
 for(;;){
     
     i=0;
     dis=0;
     volume=v;
     
    digitalWrite(DISP_1_PIN,LOW);
    digitalWrite(DISP_2_PIN,LOW);
    digitalWrite(DISP_3_PIN,LOW);
    digitalWrite(DISP_4_PIN,LOW);
    
     lcdPosition(0,0);
     lcdString("Selecionado: ");
     lcdNumber(s);
     lcdPosition(1,0);
     lcdString("volume: ");
     if(volume!=100)
     lcdNumber(volume);
     else
         lcdString("100");
     kpDebounce();
     PORTD=s;

if (kpRead() != tecla){
 tecla = kpRead();
 
     if(bitTst(tecla,5)){
         lcdCommand(0x01);
       while(i!=100)  {
           
        PORTD=0;   
       
        dis++;
        kpDebounce();
        
        if(dis==125){
        lcdPosition(0,0);
        lcdString("Escolha o efeito:");
        lcdPosition(1,7);
        lcdNumber(s);
        kpDebounce();
        dis=151;
        }
        
        if(dis==276){
            lcdCommand(0x01);
            lcdPosition(0,0);
            lcdString("Escolha o efeito:");
            dis=0;
        }
            
        
        
      if (kpRead() != tecla){
      tecla = kpRead();
      
 
     if (bitTst(tecla, 0)) 
         s++;
 
         if(s>15)
             s=1;
 
     if (bitTst(tecla, 2)) 
         s-=1;

        if(s<1)
             s=15;
     
     if(bitTst(tecla, 5)){
         i=100;
      lcdCommand(0x01);}
 

     } 
    }}
 if(bitTst(tecla,7)){
     ssdInit();
     lcdCommand(0x01);
     lcdString("     Volume");
    
       while(i!=100)  {
    
     v=adcRead(0)*0.098039;
     ssdDigit(((v/1)%10),3);
     ssdDigit(((v/10)%10),2);
     ssdDigit(((v/100)%10),1);
     ssdDigit(((v/1000)%10),0);
     
     
     digitalWrite(DISP_1_PIN,LOW);
     digitalWrite(DISP_2_PIN,LOW);
     digitalWrite(DISP_3_PIN,LOW);
     digitalWrite(DISP_4_PIN,LOW);
        
     dis++;
     
       if(dis==40){
       lcdCommand(0x01);
       dis=41;
       ssdUpdate();
       for(j=0;j<1000;j++);
       } 
       if(dis==81){
       lcdString("     Volume");
       dis=0;
       ssdUpdate();
       for(j=0;j<1000;j++);
       } 
    
   
     
     kpDebounce();
     if (kpRead() != tecla){
            tecla = kpRead();
            
       if(bitTst(tecla,7)){
       i=100;
       lcdCommand(0x01);
       }}
            
        ssdUpdate(); 
        for(j=0;j<1000;j++);
 
        
       }
     
 } 
}

 }
}