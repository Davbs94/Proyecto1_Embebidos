#include <stdio.h>
#include <stdlib.h>
#include "../include/gpio.h"





int main(int argc, char **argv)
{
  
 
  // Set up gpi pointer for direct register access
  setup_io();
 
  // Switch GPIO 7..11 to output mode
 
 /************************************************************************\
  * You are about to change the GPIO settings of your computer.          *
  * Mess this up and it will stop working!                               *
  * It might be a good idea to 'sync' before running this program        *
  * so at least you still have your code changes written to the SD-card! *
 \************************************************************************/
 
  // Set GPIO pins 7-11 to output

  //configure_pin(9);
  printf("ddddd\n");
  while(1){
	  printf("%d\n",get_pin(9));
	  sleep(1);
	  
  }
	  
 /*
 
  for (rep=0; rep<1100; rep++)
  {

     set_pin(9,1);
     sleep(1);
     set_pin(9,0);
     sleep(1);
  }
  
 
  return 0;
  */
 
} // main
