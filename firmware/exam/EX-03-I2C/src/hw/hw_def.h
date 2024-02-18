#ifndef HW_DEF_H_
#define HW_DEF_H_



#include "bsp.h"


#define _DEF_FIRMWATRE_VERSION    "V240214R1"
#define _DEF_BOARD_NAME           "STM32MP135-FW"



#define _USE_HW_LED
#define      HW_LED_MAX_CH          2
#define      HW_LED_CH_LED_R        _DEF_LED1
#define      HW_LED_CH_LED_B        _DEF_LED2

#define _USE_HW_UART                
#define      HW_UART_MAX_CH         1
#define      HW_UART_CH_SWD         _DEF_UART1
#define      HW_UART_CH_CLI         _DEF_UART1

#define _USE_HW_LOG
#define      HW_LOG_CH              HW_UART_CH_SWD

#define _USE_HW_CLI
#define      HW_CLI_CMD_LIST_MAX    32
#define      HW_CLI_CMD_NAME_MAX    16
#define      HW_CLI_LINE_HIS_MAX    8
#define      HW_CLI_LINE_BUF_MAX    64

#define _USE_HW_I2C
#define      HW_I2C_MAX_CH          1
#define      HW_I2C_CH_EEPROM       _DEF_I2C1


//-- USE CLI
//
#define _USE_CLI_HW_LED             1
#define _USE_CLI_HW_I2C             1


#endif