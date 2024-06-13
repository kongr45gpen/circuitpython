/*
    GNU linker script for STM32H755 with filesystem, tcm
    CM4 (second core) at 0x08100000 - 0x081FFFFF
*/

/* Entry Point */
ENTRY(Reset_Handler)

_ld_default_stack_size = 24K;

/* Specify the memory areas */
MEMORY
{
    FLASH (rx)          : ORIGIN = 0x08100000, LENGTH = 1024K
    FLASH_ISR (rx)      : ORIGIN = 0x08100000, LENGTH = 128K    /* sector 0, 128K */
    FLASH_FS (r)        : ORIGIN = 0x08120000, LENGTH = 384K    /* sector 1-3, 128K */
    FLASH_FIRMWARE (rx) : ORIGIN = 0x08180000, LENGTH = 512K    /* sectors 4*128 */
    DTCM (xrw)          : ORIGIN = 0x20000000, LENGTH = 128K
    RAM_D1 (xrw)        : ORIGIN = 0x24000000, LENGTH = 512K    /* AXI SRAM */
    SRAM_D2 (xrw)       : ORIGIN = 0x30000000, LENGTH = 288K    /* AHB D2 SRAM */
    RAM (xrw)           : ORIGIN = 0x10000000, LENGTH = 288K    /* Use SRAM 2 for CM4 */
    SRAM_D3 (xrw)       : ORIGIN = 0x38000000, LENGTH = 64K     /* AHB D3 SRAM */
    ITCM (xrw)          : ORIGIN = 0x00000000, LENGTH = 64K
}

/* produce a link error if there is not this amount of RAM for these sections */
_minimum_stack_size = 24K; /*TODO: this can probably be bigger, but how big?*/
_minimum_heap_size = 16K;

/* brainless copy paste for stack code. Results in ambiguous hard crash */
/* _ld_default_stack_size = 20K; */

/* Define the top end of the stack.  The stack is full descending so begins just
   above last byte of RAM.  Note that EABI requires the stack to be 8-byte
   aligned for a call. */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* RAM extents for the garbage collector */
_ram_start = ORIGIN(RAM);
_ram_end = ORIGIN(RAM) + LENGTH(RAM);
