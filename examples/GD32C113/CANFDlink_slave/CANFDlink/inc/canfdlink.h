#ifndef CANFDLINK_H
#define CANFDLINK_H

#include <stdint.h>

/* 帧类型标识 */
#define CMD_FRAME                ((uint32_t)0x4) /* 命令帧（0100B） */
#define CFG_FRAME                ((uint32_t)0x5) /* 配置帧（0101B） */
#define DATA_FRAME               ((uint32_t)0x7) /* 数据帧（0111B） */
#define HEART_FRAME              ((uint32_t)0xe) /* 心跳帧（1110B） */

/* 问/答 */
#define ENQUIRY                  ((uint32_t)1) /* 问询帧 */
#define RESPONSE                 ((uint32_t)0) /* 应答帧 */
#define RESERVE				     ((uint32_t)0) /* 保留 */

/* 心跳编码 */
#define HEART_CODE               ((uint32_t)0xa0)

#endif /* CANFDLINK_H */
