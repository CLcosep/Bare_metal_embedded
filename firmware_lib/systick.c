#include "systick.h"

#define SYST_CSR (*(volatile uint32_t *) 0xE000E010)
#define SYST_RVR (*(volatile uint32_t *) 0xE000E014)
#define SYST_CVR (*(volatile uint32_t *) 0xE000E018)

static volatile uint32_t ms_tick = 0;

void  SysTick_Handler(void) {ms_tick++; }

void systick_init_1ms(void) {
    SYST_RVR = 7999;
    SYST_CVR = 0;
    SYST_CSR = (1 << 0) | ( 1 << 1) | (1 << 2);
}

uint32_t millis(void) {return ms_tick; }