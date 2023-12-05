// Console IO is a wrapper between the actual in and output and the console code

#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include <stdint.h>
#include "stm32f3xx_hal.h"

#include <FreeRTOS.h>
#include "stream_buffer.h"

typedef enum {CONSOLE_SUCCESS = 0u, CONSOLE_ERROR = 1u } eConsoleError;


#ifdef __cplusplus
extern "C" {
#endif

eConsoleError ConsoleIoInit(UART_HandleTypeDef *huartHandle, StreamBufferHandle_t *streamHandle);

#ifdef __cplusplus
}
#endif

eConsoleError ConsoleIoReceive(uint8_t* character, uint32_t *readLength, size_t millisToWait);

eConsoleError ConsoleIoSendString(const char *buffer); // must be null terminated
eConsoleError ConsoleIoHandleInputInterrupt();


#endif // CONSOLE_IO_H
