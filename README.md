# STM32-MCP2515

Forked from https://github.com/thumptech/STM32-MCP2515

I removed the hardcoded requirement for the SPI and MCP clock settings

The user must still however ensure the correct STM32 family is used
by changing the #include for the appropriate HAL config
default is STM32F4 family, ie: "#include <stm32f4xx_hal.h>"
if anyone knows of a more elegant way to include the correct header
please let me know.

Typical usage:

##1. Initialisation:

#include "mcp2515.h"
mcp2515_t mcp2515 = {&hspi2, {MCP2515_CS_GPIO_Port, MCP2515_CS_Pin},MCP_16MHZ}; // SPI settings, MCP crystal frequency and operating mode
can_frame TxFrame;
can_frame RxFrame;

##2. Setup:
MCP_reset(&mcp2515);
MCP_setBitrate(&mcp2515,CAN_250KBPS);
MCP_setMode(&mcp2515,MODE_NORMAL);

##3 Transmit a message
TxFrame.can_id = 0x0FF; 
TxFrame.can_dlc = 8;
TxFrame.data[0] = 0;
TxFrame.data[1] = 1;
TxFrame.data[2] = 2;
TxFrame.data[3] = 3;
TxFrame.data[4] = 4;
TxFrame.data[5] = 5;
TxFrame.data[6] = 6;
TxFrame.data[7] = 7;
MCP_sendMessage(&mcp2515,&TxFrame);

##3 Receive a message
if (MCP_readMessage(&mcp2515,&RxFrame) == ERROR_OK) {
    // Frame received, do whatever you want with it.    
}
else {
    // Frame not received, do nothing
}