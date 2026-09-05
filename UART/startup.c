#include <stdint.h>

// defined by linker script (.ld)
extern uint32_t _estack, _sdata, _edata, _sidata, _sbss, _ebss;

void Reset_Handler(void);
void Default_Handler(void);

/*
    Every unused interrupt handler just aliases to Default_Handler unless overriden
*/
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

//the vector table itself, "section" pins it at the very start of Flash - see linker script
__attribute__((section(".isr_vector")))
void (* const vector_table[]) (void) = {
    (void (*)(void)) &_estack, //word 0: initial stack pointer value
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0, 0, 0, 0,         //reserved
    SVC_Handler,
    DebugMon_Handler,
    0,                  //reserved
    PendSV_Handler,
    SysTick_Handler,
    // Peripheral interrupts (USART, TIM, EXIT..) would follow here
    // not needed yet, LED blink doesnt enable any interrupts, so these core exceptions are the only entries that can ever fire.
};

void Default_Handler(void) {
    while(1); //something unexpected happened - halt here rather than run wild
}

void Reset_Handler(void) {
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) *dst++ = *src++; // copy .data from flash to RAM

    dst = &_sbss;
    while (dst < &_ebss) *dst++ = 0; // zero the .bss

    extern int main(void);
    main();

    while(1); // if main() ever returns, halt
}