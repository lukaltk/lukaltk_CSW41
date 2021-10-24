#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

int flag = 0; // milisseconds
int portJflag = 0;
int startFlag = 0;

void SysTickIntHandler(void){
  flag++;
}

void portJHandler(void) { 
  portJflag = 1;
}

void setClock(void) {
  SysCtlClockFreqSet(
    (
      SYSCTL_XTAL_25MHZ |
      SYSCTL_OSC_MAIN | 
      SYSCTL_USE_PLL | 
      SYSCTL_CFG_VCO_240
    ), 120000000);
}

void setupSystick(void) {
  SysTickDisable();
  // The clock is 120MHz
  // Configure the SysTick counter.
  // Every 1000 flag makes 1 second
  SysTickPeriodSet(120000);
  // Pointer to a interruption
  SysTickIntRegister(SysTickIntHandler);
  // Enable the SysTick counter.
  SysTickIntEnable();
  SysTickEnable();
}

void setupGPIO(void) {
  
  //--------------------------------port J--------------------------------------
  
  // Enable clock on port J
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
  
  // Wait until the port is ready to use
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)){}
  
  // Disable the interrupt of pin 0
  GPIOIntDisable(GPIO_PORTJ_AHB_BASE,GPIO_PIN_0);
  
  // Register a function to call
  GPIOIntRegister(GPIO_PORTJ_AHB_BASE, portJHandler);
  
  //Configure: PortJ | Pin 0 | Strength 2 mA | Weak pull-up enabled
  GPIOPadConfigSet(
    GPIO_PORTJ_AHB_BASE,
    GPIO_PIN_0,
    GPIO_STRENGTH_2MA,
    GPIO_PIN_TYPE_STD_WPU
  );
  
  //Define the pin as input
  GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_1);
  
  // Make pin 0 rising edge triggered interrupts.
  GPIOIntTypeSet(GPIO_PORTJ_AHB_BASE, GPIO_PIN_0, GPIO_LOW_LEVEL);
  
  // Enable the pin interrupts.
  GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_PIN_0);
  
  //----------------------------------Port N------------------------------------
  
  // Enable clock on port N
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
  
  // Wait until the port is ready to use
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
  
  //Configure port as output
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
  
  //Start turned off
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
}

int main(void) {
  
  setClock();
  setupSystick();
  setupGPIO();
  
  while(1) {
    
    if((flag == 1000) && (startFlag == 0)) {
      printf("Start!\n");
      GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 1);
      flag = 0;
      startFlag = 1;
    }
    
    if(flag == 3000) {
      
      GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
      printf("Tempo de 3s esgotado!\n");
      flag = 0;
      return 0;
      
    } else if (portJflag == 1) {
      
      GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
      SysTickDisable();
      GPIOIntDisable(GPIO_PORTJ_AHB_BASE,GPIO_PIN_0);
      printf("Tempo: %i ms\n", flag);
      portJflag = 0;
      return 0;
      
    }
  }
}