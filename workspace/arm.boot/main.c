#include "main.h"
#include "uart.h"
#include "isr.h"
#include "kprintf.h"

/*
 * Define ECHO_ZZZ to have a periodic reminder that this code is polling
 * the UART, actively. This means the processor is running continuously.
 * Polling is of course not the way to go, the processor should halt in
 * a low-power state and wake-up only to handle an interrupt from the UART.
 * But this would require setting up interrupts...
 */
#define ECHO_ZZZ 

/**
 * This is the C entry point, upcalled once the hardware has been setup properly
 * in assembly language, see the startup.s file.
 */


void c_entry(){
  _copy_vector();
  _irqs_setup();
  init_uart();
  init_pic();
  _irqs_enable();
  
  int i = 0;
  int count = 0;
  uart_send_string(UART0, "\nHello world!\n");
  uart_send_string(UART0, "\nQuit with \"C-a c\" and then type in \"quit\".\n");
  while (1) {
    unsigned char c;
/*#ifdef ECHO_ZZZ
    while (0 == uart_receive(UART0, &c)) {
      count++;
      if (count > 50000000) {
        uart_send_string(UART0, "\n\rZzzz....\n\r");
        count = 0;
      }
    }
#else*/
    if (0==uart_receive(UART0,&c))
    continue;
//#endif
    if (c == 13) {
      uart_send(UART0, '\r');
      uart_send(UART0, '\n');
    } else {
      uart_send(UART0, c);
    }
  }
}
