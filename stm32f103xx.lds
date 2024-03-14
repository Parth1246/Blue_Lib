ENTRY(Reset_Handler)

MEMORY
{
	FLASH(rx): ORIGIN =0x08000000, LENGTH =64K
	SRAM(rwx): ORIGIN =0x20000000, LENGTH =20K 
}

SECTIONS
{
	.text :
	{
	   KEEP(*(.isr_vector))
	   *(.text)
	   *(.text.*)
	   *(.init)
	   *(.fini)
	   *(.rodata)
	   *(.rodata.*)
	   . = ALIGN(4);
       _etext = .;
	}> FLASH

	_la_data = LOADADDR(.data);

	.data :
	{
	   _sdata = .;
	   *(.data)
	   *(.data.*)
	   . = ALIGN(4);
       _edata = .;
	}> SRAM AT> FLASH

	.bss :
	{
	  _sbss = .;
	  *(.bss)
	  *(.bss.*)
	  *(COMMON)
	  . = ALIGN(4);
      _ebss = .;
	}> SRAM

}