#include "modbus_canfd_slave.h"
#include "canfdlink.h"
#include "canfdlink_port.h"
#include "modbus_common.h"

static void analysis_enquiry_frame_efid(uint32_t efid, ModbusCanfd_efidMsg* efid_msg);
static void modbus_canfd_03H(uint8_t* pdu);

#if 0
/**
 * @brief  处理modbus canfd问询帧
 * @param
 * @retval
 */
uint8_t process_modbus_canfd(slaveMsg_TypeDef* slave, canfdMsg_TypeDef* msg)
{
    ModbusCanfd_efidMsg efid_msg;

    /* -------------efid部分--------------- */
    /* 解析Modbus CANFD问询帧的efid */
    analysis_enquiry_frame_efid(msg->efid, &efid_msg);

    /* 检查问答标识 */
    if ()

        /* 检查PDU长度 */
        if (efid_msg.pdu_len < EXPECT_RESPONE_FRAME_LEN || efid_msg.pdu_len > CANFD_MAX_LEN)
        {

            return 0; /* efid错误 */
        }

    /* 判断问询帧的从节点地址 */
    if (efid_msg.slave_id != slave->id)
    {
        return 0; /* 从节点地址不符，无需应答 */
    }

    /* -------------PDU部分--------------- */
    /* 判断功能码 */
    switch (msg->data[0])
    {
    case 0x03:
        modbus_canfd_03H(msg->data);
        break;

    case 0x10:
        // modbus_canfd_10H();
        break;

    default: /* 不支持的功能码 */
        // RspCode = RSP_ERR_CMD;
        // MODS_SendAckErr(RspCode);
        break;
    }

    return 1;
}

/**
 * @brief  解析modbus canfd问询帧的efid
 * @param
 * @retval
 */
static void analysis_enquiry_frame_efid(uint32_t efid, ModbusCanfd_efidMsg* efid_msg)
{
    efid_msg->frame_id = (efid >> 25) & 0xF;   /* 帧标识 */
    efid_msg->frame_id = (efid >> 24) & 0x1;   /* 问答标识 */
    efid_msg->pdu_len = (efid >> 16) & 0xFF; /* modbus canfd PDU 长度 */
    efid_msg->slave_id = (efid >> 8) & 0xFF; /* 目标节点即从节点 */
    efid_msg->master_id = efid & 0xFF;       /* 源节点即主节点 */
}

// static void respond_exception(ModbusCanfd_efidMsg* efid_msg, ModbusCanfd_exceptionCode exception_code)
// {
//     canfdMsg_TypeDef* msg = {0};

//     msg->data[0] = modbus_canfd.canfd_rece_buf[1] | 0x80; /* exception func code */
//     msg->data[1] = exception_code;                        /* err code */

//     msg->dlc = 2;
//     canfd_send(&msg);
// }

static void modbus_canfd_03H(uint8_t* pdu)
{
}

#endif
