#include <iostream>
#include <stdio.h>
#include "modbus_common.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {

    uint16_t reg_value = 0;

	// write 32bit data
    write_modbus_reg(0x2000,0x2345);    // high 16 bits
    write_modbus_reg(0x2001,0x6789);    // low 16 bits 
    
    // write 16bit data
    write_modbus_reg(0x1000,0xABCD);

    // write 8bit data
    write_modbus_reg(0x2100,0xABCD);    // only write 0xCD

	// read 32bit data
    read_modbus_reg(0x2000,&reg_value);
    printf("0x2000: 0x%X\n", reg_value);
    read_modbus_reg(0x2001,&reg_value);
    printf("0x2001: 0x%X\n", reg_value);    
    
    // read 16bit data
    read_modbus_reg(0x1000,&reg_value);
    printf("0x1000: 0x%X\n", reg_value);

    // read 8bit data
    read_modbus_reg(0x2100,&reg_value);
    printf("0x2100: 0x%04X\n", reg_value);
    
    // rw not exist addr
    if (read_modbus_reg(0x3000,&reg_value) == RegRead_ADDR_ERROR)
    {
        printf("This address does not exist.\n");
    }
    if (write_modbus_reg(0x3000,0x1111) == RegWrite_ADDR_ERROR)
    {
        printf("This address does not exist.\n");
    }    

    // write forbit write addr
    if (write_modbus_reg(0x2002,0x1111) == RegWrite_ACCESS_ERROR)
    {
        printf("This address is forbidden to write.\n");
    }   

	return 0;
}

