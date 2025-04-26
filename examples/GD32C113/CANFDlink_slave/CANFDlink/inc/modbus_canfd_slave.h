#ifndef MODBUS_CANFD_SLAVE_H
#define MODBUS_CANFD_SLAVE_H

#include "data.h"

#define EXPECT_RESPONE_FRAME_LEN 2  /* 异常响应帧长度 */
#define CANFD_MAX_LEN            64 /* CANFD最大承载数据量 */
#define MAX_READ_REG_NUM         31 /* modbus canfd 单次最多可读取的寄存器数量 (64-1-1)/2 */
#define MAX_WRITE_REG_NUM        29 /* modbus canfd 单次最多可写入的寄存器数量 (64-1-4-1)/2 */

/**
 * @brief  modbus canfd 拓展帧ID信息定义
 */
typedef struct
{
    uint8_t frame_id;  /* 帧标识 */
    uint8_t isEnquiry; /* 问答标识 */
    uint8_t pdu_len;   /* PDU长度 */
    uint8_t slave_id;  /* 从节点ID */
    uint8_t master_id; /* 主节点ID */
} ModbusCanfd_efidMsg;

/**
 * @brief  modbus canfd 异常代码定义
 */
typedef enum
{
    ILLEGAL_FUNC = 0x01, /* 非法功能：使用了目前不支持的功能码 */
    ILLEGAL_ADDR,        /* 非法数据地址：地址不存在 */
    ILLEGAL_VALUE,       /* 非法数据值：写入的数据超出范围 */
    ILLEGAL_ACCESS,      /* 非法访问：地址不可写 */
    ILLEGAL_EFID,        /* 非法efid：问答标识或PDU长度错误 */
    ILLEGAL_REG_NUM,     /* 非法的寄存器数量：读取或写入的寄存器超出CAN FD的承载数量 */
} ModbusCanfd_exceptionCode;

uint8_t process_modbus_canfd(slaveMsg_TypeDef* slave, canfdMsg_TypeDef* msg);

#endif /* MODBUS_CANFD_SLAVE_H */
