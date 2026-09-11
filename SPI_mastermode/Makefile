include ../common.mk

firmware.elf: startup.c main.c ../firmware_lib/gpio.c ../firmware_lib/spi.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^