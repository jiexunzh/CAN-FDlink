#ifndef DATA_H
#define DATA_H

#include <stdint.h>

typedef enum
{
    Fault = 0x00,        /* 节点故障 */
    Disconnected = 0x01, /* 节点未连接CAN FDlink */
    Connecting = 0x02,   /* 节点连接CAN FDlink */
    Operational = 0x03,  /* 节点运行（传输数据） */
} nodeState_TypeDef;

/**
 * @brief This structure contains all necessary informations to define a CAN-FDlink node
 */
typedef struct
{
    uint8_t id;                   /* 节点ID */
    uint16_t heartbeat_time;      /* 心跳间隔 */
    nodeState_TypeDef node_state; /* 节点状态 */
} nodeMsg_TypeDef;

/**
 * @brief The CANFD message structure
 */
typedef struct
{
    uint32_t efid;
    uint8_t dlc;
    uint8_t data[64];
} canfdMsg_TypeDef;

#endif /* DATA_H */
