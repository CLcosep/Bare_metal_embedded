include ../common.mk

firmware.elf: startup.c main.c ../firmware_lib/gpio.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^