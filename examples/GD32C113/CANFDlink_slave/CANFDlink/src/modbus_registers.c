/*
    Modbus寄存器数据映射
*/
#include "modbus_registers.h"

int32_t sensor_data[6] = {0};
uint8_t led_control = 0;

/* 用户自定义通信对象映射表 - 0表示无对象 */
static uint16_t sub_index[SUB_INDEX_LEN] = {
    0x2000, 0x2001, 0x2002, 0x2003, 0x2004, 0x2005, 
    0x2006, 0x2007, 0x2008, 0x2009, 0x200A, 0x200B,
};

/* Modbus寄存器数据映射表 - 0地址不可使用 */
const ModbusReg_TypeDef MODBUS_REGISTERS[] = {
	/* 用户自定义通信对象区 - 该部分放在最前面，是为了提高查询速度 */
    {0x2000, USE_TWO_REG_32BIT, ONLY_READ, &sensor_data[0]},
    {0x2002, USE_TWO_REG_32BIT, ONLY_READ, &sensor_data[1]},
    {0x2004, USE_TWO_REG_32BIT, ONLY_READ, &sensor_data[2]},
    {0x2006, USE_TWO_REG_32BIT, ONLY_READ, &sensor_data[3]},
    {0x2008, USE_TWO_REG_32BIT, ONLY_READ, &sensor_data[4]},
    {0x200A, USE_TWO_REG_32BIT, ONLY_READ, &sensor_data[5]},

    {0x2100, USE_ONE_REG_8BIT, READ_WRITE, &led_control},	
	
	/* 通信对象映射区 - 该部分一共有 SUB_INDEX_LEN 个寄存器，用户不需要修改 */
	{0x1000, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[0]},
    {0x1001, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[1]},
    {0x1002, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[2]},
    {0x1003, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[3]},
    {0x1004, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[4]},
    {0x1005, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[5]},
    {0x1006, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[6]},
    {0x1007, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[7]},
    {0x1008, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[8]},
    {0x1009, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[9]},
    {0x100A, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[10]},
	{0x100B, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[11]},
    {0x100C, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[12]},
    {0x100D, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[13]},
    {0x100E, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[14]},
    {0x100F, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[15]},
    {0x1010, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[16]},
    {0x1011, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[17]},
    {0x1012, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[18]},
    {0x1013, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[19]},
    {0x1014, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[20]},
    {0x1015, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[21]},    
	{0x1016, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[22]},
    {0x1017, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[23]},
    {0x1018, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[24]},
    {0x1019, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[25]},
    {0x101A, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[26]},
    {0x101B, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[27]},
    {0x101C, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[28]},
    {0x101D, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[29]},
    {0x101E, USE_ONE_REG_16BIT, READ_WRITE, &sub_index[30]},
};

/* modbus寄存器（数据）个数 */
const uint16_t MODBUS_DATA_NUM = sizeof(MODBUS_REGISTERS) / sizeof(ModbusReg_TypeDef);
