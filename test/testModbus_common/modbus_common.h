#ifndef MODBUS_COMMON_H
#define MODBUS_COMMON_H

#include <stdint.h>

typedef enum
{
    RegRead_SUCCESS = 0,
    RegRead_ADDR_ERROR,     /* 寄存器地址错误 */
} RegRead_TypeDef;

typedef enum
{
    RegWrite_SUCCESS = 0,
    RegWrite_ADDR_ERROR,   /* 寄存器地址错误 */
    RegWrite_ACCESS_ERROR, /* 寄存器不可写入 */
} RegWrite_TypeDef;

RegRead_TypeDef read_modbus_reg(uint16_t reg_addr, uint16_t* p_read);
RegWrite_TypeDef write_modbus_reg(uint16_t reg_addr, uint16_t reg_value);

#endif /* MODBUS_COMMON_H */
