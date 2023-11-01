#include "at91sam3x8.h"
#include "system_sam3x.h"
#include "keypad.h"
#include "calendar.h"




unsigned int col;
unsigned int row;
unsigned int value;


void keypadConfig(){

  
  *AT91C_PMC_PCER = (1<<13);

  *AT91C_PMC_PCER = (1<<14);

  //PIOC
  *AT91C_PIOC_PER = 0x3BC;
  *AT91C_PIOC_ODR = 0x3C;
  *AT91C_PIOC_PPUER =  0x3C;

  //PIOD

  *AT91C_PIOD_PER = (0x4);
  *AT91C_PIOD_OER =(0x4);
  *AT91C_PIOD_PPUDR =  (0x4);


  }



int readKeypad(void){
 
 
    value = 0;
    col =0;

     *AT91C_PIOD_CODR =(1<<2); // open the gate (Active Low)

     *AT91C_PIOC_OER = 0x380;
     *AT91C_PIOC_PPUDR =  0x380;

     *AT91C_PIOC_SODR = (1<<7)| (1<<8)|(1<<9);  // all columns as 1

    for( int i = 7; i<10; i++){
      row = 0;

        *AT91C_PIOC_CODR = (1<<i);

   for(int j =2 ;j<6;j++){

     if(((*AT91C_PIOC_PDSR & (1<<j))!=(1<<j))){
       
      value = row*3+col+1;
       
    *AT91C_PIOC_SODR= (1<<i);
      *AT91C_PIOC_ODR = 0x380;
      *AT91C_PIOC_PPUER = 0x380;
      
      return value;
     
     }
      
       if(row<3)
         row++;
            
    }

    
   *AT91C_PIOC_SODR= (1<<i);

    if(col<2)
       col++;
        }
    
  *AT91C_PIOC_ODR = 0x380;
  *AT91C_PIOC_PPUER = 0x380;
  
 

  return value;

}




