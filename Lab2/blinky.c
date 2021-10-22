#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

//****************************************************************************
//
// System clock rate in Hz.
//
//****************************************************************************
uint32_t g_ui32SysClock;

int flag = 0;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

void sysTickHandler(void) {
  flag++;
}

int setupSystick(void) {
  
  // Disables the SysTick counter.
  SysTickDisable();
  //uint32_t ui32Value;
  
  //Sets the period of the SysTick counter.
  SysTickPeriodSet(120000);
  
  SysTickIntRegister(sysTickHandler);
  SysTickIntEnable();
  
  // Enables the SysTick counter
  SysTickEnable();
  
  //ui32Value = SysTickValueGet;
  return 0;
}

int main(void) {
  
   // Run from the PLL at 120 MHz.
   g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_240), 120000000);
   
    // Enable the GPIO port that is used for the on-board LED.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    // Check if the peripheral access is enabled.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)) {}

    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);
    //GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
    
    setupSystick();
    
    volatile int buttonFlag = 0;
    
    printf("Start!\n");
    
    while(1) {
      
      if(flag == 1000) {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        
        
      } else if(flag >= 1000) {
        buttonFlag = GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0);
        
        if(buttonFlag == 1){
          GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
          int tempo = flag - 1000;
          printf("Tempo: %d ms\n", tempo);
          return 0;
        
        } else if(flag == 4000) {
          GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
          printf("Tempo de 3s esgotado!\n");
          return 0;
        }
        
      }
    }
}
