/*
 * Memory Spaces Definitions.
 *
 * Need modifying for a specific board. 
 *   FLASH.ORIGIN: starting address of flash
 *   FLASH.LENGTH: length of flash
 *   RAM.ORIGIN: starting address of RAM bank 0
 *   RAM.LENGTH: length of RAM bank 0
 *
 * The values below can be addressed in further linker scripts
 * using functions like 'ORIGIN(RAM)' or 'LENGTH(RAM)'.
 */

/*
*MEMORY
*{
*  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 128K
*  CCMRAM (xrw) : ORIGIN = 0x10000000, LENGTH = 64K
*  VECTORS (rx) : ORIGIN = 0x08000000, LENGTH = 16K
*  PARAMS (rx) : ORIGIN = 0x08004000, LENGTH = 16K
*  FLASH(rx) : ORIGIN = 0x08008000, LENGTH = 736K
*  LOG (rx) : ORIGIN =  0x080C0000, LENGTH = 256K
*}
*/

MEMORY
{
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
	FLASH (rx) : ORIGIN = 0x8000000, LENGTH = 1024K
}
