/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KBD_C2_Pin GPIO_PIN_0
#define KBD_C2_GPIO_Port GPIOF
#define KBD_C1_Pin GPIO_PIN_1
#define KBD_C1_GPIO_Port GPIOF
#define KBD_C3_Pin GPIO_PIN_2
#define KBD_C3_GPIO_Port GPIOF
#define KBD_C4_Pin GPIO_PIN_4
#define KBD_C4_GPIO_Port GPIOF
#define LED0_Pin GPIO_PIN_9
#define LED0_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOF
#define Shot_Control_Pin GPIO_PIN_2
#define Shot_Control_GPIO_Port GPIOC
#define Charge_Control_Pin GPIO_PIN_3
#define Charge_Control_GPIO_Port GPIOA
#define ButtonSteering_Pin GPIO_PIN_10
#define ButtonSteering_GPIO_Port GPIOB
#define LCD_BL_Pin GPIO_PIN_15
#define LCD_BL_GPIO_Port GPIOB
#define OMV_TX_Pin GPIO_PIN_6
#define OMV_TX_GPIO_Port GPIOC
#define OMV_RX_Pin GPIO_PIN_7
#define OMV_RX_GPIO_Port GPIOC
#define KBD_R4_Pin GPIO_PIN_8
#define KBD_R4_GPIO_Port GPIOA
#define USB_TX_Pin GPIO_PIN_9
#define USB_TX_GPIO_Port GPIOA
#define USB_RX_Pin GPIO_PIN_10
#define USB_RX_GPIO_Port GPIOA
#define TopSteering_Pin GPIO_PIN_15
#define TopSteering_GPIO_Port GPIOA
#define SCR_TX_Pin GPIO_PIN_10
#define SCR_TX_GPIO_Port GPIOC
#define SCR_RX_Pin GPIO_PIN_11
#define SCR_RX_GPIO_Port GPIOC
#define KBD_R3_Pin GPIO_PIN_2
#define KBD_R3_GPIO_Port GPIOD
#define KBD_R1_Pin GPIO_PIN_6
#define KBD_R1_GPIO_Port GPIOD
#define KBD_R2_Pin GPIO_PIN_15
#define KBD_R2_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
