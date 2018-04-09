// 
// GPIO Raspberry pi Model 3 Library
// Allows the user to control the GPIO's
// of the rasp pi
// Last Modification: 21/03/2018 15:00
//

#define BCM2708_PERI_BASE        0x3F000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) // GPIO controller 
 
 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "../include/gpio.h"
 
#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)
 
int  mem_fd;
void *gpio_map;
volatile unsigned *gpio;
 
 
// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
#define GPIO_SET *(gpio+7)
#define GPIO_CLR *(gpio+10)
#define GET_GPIO(g) (*(gpio+13)&(1<<g))
#define GPIO_PULL *(gpio+37)
#define GPIO_PULLCLK0 *(gpio+38)
 


//Configure Pin for I/O
void configure_pin(int pin)
{
	INP_GPIO(pin);
	OUT_GPIO(pin);
}
 
//Set the digital value of a pin
void set_pin(int pin,int value)
{
	if (value==1){
		GPIO_SET = 1<<pin;
	}
	if (value==0){
		GPIO_CLR = 1<<pin;
	}
}

//Return a 1 or 0, depends on the input of the pin
int get_pin(int pin)
{   
  if (GET_GPIO(pin)){ 
    return 0;
  }
  else{
    return 1;
  }
}
 

// Set up a memory regions to access GPIO
void setup_io()
{
   //open /dev/mem
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }
   gpio_map = mmap(
      NULL,             
      BLOCK_SIZE,       
      PROT_READ|PROT_WRITE,
      MAP_SHARED,       
      mem_fd,           
      GPIO_BASE         
   );
   close(mem_fd);
   if (gpio_map == MAP_FAILED) {
      printf("map error %d\n", (int)gpio_map);
      exit(-1);
   }
   gpio = (volatile unsigned *)gpio_map;
 
 
}


 
 

