#include "isr.h"
#include "uart.h"
#include "kprintf.h"
/*
void irq_handler(void) {
    for (;;) {
        int irq = pic_next_raised_irq();switch (irq) {
            case -1:pic_enable_all_irqs();return;
            //case UART0_IRQ:uart0_isr();
            break;
        }
    }
    uart_send_string(UART0,"OK");
}
*/
void isr() {
    kprintf("ISR OK\n");
}