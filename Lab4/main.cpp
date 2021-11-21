#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

uint32_t SysClock;

void UARTSendString(const uint8_t *Buffer, uint32_t len) {
    while(len--) {
      UARTCharPutNonBlocking(UART0_BASE, *Buffer++);
    }
}

void UARTHandler(void) {
    uint32_t status;
    volatile int32_t ch;

    status = UARTIntStatus(UART0_BASE, true);   
    UARTIntClear(UART0_BASE, status);
    
    while(UARTCharsAvail(UART0_BASE)) {
      ch = UARTCharGetNonBlocking(UART0_BASE);
      if((ch > 64) && (ch < 91)) {
          ch = ch + 32;
      }else{
        if((ch > 96) && (ch < 123)) {
            ch = ch - 32;
        }  
      }
        UARTCharPutNonBlocking(UART0_BASE, ch); // Escreve na UART
    }
    ch = 0;
}

void setup() {
  
    SysClock = SysCtlClockFreqSet(
      (SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240),
      120000000
    );
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    
    IntMasterEnable();
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    
    UARTConfigSetExpClk(
      UART0_BASE, 
      SysClock, 
      115200, 
      (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)
    );
    
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
}

int main(void) {
    setup();
    UARTSendString((uint8_t *)"Text: ", 6);
    while(1){}
}
