#include "pmic.h"



#ifdef _USE_HW_PMIC
#include "cli.h"
#include "i2c.h"
#include "pmic_reg.h"


#if CLI_USE(HW_PMIC)
static void cliCmd(cli_args_t *args);
#endif

static bool pmicRegRead(uint8_t addr, uint8_t *p_data);
static bool pmicRegWrite(uint8_t addr, uint8_t data);
static bool pmicRegUpdate(uint8_t addr, uint8_t data, uint8_t mask);
static bool pmicInitReg(void);

static bool is_init = false;
static bool is_enable = false;
static bool is_detected = false;
static const uint8_t i2c_ch = _DEF_I2C1;
static const uint8_t i2c_addr = 0x33;





bool pmicInit(void)
{
  bool ret = true;


  if (i2cIsBegin(i2c_ch) == true)
    ret = true;
  else
    ret = i2cBegin(i2c_ch, 400);

  if (ret == true && i2cIsDeviceReady(i2c_ch, i2c_addr))
  {    
    is_detected = true;
  }
  else
  {
    ret = false;
  }

  is_enable = HW_PMIC_SETUP;

  logPrintf("[%s] pmicInit()\n", ret ? "OK":"NG");
  if (ret == true)
  {
    if (is_enable)
    {
      ret = pmicInitReg();
      logPrintf("[%s] pmicInitReg()\n", ret ? "OK":"NG");
    }
  }

  is_init = ret;

#if CLI_USE(HW_PMIC)
  cliAdd("pmic", cliCmd);
#endif
  return ret;
}

bool pmicInitReg(void)
{
  bool ret = true;


  pmicRegWrite(STPMIC1_MAIN_CONTROL_REG,    0x04);
  pmicRegWrite(STPMIC1_VIN_CONTROL_REG,     0xC0);
  pmicRegWrite(STPMIC1_MASK_RESET_BUCK_REG, 0x04);

  // VDD_CPU
  //
  pmicRegUpdate(STPMIC1_BUCK1_CONTROL_REG, 26<<2, 0xFC); // 1.25V
  pmicRegUpdate(STPMIC1_BUCK1_CONTROL_REG,  1<<0, 0x01);

  // VDD_DDR
  //
  pmicRegUpdate(STPMIC1_BUCK2_CONTROL_REG, 30<<2, 0xFC); // 1.35V
  pmicRegUpdate(STPMIC1_BUCK2_CONTROL_REG,  1<<0, 0x01);
  
  // VDD
  //
  pmicRegUpdate(STPMIC1_BUCK3_CONTROL_REG, 54<<2, 0xFC); // 3.3V
  pmicRegUpdate(STPMIC1_BUCK3_CONTROL_REG,  1<<0, 0x01);

  // VDD_CORE
  //
  pmicRegUpdate(STPMIC1_BUCK4_CONTROL_REG, 26<<2, 0xFC); // 1.25V
  pmicRegUpdate(STPMIC1_BUCK4_CONTROL_REG,  1<<0, 0x01);

  // VDD_ADC
  //
  pmicRegUpdate(STPMIC1_LDO1_CONTROL_REG, 24<<2, 0xFC); // 3.3V
  pmicRegUpdate(STPMIC1_LDO1_CONTROL_REG,  1<<0, 0x01);

  // VDD_USB
  //
  pmicRegUpdate(STPMIC1_LDO4_CONTROL_REG,  1<<0, 0x01);

  // VDD_SD
  //
  pmicRegUpdate(STPMIC1_LDO5_CONTROL_REG, 20<<2, 0xFC); // 2.9V
  pmicRegUpdate(STPMIC1_LDO5_CONTROL_REG,  1<<0, 0x01);  

  // 1V8_PERIPH
  //
  pmicRegUpdate(STPMIC1_LDO6_CONTROL_REG,  9<<2, 0xFC); // 1.8V
  pmicRegUpdate(STPMIC1_LDO6_CONTROL_REG,  1<<0, 0x01);  


  // VREF_DDR Disable
  //
  pmicRegUpdate(STPMIC1_VREF_DDR_CONTROL_REG,  0<<0, 0x01);  


  // v3v3_sw   enable usb SWOUT , enable active discharge 
  //
  pmicRegWrite(STPMIC1_USB_CONTROL_REG, 
    (1<<2) | // SWOUT_ON  : PD active when PWR_SW is disabled (SW_ON bit = 0)
    (1<<4) | // VBUSOTG_PD: PD active when PWR_USB_SW is disabled (VBUSOTG_ON bit = 0)
    (1<<5)   // SWOUT_PD  : PWR_SW enabled
    );

  return ret;
}

bool pmicRegRead(uint8_t addr, uint8_t *p_data)
{
  bool ret = true;

  ret = i2cReadByte(i2c_ch, i2c_addr, addr, p_data, 50);

  return ret;
}

bool pmicRegWrite(uint8_t addr, uint8_t data)
{
  bool ret = true;

  ret = i2cWriteByte(i2c_ch, i2c_addr, addr, data, 50);

  return ret;
}

bool pmicRegUpdate(uint8_t addr, uint8_t data, uint8_t mask)
{
  bool ret = true;
  uint8_t reg = 0;

  ret &= pmicRegRead(addr, &reg);

  reg &= ~mask;
  reg |= (data & mask);

  ret &= pmicRegWrite(addr, reg);

  return ret;
}

void pmicInfoBUCK1(void)
{
  const uint16_t buck1_voltage_table[] = {
    600, 625, 650, 675, 700, 725, 750, 775, 800, 825, 850, 875, 900, 925, 950, 975, 1000, 1025, 1050,
    1075, 1100, 1125, 1150, 1175, 1200, 1225, 1250, 1275, 1300, 1325, 1350, 1350, // 31  1,35
  };
  uint8_t reg;

  pmicRegRead(STPMIC1_BUCK1_CONTROL_REG, &reg);

  logPrintf("BUCK1 : VDD_CPU\n");
  logPrintf("  ENA - %d\n", (reg & (1<<0)) ? 1:0);
  logPrintf("  VOL - %d.%d\n", 
    buck1_voltage_table[reg>>2]/1000, 
    buck1_voltage_table[reg>>2]%1000
    );
}

void pmicInfoBUCK2(void)
{
  const uint16_t buck2_voltage_table[] = {
    1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
    1000, 1050, 1050, 1100, 1100, 1150, 1150, 1200, 1200, 1250, 1250, 1300, 1300, 1350, 1350, 1400, 1400, 1450, 1450, 1500, //
  };
  uint8_t reg;

  pmicRegRead(STPMIC1_BUCK2_CONTROL_REG, &reg);

  logPrintf("BUCK2 : VDD_DDR\n");
  logPrintf("  ENA - %d\n", (reg & (1<<0)) ? 1:0);
  logPrintf("  VOL - %d.%d\n", 
    buck2_voltage_table[reg>>2]/1000, 
    buck2_voltage_table[reg>>2]%1000
    );
}

void pmicInfoBUCK3(void)
{
  const uint16_t buck3_voltage_table[] = {
    1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, //
    1000, 1000, 1100, 1100, 1100, 1100, 1200, 1200, 1200, 1200, 1300, 1300, 1300, 1300, 1400, 1400, 1400, 1400, //
    1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, //
    3300, 3400,                                                                                                 //
  };
  uint8_t reg;

  pmicRegRead(STPMIC1_BUCK3_CONTROL_REG, &reg);

  logPrintf("BUCK3 : VDD\n");
  logPrintf("  ENA - %d\n", (reg & (1<<0)) ? 1:0);
  logPrintf("  VOL - %d.%d\n", 
    buck3_voltage_table[reg>>2]/1000, 
    buck3_voltage_table[reg>>2]%1000
    );
}

void pmicInfoBUCK4(void)
{
  const uint16_t buck4_voltage_table[] = {
    600, 625, 650, 675, 700, 725, 750, 775, 800, 825, 850, 875, 900, 925, 950, 975, 1000, 1025, 1050, 1075, 1100,     //
    1125, 1150, 1175, 1200, 1225, 1250, 1275, 1300, 1300, 1350, 1350, 1400, 1400, 1450, 1450, 1500, 1600, 1700, 1800, //
    1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, //
    3800, 3900,                                                                                                       //
  };
  uint8_t reg;

  pmicRegRead(STPMIC1_BUCK4_CONTROL_REG, &reg);

  logPrintf("BUCK4 : VDD_CORE\n");
  logPrintf("  ENA - %d\n", (reg & (1<<0)) ? 1:0);
  logPrintf("  VOL - %d.%d\n", 
    buck4_voltage_table[reg>>2]/1000, 
    buck4_voltage_table[reg>>2]%1000
    );
}

void pmicInfoLDO1(void)
{
  const uint16_t ldo1_voltage_table[] = {
    1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1800, 1900, 2000, 2100, //
    2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300,       //
  };
  uint8_t reg;

  pmicRegRead(STPMIC1_LDO1_CONTROL_REG, &reg);

  logPrintf("LDO1 : VDD_ADC\n");
  logPrintf("  ENA - %d\n", (reg & (1<<0)) ? 1:0);
  logPrintf("  VOL - %d.%d\n", 
    ldo1_voltage_table[reg>>2]/1000, 
    ldo1_voltage_table[reg>>2]%1000
    );
}

void pmicInfoLDO6(void)
{
  const uint16_t ldo6_voltage_table[] = {
    900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, //
    2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300,                  //
  };
  uint8_t reg;

  pmicRegRead(STPMIC1_LDO6_CONTROL_REG, &reg);

  logPrintf("LDO6 : 1V8_PERIPH\n");
  logPrintf("  ENA - %d\n", (reg & (1<<0)) ? 1:0);
  logPrintf("  VOL - %d.%d\n", 
    ldo6_voltage_table[reg>>2]/1000, 
    ldo6_voltage_table[reg>>2]%1000
    );
}

void pmicInfoLDO5(void)
{
  const uint16_t ldo5_voltage_table[] = {
    1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400,
    2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, //
  };
  uint8_t reg;

  pmicRegRead(STPMIC1_LDO5_CONTROL_REG, &reg);

  logPrintf("LDO5 : VDD_SD\n");
  logPrintf("  ENA - %d\n", (reg & (1<<0)) ? 1:0);
  logPrintf("  VOL - %d.%d\n", 
    ldo5_voltage_table[reg>>2]/1000, 
    ldo5_voltage_table[reg>>2]%1000
    );
}

void pmicInfoLDO4(void)
{
  uint8_t reg;

  pmicRegRead(STPMIC1_LDO4_CONTROL_REG, &reg);

  logPrintf("LDO5 : VDD_USB\n");
  logPrintf("  ENA - %d\n", (reg & (1<<0)) ? 1:0);
}

void pmicInfoPrint(void)
{
  pmicInfoBUCK1();
  pmicInfoBUCK2();
  pmicInfoBUCK3();
  pmicInfoBUCK4();
  pmicInfoLDO1();
  pmicInfoLDO6();
  pmicInfoLDO5();
  pmicInfoLDO4();
}

#if CLI_USE(HW_PMIC)
void cliCmd(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "info"))
  {
    cliPrintf("is_init     : %s\n", is_init ? "True":"False");
    cliPrintf("is_enable   : %s\n", is_enable ? "True":"False");
    cliPrintf("is_detected : %s\n", is_detected ? "True":"False");

    pmicInfoPrint();
    ret = true;
  }

  if (args->argc == 3 && args->isStr(0, "read") == true)
  {
    bool pmic_ret;
    uint8_t addr;
    uint8_t length;

    addr = (uint8_t) args->getData(1);
    length   = (uint8_t) args->getData(2);

    for (int i=0; i<length; i++)
    {
      uint8_t reg;
      pmic_ret = pmicRegRead(addr+i, &reg);

      if (pmic_ret == true)
      {
        cliPrintf("REG - 0x%02X : 0x%02X\n", addr+i, reg);
      }
      else
      {
        cliPrintf("REG - Fail \n");
        break;
      }
    }
    ret = true;
  }

  if (args->argc == 3 && args->isStr(0, "write") == true)
  {
    bool pmic_ret;
    uint8_t addr;
    uint8_t reg;

    addr = (uint8_t) args->getData(1);
    reg  = (uint8_t) args->getData(2);

    pmic_ret = pmicRegWrite(addr, reg);

    if (pmic_ret == true)
    {
      cliPrintf("REG - 0x%02X : 0x%02X\n", addr, reg);
    }
    else
    {
      cliPrintf("REG - Fail \n");
    }
    ret = true;
  }

  if (ret == false)
  {
    cliPrintf("pmic info\n");
    cliPrintf("pmic read  addr len\n");
    cliPrintf("pmic write addr data\n");
  }
}
#endif

#endif