#include <stdint.h>
#include <stdbool.h>
#include "tx_api.h"
#include "tx_port.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define STACK_SIZE 1024 
#define BYTE_POOL_SIZE 9120

UCHAR byte_pool_memory[BYTE_POOL_SIZE];

TX_THREAD thread1;
TX_THREAD thread2;
TX_THREAD thread3;

TX_BYTE_POOL byte_pool;
UINT status;

void thread_1(ULONG thread_input);
void thread_2(ULONG thread_input);
void thread_3(ULONG thread_input);

void setup(void);

int main() {
   setup();
   tx_kernel_enter();
}

void setup(void) {
  // Port N configuration
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
   while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
   GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
   GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
   
  // Port F configuration
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
   while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}
   GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, GPIO_PIN_4);
}

void tx_application_define(void *first_unused_memory) {
   CHAR *pointer = TX_NULL;
   
   status = tx_byte_pool_create(&byte_pool, "Block of memory", byte_pool_memory, BYTE_POOL_SIZE);

   status = tx_byte_allocate(&byte_pool, (VOID**)&pointer, STACK_SIZE,TX_NO_WAIT);

   status = tx_thread_create(
      &thread1,
      "thread 1",
      thread_1,
      30,
      pointer,
      STACK_SIZE,
      1,
      1,
      TX_NO_TIME_SLICE,
      TX_AUTO_START
   );
   
   status = tx_byte_allocate(&byte_pool, (VOID**)&pointer, STACK_SIZE, TX_NO_WAIT);
   
   status = tx_thread_create(
      &thread2,
      "thread 2",
      thread_2,
      30,
      pointer,
      STACK_SIZE,
      2,
      2,
      TX_NO_TIME_SLICE,
      TX_AUTO_START
   );
   
   status = tx_byte_allocate(&byte_pool, (VOID**)&pointer, STACK_SIZE, TX_NO_WAIT);

   status = tx_thread_create(
      &thread3,
      "thread 3",
      thread_3,
      30,
      pointer,
      STACK_SIZE, 
      3,
      3,
      TX_NO_TIME_SLICE,
      TX_AUTO_START
   );

   tx_block_release(pointer);

}

void thread_1(ULONG thread_input) {
   uint32_t ui32Loop = 0;
   uint32_t blink;
 
   ULONG time_before;
   ULONG time_after;
   ULONG time_lapsed ;
 
   time_before = tx_time_get();
 
   GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
   GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_4, 0x0);
 
   time_before = tx_time_get();
 
   while(ui32Loop < thread_input) {

      for(blink = 0; blink < 200000; blink++) {}

      GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);

      for(blink = 0; blink < 200000; blink++){}

      GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);

      ui32Loop++;
   }

   time_after = tx_time_get();
   time_lapsed = time_after - time_before;
}


void thread_2(ULONG thread_input) {
   uint32_t ui32Loop = 0;
   uint32_t blink;

   ULONG time_before;
   ULONG time_after;
   ULONG time_lapsed ;

   GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
   GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_4, 0x0);

   time_before = tx_time_get();

   while(ui32Loop < thread_input) {
      for(blink = 0; blink < 200000; blink++) {}
      
      GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
      
      for(blink = 0; blink < 200000; blink++) {}
      GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
      ui32Loop++;
   }

   time_after = tx_time_get();
   time_lapsed = time_after - time_before;
}


void thread_3(ULONG thread_input) {
   uint32_t ui32Loop = 0;
   uint32_t blink;
   
   ULONG time_before;
   ULONG time_after;
   ULONG time_lapsed;
   
   GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
   GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_4, 0x0);
   
   time_before = tx_time_get();
   
   while(ui32Loop < thread_input) {
      for(blink = 0; blink < 200000; blink++) {}
      
      GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_4, GPIO_PIN_4);
      
      for(blink = 0; blink < 200000; blink++) {}

      GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_4, 0x0);

      ui32Loop++;
   }

   time_after = tx_time_get();
   time_lapsed = time_after - time_before;
}