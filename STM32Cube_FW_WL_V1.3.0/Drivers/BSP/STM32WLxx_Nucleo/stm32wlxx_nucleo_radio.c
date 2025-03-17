/**
  ******************************************************************************
  * @file    stm32wlxx_nucleo_radio.c
  * @author  MCD Application Team
  * @brief   This file provides set of firmware functions to manage:
  *          - RF circuitry available on STM32WLXX-Nucleo
  *            Kit from STMicroelectronics
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_nucleo_radio.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32WLXX_NUCLEO
  * @{
  */

/** @addtogroup STM32WLXX_NUCLEO_RADIO_LOW_LEVEL
  * @brief This file provides set of firmware functions to Radio switch 
  *        available on STM32WLXX-Nucleo Kit from STMicroelectronics.
  * @{
  */

/** @addtogroup STM32WLXX_NUCLEO_RADIO_LOW_LEVEL_Exported_Functions
  * @{
  */
  
/**
  * @brief  Init Radio Switch 
  * @retval BSP status
  */
void BJJA_LM_LoadHSECapacitor();
int32_t BSP_RADIO_Init(void)
{
	BJJA_LM_LoadHSECapacitor();//add by weli
#ifdef DK_TRSWITCH
  GPIO_InitTypeDef  gpio_init_structure = {0};
  
  /* Enable the Radio Switch Clock */
  RF_SW_CTRL3_GPIO_CLK_ENABLE();
  
  /* Configure the Radio Switch pin */
  gpio_init_structure.Pin   = RF_SW_CTRL1_PIN;
  gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull  = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  
  HAL_GPIO_Init(RF_SW_CTRL1_GPIO_PORT, &gpio_init_structure);
  
  gpio_init_structure.Pin = RF_SW_CTRL2_PIN;
  HAL_GPIO_Init(RF_SW_CTRL2_GPIO_PORT, &gpio_init_structure);
  
  gpio_init_structure.Pin = RF_SW_CTRL3_PIN;
  HAL_GPIO_Init(RF_SW_CTRL3_GPIO_PORT, &gpio_init_structure);

  HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_RESET); 
#else	
	GPIO_InitTypeDef  gpio_init_structure = {0};

  /* Enable the Radio Switch Clock */
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* Configure the Radio Switch pin */
  gpio_init_structure.Pin   = GPIO_PIN_4|GPIO_PIN_3;
  gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull  = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

  HAL_GPIO_Init(GPIOC, &gpio_init_structure);


  //gpio_init_structure.Pin = RF_SW_CTRL3_PIN;
  //HAL_GPIO_Init(RF_SW_CTRL3_GPIO_PORT, &gpio_init_structure);

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
  //HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_RESET);
#endif
  return BSP_ERROR_NONE;
}

/**
  * @brief  DeInit Radio Switch
  * @retval BSP status
  */
int32_t BSP_RADIO_DeInit(void)
{
  RF_SW_CTRL3_GPIO_CLK_ENABLE();
#ifdef DK_TRSWITCH
  /* Turn off switch */
  HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_RESET); 
  
  /* DeInit the Radio Switch pin */
  HAL_GPIO_DeInit(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN);
  HAL_GPIO_DeInit(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN);
  HAL_GPIO_DeInit(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN);
#else
	  /* Turn off switch */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
  //HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_RESET);

  /* DeInit the Radio Switch pin */
  HAL_GPIO_DeInit(GPIOC, GPIO_PIN_4);
  HAL_GPIO_DeInit(GPIOC, GPIO_PIN_3);
  //HAL_GPIO_DeInit(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN);
#endif
  return BSP_ERROR_NONE;
}

/**
  * @brief  Configure Radio Switch.
  * @param  Config: Specifies the Radio RF switch path to be set. 
  *         This parameter can be one of following parameters:
  *           @arg RADIO_SWITCH_OFF
  *           @arg RADIO_SWITCH_RX
  *           @arg RADIO_SWITCH_RFO_LP
  *           @arg RADIO_SWITCH_RFO_HP
  * @retval BSP status
  */
int32_t BSP_RADIO_ConfigRFSwitch(BSP_RADIO_Switch_TypeDef Config)
{
  switch (Config)
  {
    case RADIO_SWITCH_OFF:
    {
			
#ifdef DK_TRSWITCH
      /* Turn off switch */
      HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET);
#else
			//AT_PRINTF("[Weli]entry OFF mode begin \r\n"); 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
#endif
      break;      
    }
    case RADIO_SWITCH_RX:
    {
			
#ifdef DK_TRSWITCH
      HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_SET);
      HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_SET); 
      HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_RESET);
#else
			//AT_PRINTF("[Weli]entry RX mode begin \r\n"); 
      /*Turns On in Rx Mode the RF Switch */
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
#endif
      break;
    }
    case RADIO_SWITCH_RFO_LP:
    {
			

#ifdef DK_TRSWITCH 
      /*Turns On in Tx Low Power the RF Switch */
      HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_SET);
      HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_SET); 
      HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_SET);
#else
			//AT_PRINTF("[Weli]entry LP mode begin \r\n"); 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
			//AT_PRINTF("[Weli]PC3:%d,PC4:%d \r\n",HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3),HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4)); 
#endif
      break;
    }
    case RADIO_SWITCH_RFO_HP:
    {
			
#ifdef DK_TRSWITCH
      /*Turns On in Tx High Power the RF Switch */
      HAL_GPIO_WritePin(RF_SW_CTRL3_GPIO_PORT, RF_SW_CTRL3_PIN, GPIO_PIN_SET);
      HAL_GPIO_WritePin(RF_SW_CTRL1_GPIO_PORT, RF_SW_CTRL1_PIN, GPIO_PIN_RESET); 
      HAL_GPIO_WritePin(RF_SW_CTRL2_GPIO_PORT, RF_SW_CTRL2_PIN, GPIO_PIN_SET);
#else
			//AT_PRINTF("[Weli]entry HP mode begin \r\n"); 
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
#endif
      break;
    }
    default:
      break;    
  }  

  return BSP_ERROR_NONE;
}

/**
  * @brief  Return Board Configuration
  * @retval 
  *  RADIO_CONF_RFO_LP_HP
  *  RADIO_CONF_RFO_LP
  *  RADIO_CONF_RFO_HP
  */
int32_t BSP_RADIO_GetTxConfig(void)
{
  return RADIO_CONF_RFO_HP;
	
}

/**
  * @brief  Get If TCXO is to be present on board
  * @note   never remove called by MW,
  * @retval
  *  RADIO_CONF_TCXO_NOT_SUPPORTED
  *  RADIO_CONF_TCXO_SUPPORTED
  */
int32_t BSP_RADIO_IsTCXO(void)
{
#ifdef RC_WLE_TCXO
	return RADIO_CONF_TCXO_SUPPORTED;
#else
  return RADIO_CONF_TCXO_NOT_SUPPORTED;
#endif
	
}

/**
  * @brief  Get If DCDC is to be present on board
  * @note   never remove called by MW,
  * @retval
  *  RADIO_CONF_DCDC_NOT_SUPPORTED
  *  RADIO_CONF_DCDC_SUPPORTED  
  */
int32_t BSP_RADIO_IsDCDC(void)
{
  return RADIO_CONF_DCDC_SUPPORTED;
}

/**
  * @brief  Return RF Output Max Power Configuration
  * @retval
  *    RADIO_CONF_RFO_LP_MAX_15_dBm for LP mode
  *    RADIO_CONF_RFO_HP_MAX_22_dBm for HP mode
  */
int32_t BSP_RADIO_GetRFOMaxPowerConfig(BSP_RADIO_RFOMaxPowerConfig_TypeDef Config)
{
  int32_t ret;
	
  //if(Config == RADIO_RFO_LP_MAXPOWER)
  //{
  //  ret = RADIO_CONF_RFO_LP_MAX_15_dBm;
  //}
  //else
  {
    ret = RADIO_CONF_RFO_HP_MAX_22_dBm;
  }

  return ret;
}



#include "radio_conf.h"
#include "radio_driver.h"
/***calibration XO begin*****/


#define STORE_ADDRESS ((uint32_t)OTP_AREA_BASE) 
#define ADDITIONAL_DATA_PTR ((uint32_t)0x20006FF0)
#define OTP_HSE_STR_IDX ((uint8_t)0x00)
#define OTP_AREA_SIZE ((uint32_t)1024)

#ifdef __GNUC__
typedef struct __attribute__((packed))
#else
typedef __packed struct
#endif
{
  uint8_t additional_data[5]; /*!< 40 bits of data to fill OTP slot (e.g: address, key..) */
  uint8_t hse_tuning_in;         /*!< Load capacitance to be applied on HSE in pad */
  uint8_t hse_tuning_out;         /*!< Load capacitance to be applied on HSE out pad */
  uint8_t index;              /*!< Structure index */
} OTP_DATA_t;
/***calibration XO end*****/
/*************************function end*********************************/

void BJJA_LM_LoadHSECapacitor()
{
  OTP_DATA_t otp_data;
  uint32_t idx = 0;
  uint8_t check_flag=0x00;
  for (idx = 0; idx < OTP_AREA_SIZE; idx += sizeof(OTP_DATA_t))
  {
    memcpy(&otp_data, (void*)STORE_ADDRESS + idx, sizeof(otp_data));
    if (otp_data.additional_data[0]==0x55 && otp_data.additional_data[1]==0x44 && otp_data.additional_data[2]==0x33 &&
      otp_data.additional_data[3]==0x22 &&otp_data.additional_data[4]==0x11)
    {
      check_flag=1;
      break;
    }
  }
  if(check_flag)
  {
    //APP_PPRINTF("load otp capacitor:%d,%s\r\n",__LINE__,__FUNCTION__);
    SUBGRF_WriteRegister( REG_XTA_TRIM, otp_data.hse_tuning_in );
    SUBGRF_WriteRegister( REG_XTB_TRIM, otp_data.hse_tuning_out );
  }
  else
  {
    //APP_PPRINTF("load default capacitor:%d,%s\r\n",__LINE__,__FUNCTION__);
    SUBGRF_WriteRegister( REG_XTA_TRIM, XTAL_DEFAULT_CAP_VALUE );
    SUBGRF_WriteRegister( REG_XTB_TRIM, XTAL_DEFAULT_CAP_VALUE );
  }
}



/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
