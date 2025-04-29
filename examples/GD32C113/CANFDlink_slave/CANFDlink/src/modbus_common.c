/* 
    基于Modbus寄存器数据映射表实现Modbus读写寄存器基本功能，
    适用于 Modbus RTU / Modbus CANFD / Modbus TCP
*/
#include "modbus_common.h"
#include "modbus_registers.h"

static void write_high_16bits(uint32_t* p_reg32, uint16_t reg16);
static void write_low_16bits(uint32_t* p_reg32, uint16_t reg16);

/**
 * @brief  read_modbus_reg
 * @param  reg_addr 读取的寄存器地址
 * @param  p_read 存放寄存器读取值变量的指针
 * @retval 读取成功 / 读取地址异常
 */
RegRead_TypeDef read_modbus_reg(uint16_t reg_addr, uint16_t* p_read)
{
    uint16_t value = 0;
    RegRead_TypeDef RegRead_state = RegRead_ADDR_ERROR;
    uint16_t i;

    /* 遍历Modbus寄存器数据映射表 */
    for (i = 0; i < MODBUS_DATA_NUM; i++)
    {
        /* 数据使用1个Modbus寄存器（8位或16位数据） */
        if (MODBUS_REGISTERS[i].reg_num == USE_ONE_REG_8BIT || MODBUS_REGISTERS[i].reg_num == USE_ONE_REG_16BIT)
        {
            /* reg_addr == 起始地址 */
            if (reg_addr == MODBUS_REGISTERS[i].start_addr)
            {
                if (MODBUS_REGISTERS[i].reg_num == USE_ONE_REG_8BIT) /* 8位数据 */
                {
                    value = *(uint8_t*)MODBUS_REGISTERS[i].p_data;
                }
                else /* 16位数据 */
                {
                    value = *(uint16_t*)MODBUS_REGISTERS[i].p_data;
                }
                RegRead_state = RegRead_SUCCESS;
                break;
            }
        }
        /* 数据使用2个Modbus寄存器（32位数据） */
        else if (MODBUS_REGISTERS[i].reg_num == USE_TWO_REG_32BIT)
        {
            /* reg_addr == 起始地址 || 起始地址 + 1 */
            if (reg_addr == MODBUS_REGISTERS[i].start_addr || reg_addr == MODBUS_REGISTERS[i].start_addr + 1)
            {
                if (reg_addr == MODBUS_REGISTERS[i].start_addr) /* 起始地址 */
                {
                    value = (*(uint32_t*)MODBUS_REGISTERS[i].p_data) >> 16;  // 读数据高16位
                }
                else /* 起始地址 + 1 */
                {
                    value = (*(uint32_t*)MODBUS_REGISTERS[i].p_data) & 0xffff;  // 读数据低16位
                }
                RegRead_state = RegRead_SUCCESS;
                break;
            }
        }
    }

    if (RegRead_state == RegRead_SUCCESS)
    {
        *p_read = value;
    }

    return RegRead_state; /* 读取成功，返回0；地址异常，返回1 */
}

/**
 * @brief  read_modbus_reg
 * @param  reg_addr 寄存器地址
 * @param  reg_value 寄存器值
 * @retval 写入成功 / 地址异常 / 不可写入
 */
RegWrite_TypeDef write_modbus_reg(uint16_t reg_addr, uint16_t reg_value)
{
    uint16_t i;

    /* 遍历Modbus寄存器数据映射表 */
    for (i = 0; i < MODBUS_DATA_NUM; i++)
    {
        /* 数据使用1个Modbus寄存器（8位或16位数据） */
        if (MODBUS_REGISTERS[i].reg_num == USE_ONE_REG_8BIT || MODBUS_REGISTERS[i].reg_num == USE_ONE_REG_16BIT)
        {
            if (reg_addr == MODBUS_REGISTERS[i].start_addr)
            {
                if (MODBUS_REGISTERS[i].access_type == ONLY_READ)
                {
                    return RegWrite_ACCESS_ERROR;
                }
                if (MODBUS_REGISTERS[i].reg_num == USE_ONE_REG_8BIT) /* 8位数据 */
                {
                    *(uint8_t*)MODBUS_REGISTERS[i].p_data = (reg_value & 0xFF);
                }
                else /* 16位数据 */
                {
                    *(uint16_t*)MODBUS_REGISTERS[i].p_data = reg_value;
                }
                return RegWrite_SUCCESS;
            }
        }
        /* 数据使用2个Modbus寄存器（32位数据） */
        else if (MODBUS_REGISTERS[i].reg_num == USE_TWO_REG_32BIT)
        {
            /* 判断寄存器地址 */
            if (reg_addr == MODBUS_REGISTERS[i].start_addr || reg_addr == MODBUS_REGISTERS[i].start_addr + 1)
            {
                if (MODBUS_REGISTERS[i].access_type == ONLY_READ)
                {
                    return RegWrite_ACCESS_ERROR;
                }
                if (reg_addr == MODBUS_REGISTERS[i].start_addr) /* 起始地址 */
                {
                    write_high_16bits((uint32_t*)MODBUS_REGISTERS[i].p_data, reg_value);  // 写入数据高16位
                }
                else /* 起始地址 + 1 */
                {
                    write_low_16bits((uint32_t*)MODBUS_REGISTERS[i].p_data, reg_value);  // 写入数据低16位
                }
                return RegWrite_SUCCESS;
            }
        }
    }

    return RegWrite_ADDR_ERROR;
}

/**
 * @brief  向32位数据的高16位写入值
 * @param  p_reg32 32位数据指针
 * @param  reg16 16位数据
 * @retval
 */
static void write_high_16bits(uint32_t* p_reg32, uint16_t reg16)
{
    uint32_t reg16_shifted;

    // 清除reg32的高16位
    *p_reg32 &= ~0xFFFF0000;

    // 将reg16移到高16位置位
    reg16_shifted = ((uint32_t)reg16) << 16;

    // 将reg32的高16位置位
    *p_reg32 |= reg16_shifted;
}

/**
 * @brief  向32位数据的低16位写入值
 * @param  p_reg32 32位数据指针
 * @param  reg16 16位数据
 * @retval
 */
static void write_low_16bits(uint32_t* p_reg32, uint16_t reg16)
{
    // 清除reg32的低16位
    *p_reg32 &= ~0x0000FFFF;

    // 将reg32的低16位置位
    *p_reg32 |= (uint32_t)reg16;
}
