#ifndef BSP_H_
#define BSP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "def.h"


#include "stm32mp13xx_hal.h"
#include "stm32mp13xx_ll_etzpc.h"


void logPrintf(const char *fmt, ...);



bool bspInit(void);

void delay(uint32_t time_ms);
uint32_t millis(void);

void Error_Handler(void);


static inline void invalidate_cache(uint32_t start, uint32_t size)
{
  uint32_t current = start & ~31U;
  uint32_t end = (start + size + 31U) & ~31U;
  while (current < end)
  {
    L1C_InvalidateDCacheMVA((void*)current);
    current += 32U;
  }
}

static inline void clean_cache(uint32_t start, uint32_t size)
{
  uint32_t current = start & ~31U;
  uint32_t end = (start + size + 31U) & ~31U;
  while (current < end)
  {
    L1C_CleanDCacheMVA((void*)current);
    current += 32U;
  }
}

#define invalidate_cache_by_addr(__ptr__, __size__) invalidate_cache((uint32_t)(__ptr__), (uint32_t)(__size__))
#define clean_cache_by_addr(__ptr__, __size__) clean_cache((uint32_t)(__ptr__), (uint32_t)(__size__))


#ifdef __cplusplus
}
#endif

#endif