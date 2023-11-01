#include "at91sam3x8.h"
#include "system_sam3x.h"
#include "display.h"
#include "keypad.h"
#include "stdlib.h"



void displayConfig(){

  *AT91C_PMC_PCER = (1<<13);
  *AT91C_PMC_PCER = (1<<14);

  *AT91C_PIOC_PER = 0xFF3FC;
  *AT91C_PIOD_PER = (1<<0);

  *AT91C_PIOC_OER = 0xFF000;
  *AT91C_PIOC_PPUDR =  0xFF000;

  *AT91C_PIOD_OER =(1<<0);
  *AT91C_PIOD_PPUDR = (1<<0);
  
  
 *AT91C_PIOC_CODR = (1<<18);// set large font 
  *AT91C_PIOC_CODR = (1<<19); // display mode signal RV=0 normal.

}


void Delay(int Value){

 for(int i=0; i<Value ;i++)
  asm("nop");
}



unsigned char Read_Status_Display(void){

unsigned char temp=0;

//Make databus as input // pin 2,3,4,5,6,7,8,9
  *AT91C_PIOC_ODR = 0x3FC;

  //Set dir(direction) as input (74chip, input = 1)

  *AT91C_PIOC_SODR = (1<<13);   //Set bit one


   //Clear / enable OE output (74chip, enable = 0)

  *AT91C_PIOC_CODR = (1<<12); //Set bit zero



  //Set C/D

  *AT91C_PIOC_SODR = (1<<14); //Set bit one


  //Clear chip select display

  *AT91C_PIOC_CODR = (1<<15); //Set bit zero



   //Clear read display
  *AT91C_PIOC_CODR = (1<<16); //Set bit zero



   Delay(10);//Make Delay

    //Read databus and save it in temp
  temp =
    (*AT91C_PIOC_PDSR & 0x3FC)>>2; // pin 2,3,4,5,6,7,8,9


   //Set chip select display
  *AT91C_PIOC_SODR = (1<<15); //Set bit one

  //Set read display
  *AT91C_PIOC_SODR = (1<<16); //Set bit one

  //Disable OE output (74chip)
  *AT91C_PIOC_SODR = (1<<12); //Set bit one

  //Set dir as output (74chip) Output = 0
  *AT91C_PIOC_CODR = (1<<13);   //Set bit zero
  return temp;







}


void Write_Command_2_Display(unsigned char Command){


 //Wait until Read_Status__Display returns an OK.
  while((Read_Status_Display() & 0x3) != 0x3);

  //Clear databus // pin 2,3,4,5,6,7,8,9
   *AT91C_PIOC_OER = 0x3FC;
  *AT91C_PIOC_CODR = 0x3FC;

   //Set Data to databus
  *AT91C_PIOC_SODR = (Command << 2);

  //Set dir as output (74chip)  //Set bit zero
  *AT91C_PIOC_CODR = (1<<13);

   //Enable output OE (74chip)   //Set bit zero
  *AT91C_PIOC_CODR = (1<<12);

  //Set databus as output // pin 2,3,4,5,6,7,8,9
  *AT91C_PIOC_OER = 0x3FC;

  //Set C/D signal High (1 = Command)
  *AT91C_PIOC_SODR = (1<<14);

  //Clear chip select display
  *AT91C_PIOC_CODR = (1<<15); //Set bit zero

  //Clear write display
  *AT91C_PIOC_CODR = (1<<17); //Set bit zero

  Delay(10);

  //Set chip enable display
  *AT91C_PIOC_SODR = (1<<15); //Set bit one

  //Set write display
  *AT91C_PIOC_SODR = (1<<17); //Set bit zero

  //Disable OE output (74chip)
  *AT91C_PIOC_SODR = (1<<12); //Set bit one

   //Make databus as input
  *AT91C_PIOC_ODR = 0x3FC;

}






void Write_Data_2_Display(unsigned char Data){


 //Wait until Read_Status__Display returns an OK.
  while((Read_Status_Display() & 0x3) != 0x3);   //STA0 and STA1 is both 1


  //Clear databus // pin 2,3,4,5,6,7,8,9
  *AT91C_PIOC_OER = 0x3FC;
  *AT91C_PIOC_CODR = 0x3FC;

   //Set Data to databus
  *AT91C_PIOC_SODR = (Data << 2);

  //Set dir as output (74chip)  //Set bit zero
  *AT91C_PIOC_CODR = (1<<13);

   //Enable output OE (74chip)   //Set bit zero
  *AT91C_PIOC_CODR = (1<<12);

  //Set databus as output // pin 2,3,4,5,6,7,8,9
  *AT91C_PIOC_OER = 0x3FC;

  //Set C/D signal High (0 = Data)
  *AT91C_PIOC_CODR = (1<<14);

  //Clear chip select display
  *AT91C_PIOC_CODR = (1<<15); //Set bit zero

  //Clear write display
   *AT91C_PIOC_CODR = (1<<17); //Set bit zero

  Delay(10);

  //Set chip enable display
  *AT91C_PIOC_SODR = (1<<15); //Set bit one

  //Set write display
  *AT91C_PIOC_SODR = (1<<17); //Set bit zero

  //Disable OE output (74chip)

  *AT91C_PIOC_SODR = (1<<12); //Set bit one

   //Make databus as input
  *AT91C_PIOC_ODR = 0x3FC;

}



void Init_Display(void){
  //Clear Reset display

  *AT91C_PIOD_CODR = (1<<0); //Set bit zero

  Delay(10);//Make Delay

  //Set reset display

  *AT91C_PIOD_SODR = (1<<0); //Set bit one

  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x40); //Set text home address
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x40);
  Write_Command_2_Display(0x42); //Set Graphic home address
  Write_Data_2_Display(0x1e);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x41); //Set text area
  Write_Data_2_Display(0x1e);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x43); //Set graphics area
  Write_Command_2_Display(0x80); //Text mode
  Write_Command_2_Display(0x94); //Text on graphic off
}



void print(unsigned char key ){


  switch(value){

  case 10: key = 0x0A;

  break;

  case 11: key = 0x10;
  break;


  case 12 : key = 0x03;
  break;


  default:

    key = (unsigned char) 0x10 + value;
    break;


     }

     Write_Data_2_Display(key);
     Write_Command_2_Display(0xC4);


}


void ClearDisplay(){

  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x24);


 for(int i = 0; i<= 480; i++){
   Write_Data_2_Display(0x00);
 Write_Command_2_Display(0xC0);
  }

 Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x24);
} 











