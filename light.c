#include "at91sam3x8.h"
#include "system_sam3x.h"
#include "light.h"



unsigned int Aflag=0,resultval;
double val1,val2,difval;

void lightConfig(){

*AT91C_PMC_PCER = (1<<11); // PIOA
*AT91C_PMC_PCER1 = (1<<5); //ADC 37

 *AT91C_PIOA_PER = 0x18;//  PIN 59 & 60
 *AT91C_PIOA_OER = 0x18;
 *AT91C_PIOA_PPUDR =  0x18;

}



void ADC_Config(){
    
    Aflag=0;
    
 *AT91C_ADCC_MR =(*AT91C_ADCC_MR & 0xFFFF00FF) | (1<<9); //Set prescaler to 2 in ADC_MR -> ADCClock = 14MHz
  *AT91C_ADCC_CHER = 0x6;  //Enable channel 1 and 2 which represent AD6 & AD5
   *AT91C_ADCC_CR = 0x2;

    *AT91C_ADCC_SR;

    //NVIC
  NVIC_ClearPendingIRQ(ADC_IRQn);
  NVIC_SetPriority(ADC_IRQn, 1);
  NVIC_EnableIRQ(ADC_IRQn);

 *AT91C_ADCC_IER=0X6; //interrupt enable register for channel 1 , 2



}


void ADC_Handler(){



  if((*AT91C_ADCC_SR & 0x2) == 0x2) // check if we have value in chanel 1

   val1= (*AT91C_ADCC_CDR1& 0xFFF) * (3.3/4095); // read value


  if ((*AT91C_ADCC_SR & 0x4) == 0x4) // check if we have value in chanel 2

    val2= (*AT91C_ADCC_CDR2 & 0xFFF) * (3.3/4095); 

   Aflag=1;

  *AT91C_ADCC_IDR=0X6;



}



int differntvalue(){

 difval = val2-val1;

if(difval >-0.20 &&difval <= -0.18)

  resultval = 0;

if(difval >-0.18 && difval <= -0.16)

  resultval =10;

if(difval >-0.16 && difval <= -0.14)

  resultval =20;

if(difval >-0.14 && difval <= -0.12)

  resultval =30;

if(difval >-0.12 && difval <= -0.10)

  resultval =40;

if(difval >-0.10 && difval <= -0.08)

  resultval =50;

if(difval >-0.08 && difval <= -0.06)

  resultval =60;

if(difval >-0.06 && difval <= -0.04)

  resultval =70;

if(difval >-0.04 && difval <= 0.02)

  resultval =80;

if(difval >0.02 && difval <= 0.00)

  resultval =90;

if(difval >0.00 && difval <= 0.02)

  resultval =100;

if(difval >0.02 && difval <= 0.04)

  resultval =110;

if(difval >0.04 && difval <= 0.06)

  resultval =120;

if(difval >0.06 &&difval <= 0.08)

  resultval =130;

if(difval >0.08 && difval <= 0.10)

  resultval =140;

if(difval >0.10 && difval <= 0.12)

  resultval =150;

if(difval >0.12&& difval <= 0.14)

  resultval =160;

if(difval >0.14 && difval <= 0.16)

  resultval =170;

if(difval >0.16 && difval <= 0.18){

  resultval =180;}

return resultval;

}


