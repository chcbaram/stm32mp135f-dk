#ifndef BSP_H_
#define BSP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "def.h"


#include "stm32mp13xx_hal.h"
#include "stm32mp13xx_disco_conf.h"
#include "stm32mp13xx_disco_stpmic1.h"

void logPrintf(const char *fmt, ...);



bool bspInit(void);

void delay(uint32_t time_ms);
uint32_t millis(void);

void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif