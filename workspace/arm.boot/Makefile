
QEMU=qemu-system-arm

TOOLCHAIN=arm-none-eabi

ASFLAGS= -mcpu=arm926ej-s -g 
CFLAGS= -c -mcpu=arm926ej-s -g -nostdlib
LDFLAGS= -T kernel.ld 

MACHINE=versatilepb
MACHINE=versatileab

MEMORY=1M

# Notice that we link with our own linker script: test.ld
all: startup.o main.o exception.o uart.o isr.o kprintf.o
	$(TOOLCHAIN)-ld $(LDFLAGS) startup.o exception.o main.o uart.o isr.o kprintf.o -o kernel.elf
	$(TOOLCHAIN)-objcopy -O binary kernel.elf kernel.bin

clean: 
	rm -f startup.o main.o exception.o uart.o isr.o kprintf.o test.o kernel.elf

startup.o: startup.s
	$(TOOLCHAIN)-as $(ASFLAGS) startup.s -o startup.o

exception.o: exception.s
	$(TOOLCHAIN)-as $(ASFLAGS) exception.s -o exception.o

main.o: main.c main.h uart.h isr.h
	$(TOOLCHAIN)-gcc $(CFLAGS) main.c -o main.o

uart.o: uart.c uart.h
	$(TOOLCHAIN)-gcc $(CFLAGS) uart.c -o uart.o

isr.o: isr.c isr.h kprintf.h
	$(TOOLCHAIN)-gcc $(CFLAGS) isr.c -o isr.o

kprintf.o: kprintf.c kprintf.h
	$(TOOLCHAIN)-gcc $(CFLAGS) kprintf.c -o kprintf.o

run: all
	$(QEMU) -M $(MACHINE) -m $(MEMORY) -nographic -kernel kernel.bin -serial mon:stdio

debug: all
	$(QEMU) -M $(MACHINE) -m $(MEMORY) -nographic -kernel kernel.bin -serial mon:stdio -gdb tcp::1234 -S

kill:
	pkill qemu-system-arm

