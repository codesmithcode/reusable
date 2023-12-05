// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include "stm32f3xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ThreadLocalUartOutputStream.h"

static uint8_t recvd_uart_data; // receive buffer
static UART_HandleTypeDef *huart = NULL;
static StreamBufferHandle_t *stream = NULL;

eConsoleError ConsoleIoInit(UART_HandleTypeDef *huartHandle, StreamBufferHandle_t *streamHandle)
{
	huart = huartHandle;
	stream = streamHandle;
	HAL_UART_Receive_IT(huart, &recvd_uart_data, 1);

	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoHandleInputInterrupt()
{
	xStreamBufferSendFromISR( *stream, &recvd_uart_data, sizeof(uint8_t), NULL);
	HAL_UART_Receive_IT(huart, &recvd_uart_data, 1);

	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoReceive(uint8_t* character, uint32_t *readLength, size_t millisToWait)
{

	*readLength = xStreamBufferReceive( *stream,
	                            character,
								sizeof(uint8_t),
								 pdMS_TO_TICKS(millisToWait) );
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	printToThreadLocalUartOutputStream(buffer);
//	output.print(buffer);
//	printf("%s", buffer);
	return CONSOLE_SUCCESS;
}

