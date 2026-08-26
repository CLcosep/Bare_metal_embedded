CC 			= arm-none-eabi-gcc
OBJCCOPY 	= arm-none-eabi-objcopy

CFLAGS	= -mcpu=cortex-m3 -mthumb -O0 -g -ffreestanding -nostdlib -Wall
LDFLAGS = -T linker.ld -nostdlib

all: firmware.bin

firmware.elf: startup.c main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

firmware.bin: firmware.elf
	$(OBJCCOPY) -O binary $< $@

flash: firmware.bin
	st-flash --reset write firmware.bin 0x8000000


clean:
	rm -f firmware.elf firmware.bin

.PHONY: all flash clean