// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include "stm32f3xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

uint8_t recvd_uart_data; // receive buffer
UART_HandleTypeDef *huart;

eConsoleError ConsoleIoInit(UART_HandleTypeDef *huartHandle)
{
	huart = huartHandle;
	HAL_UART_Receive_IT(huart, &recvd_uart_data, 1);

	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoHandleInputInterrupt(uint8_t* data)
{
	*data = recvd_uart_data;
	HAL_UART_Receive_IT(huart, &recvd_uart_data, 1);

	return CONSOLE_SUCCESS;
}

uint32_t old_primask;

eConsoleError DisableInterrupt() {
	taskENTER_CRITICAL();

	return CONSOLE_SUCCESS;
}
eConsoleError RestoreInterrupt() {
	taskEXIT_CRITICAL();
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	printf("%s", buffer);
	return CONSOLE_SUCCESS;
}

