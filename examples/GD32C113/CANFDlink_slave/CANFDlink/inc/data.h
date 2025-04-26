#ifndef DATA_H
#define DATA_H

#include <stdint.h>

/**
 * @brief This structure contains all necessary informations to define a CAN-FDlink slave node
 */
typedef struct
{
    uint8_t id;
    uint16_t heartbeat_time;
} slaveMsg_TypeDef;

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
