// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include "stm32f3xx_hal.h"

eConsoleError ConsoleIoInit(void)
{
	return CONSOLE_SUCCESS;
}

uint32_t old_primask;

eConsoleError DisableInterrupt() {
	old_primask = __get_PRIMASK();
	__disable_irq();

	return CONSOLE_SUCCESS;
}
eConsoleError RestoreInterrupt() {
	__set_PRIMASK(old_primask);

	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	printf("%s", buffer);
	return CONSOLE_SUCCESS;
}

