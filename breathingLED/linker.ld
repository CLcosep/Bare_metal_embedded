MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 20K
}

_estack = ORIGIN(RAM) + LENGTH(RAM); /* top of RAM - stack grows downward from here*/ 

SECTIONS
{
    .isr_vector : {
        KEEP(*(.isr_vector)) /* the vector table must be the very firs thing in Flash*/
    } > FLASH

    .text : {
        *(.text*)       /*your compiled code*/
        *(.rodata*)     /*const data, e.g. string literals*/
    } > FLASH

    _sidata = LOADADDR(.data);  /*Where .data's initial values live in FLash*/

    .data : {
        _sdata = .;
        *(.data*)           /*initialized globals - live in RAM, copied from FLash*/
        _edata = .;
    } > RAM AT > FLASH

    .bss : {
        _sbss = .;
        *(.bss*)            /* uninitialized globals - zeroed at startup, RAM only*/
        *(COMMON)
        _ebss = .;
    } > RAM
}