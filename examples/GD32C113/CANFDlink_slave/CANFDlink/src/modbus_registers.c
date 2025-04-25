/*
    Modbus寄存器数据映射
*/
#include "modbus_registers.h"

int32_t sensor_data[6] = {0};
uint8_t led_control = 0;

/* Modbus寄存器数据映射表 */
const ModbusReg_TypeDef MODBUS_REGISTERS[] = {
    {0x0000, USE_TWO_REG, ONLY_READ, &sensor_data[0]},
    {0x0002, USE_TWO_REG, ONLY_READ, &sensor_data[1]},
    {0x0004, USE_TWO_REG, ONLY_READ, &sensor_data[2]},
    {0x0006, USE_TWO_REG, ONLY_READ, &sensor_data[3]},
    {0x0008, USE_TWO_REG, ONLY_READ, &sensor_data[4]},
    {0x000A, USE_TWO_REG, ONLY_READ, &sensor_data[5]},

    {0x0100, USE_ONE_REG_8BIT, READ_WRITE, &led_control},
};

/* modbus寄存器（数据）个数 */
const uint16_t MODBUS_DATA_NUM = sizeof(MODBUS_REGISTERS) / sizeof(ModbusReg_TypeDef);
