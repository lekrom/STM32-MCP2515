/*
 * mcp2515.h
 *
 *  Created on: Dec 13, 2020
 *      Author: matt
 */

#ifndef APPLICATION_USER_INC_MCP2515_H_
#define APPLICATION_USER_INC_MCP2515_H_

#include <stdint.h>

typedef unsigned char __u8;
typedef unsigned short __u16;
typedef unsigned long __u32;


/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000UL /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000UL /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000UL /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFUL /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFUL /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFUL /* omit EFF, RTR, ERR flags */

/*
 * Controller Area Network Identifier structure
 *
 * bit 0-28 : CAN identifier (11/29 bit)
 * bit 29   : error message frame flag (0 = data frame, 1 = error message)
 * bit 30   : remote transmission request flag (1 = rtr frame)
 * bit 31   : frame format flag (0 = standard 11 bit, 1 = extended 29 bit)
 */
typedef __u32 canid_t;

#define CAN_SFF_ID_BITS     11
#define CAN_EFF_ID_BITS     29

/* CAN payload length and DLC definitions according to ISO 11898-1 */
#define CAN_MAX_DLC 8
#define CAN_MAX_DLEN 8

struct can_frame {
    canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    __u8    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    __u8    data[CAN_MAX_DLEN] __attribute__((aligned(8)));
};

typedef enum {
	ERROR_OK = 0,
	ERROR_FAIL = 1,
	ERROR_ALLTXBUSY = 2,
	ERROR_FAILINIT = 3,
	ERROR_FAILTX = 4,
	ERROR_NOMSG = 5
} CAN_Error;

typedef enum {
	CLKOUT_DISABLE = -1,
	CLKOUT_DIV1 = 0x0,
	CLKOUT_DIV2 = 0x1,
	CLKOUT_DIV4 = 0x2,
	CLKOUT_DIV8 = 0x3,
} CAN_CLKOUT;

typedef enum {
	MCP_20MHZ, MCP_16MHZ, MCP_8MHZ
} CAN_CLOCK;

typedef enum {
	CAN_5KBPS,
	CAN_10KBPS,
	CAN_20KBPS,
	CAN_31K25BPS,
	CAN_33KBPS,
	CAN_40KBPS,
	CAN_50KBPS,
	CAN_80KBPS,
	CAN_83K3BPS,
	CAN_95KBPS,
	CAN_100KBPS,
	CAN_125KBPS,
	CAN_200KBPS,
	CAN_250KBPS,
	CAN_500KBPS,
	CAN_1000KBPS
} CAN_SPEED;

typedef enum {
	MASK0, MASK1
} MASK;

typedef enum {
	RXF0 = 0, RXF1 = 1, RXF2 = 2, RXF3 = 3, RXF4 = 4, RXF5 = 5
} RXF;

typedef enum {
	TXB0 = 0, TXB1 = 1, TXB2 = 2
} TXBn;

typedef enum {
	RXB0 = 0, RXB1 = 1
} RXBn;


CAN_Error MCP_reset(void);//
CAN_Error MCP_setListenOnlyMode();//
CAN_Error MCP_setSleepMode();//
CAN_Error MCP_setLoopbackMode();//
CAN_Error MCP_setNormalMode();//
CAN_Error MCP_setBitrate(CAN_SPEED canSpeed);//
CAN_Error MCP_setBitrateClock(CAN_SPEED canSpeed, CAN_CLOCK canClock); //
CAN_Error MCP_setFilterMask(MASK num, uint8_t ext, uint32_t ulData);//
CAN_Error MCP_setFilter(RXF num, uint8_t ext, uint32_t ulData);//
CAN_Error MCP_sendMessageTo(TXBn txbn, can_frame *frame);//
CAN_Error MCP_sendMessage(can_frame *frame);//
CAN_Error MCP_readMessageFrom(RXBn rxbn, can_frame *frame);//
CAN_Error MCP_readMessage(can_frame *frame);//
uint8_t MCP_checkReceive(void);//
uint8_t MCP_checkError(void);//
uint8_t MCP_getErrorFlags(void);//
void MCP_clearRXnOVRFlags(void);//
uint8_t MCP_getInterrupts(void);//
uint8_t MCP_getInterruptMask(void);//
void MCP_clearInterrupts(void);//
void MCP_clearTXInterrupts(void);
uint8_t MCP_getStatus(void);//
void MCP_clearRXnOVR(void);//
void MCP_clearMERR();//
void MCP_clearERRIF();//

#endif /* APPLICATION_USER_INC_MCP2515_H_ */

