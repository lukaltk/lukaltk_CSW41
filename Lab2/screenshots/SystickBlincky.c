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
  SysTickPeriodSet(12000000);
  
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

    // Check if the peripheral access is enabled.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}

    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    
    setupSystick();
    
    while(1) {
      
      if(flag == 30) {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
      }
      
      if(flag == 60) {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        flag = 0;
      }
      
    }
    
}
