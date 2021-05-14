/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "../LoRa_main_cpp/LoRa_main_file.h"
#include <FlashPROM.h>

#include <Device_relay.h>
#include <Clock_channel.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define BAND	43325E4
#define BAND	43455E4

#define PHYTOLAMP
#define PUMP_VENT
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim2;
/* USER CODE BEGIN PV */


RTC_TimeTypeDef next_time;
#define AMT_CHANNEL 2
struct clock_channel_t all_channel[AMT_CHANNEL];
struct clock_channel_t* channel1 = &all_channel[0];
struct clock_channel_t* channel2 = &all_channel[1];

RTC_TimeTypeDef time_channel1_inclusion = {.Hours=0, .Minutes=0, .Seconds=10};
RTC_TimeTypeDef time_channel1_shutdown = {.Hours=6, .Minutes=0, .Seconds=10};
RTC_TimeTypeDef time_channel2_inclusion = {.Hours=0, .Minutes=0, .Seconds=10};
RTC_TimeTypeDef time_channel2_shutdown = {.Hours=6, .Minutes=0, .Seconds=00};

//#define CLEAR_TIME
#if defined (CLEAR_TIME)
RTC_TimeTypeDef clear_time = {.Hours=0, .Minutes=10, .Seconds=30};
#endif

RTC_TimeTypeDef time_synchronization = {.Hours=23, .Minutes=59, .Seconds=30};
struct relay_t relay[AMT_CHANNEL];
bool relay_invert[AMT_CHANNEL];

#if defined( DEBUG )
uint8_t hour = 0, min = 0, sec = 0;
#endif

uint8_t build_hour = 15, build_min = 19, build_sec = 0;

uint8_t STADY_CONACT_NUMBER = 0;

DevicesDataTypeDef devices_data;

uint8_t LoRa_begin_result = 0;

uint8_t tim4 = 0;

uint16_t exti5_10 = 0;
uint16_t exti2 = 0;

uint16_t cnt_task_1 = 0;
uint16_t cnt_task_2 = 0;
uint16_t cnt_task_3 = 0;

volatile bool end_contact = false;
volatile bool change_state = false;

uint32_t control_module_id_and_channel[BUFFSIZE] = {0x00000000, 0x00000000};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM2_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */
void LoRa_sleep();
void DevicesGetValues();
void Main_cpp(DevicesDataTypeDef* devices_data);
void Contact_group_control_module();
bool Init_lora_module(SPI_HandleTypeDef *spi);
void Send_registration_packet();
void Get_control_module_info_from_main(uint32_t* id_main);
uint8_t LoRa_begin(uint64_t frequency, bool paboost, uint8_t signal_power, uint8_t SF, uint64_t SBW, uint8_t sync_word);
uint8_t Begin_lora_module(uint64_t frequency, bool paboost, uint8_t signal_power, uint8_t SF, uint64_t SBW, uint8_t sync_word);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void alarm_rtc();

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM4) //check if the interrupt comes from TIM1
	{
		tim4++;
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  relay_invert[0] = relay_invert[1] = false;

#if defined( DEBUG )
	RTC_TimeTypeDef time;
#endif

  Read_control_module_info_from_flash(control_module_id_and_channel);
  Get_control_module_info_from_main(control_module_id_and_channel);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  // Подготовка устройств

  relay[0] = relay_init(RELAY1_PIN_GPIO_Port, RELAY1_PIN_Pin, relay_invert[0]);
  relay[1] = relay_init(RELAY2_PIN_GPIO_Port, RELAY2_PIN_Pin, relay_invert[1]);

  *channel1 = clock_channel_init(&relay[0], time_channel1_inclusion, time_channel1_shutdown);
  *channel2 = clock_channel_init(&relay[1], time_channel2_inclusion, time_channel2_shutdown);

  channel1->deviation_sec = 2;
  channel2->deviation_sec = 2;

  channel1->state = true;
  channel2->state = true;

  relay_set_state(channel1->relay, channel1->state);
  relay_set_state(channel2->relay, channel2->state);

  // Запуск LoRa
  Init_lora_module(&hspi1);
  LoRa_begin_result = Begin_lora_module(BAND, true, 14, 8, 250E3, 0x4A);
  //LoRa_begin_result = LoRa_begin(BAND, true, 14, 11, 125E3, 0x4A)
  if(LoRa_begin_result == 0) {
	  for (int i = 0; i < 5; ++i) {
		  HAL_GPIO_TogglePin(LED1_PIN_GPIO_Port, LED1_PIN_Pin);
		  HAL_GPIO_TogglePin(LED2_PIN_GPIO_Port, LED2_PIN_Pin);
		  HAL_GPIO_TogglePin(LED3_PIN_GPIO_Port, LED3_PIN_Pin);
		  HAL_Delay(500);
	  }
	  while(LoRa_begin_result != 0) {
		  LoRa_begin_result = Begin_lora_module(BAND, true, 14, 8, 250E3, 0x4A);
			  HAL_GPIO_WritePin(LED1_PIN_GPIO_Port, LED1_PIN_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(LED2_PIN_GPIO_Port, LED2_PIN_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(LED3_PIN_GPIO_Port, LED3_PIN_Pin, GPIO_PIN_RESET);
	  }
  }
  HAL_GPIO_WritePin(LED1_PIN_GPIO_Port, LED1_PIN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED2_PIN_GPIO_Port, LED2_PIN_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED3_PIN_GPIO_Port, LED3_PIN_Pin, GPIO_PIN_RESET);

  // Запуск устройств
  // Перенести установку времени в ESP32!!!, как и запуск на регистрацию
  RTC_TimeTypeDef null_time = {.Hours=build_hour, .Minutes=build_min, .Seconds=build_sec};
  HAL_RTC_SetTime(&hrtc, &null_time, RTC_FORMAT_BIN);
  alarm_rtc();
  DevicesGetValues();
  Main_cpp(&devices_data);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
#if defined( DEBUG )
	if (HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN) == HAL_OK) {
		hour = time.Hours;
		min = time.Minutes;
		sec = time.Seconds;
#if defined ( CLEAR_TIME )
	if(hour == clear_time.Hours && min == clear_time.Minutes && sec == clear_time.Seconds) {
		HAL_RTC_SetDate(&hrtc, &null_date, RTC_FORMAT_BIN);
		HAL_RTC_SetTime(&hrtc, &null_time, RTC_FORMAT_BIN);
		alarm_rtc();
	}
#endif // CLEAR_TIME
	}
	HAL_Delay(1);
#endif // DEBUG
	if(change_state) {
		DevicesGetValues();
		Main_cpp(&devices_data);
		change_state = false;
	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV4;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 72;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LORA_NSS_Pin|LED1_PIN_Pin|LED2_PIN_Pin|LED3_PIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LORA_RESET_Pin|RELAY2_PIN_Pin|RELAY1_PIN_Pin|RELAY_NS_PIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LORA_NSS_Pin LED1_PIN_Pin LED2_PIN_Pin LED3_PIN_Pin */
  GPIO_InitStruct.Pin = LORA_NSS_Pin|LED1_PIN_Pin|LED2_PIN_Pin|LED3_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LORA_DIO1_Pin LORA_DIO0_Pin */
  GPIO_InitStruct.Pin = LORA_DIO1_Pin|LORA_DIO0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LORA_RESET_Pin RELAY2_PIN_Pin RELAY1_PIN_Pin RELAY_NS_PIN_Pin */
  GPIO_InitStruct.Pin = LORA_RESET_Pin|RELAY2_PIN_Pin|RELAY1_PIN_Pin|RELAY_NS_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin== GPIO_PIN_2) {
    exti2++;
    //HAL_ResumeTick();
    Contact_group_control_module();
  } else if(GPIO_Pin== GPIO_PIN_10){
    exti5_10++;
    //HAL_ResumeTick();
    Contact_group_control_module();
  } else{
    __NOP();
  }
}

void alarm_rtc() {
	RTC_AlarmTypeDef alarm = {.Alarm=1};
	alarm.AlarmTime = find_alarm_clock(all_channel, AMT_CHANNEL);

	for(int i = 0; i < AMT_CHANNEL; ++i)
		check_state_by_RTC(&all_channel[i]);
	//HAL_RTC_SetAlarm(&hrtc, &alarm, RTC_FORMAT_BIN);
	HAL_RTC_SetAlarm_IT(&hrtc, &alarm, RTC_FORMAT_BIN);
#if defined(DEBUG)
	next_time = alarm.AlarmTime;
#endif
	change_state = true;
}

void DevicesGetValues() {

	if(relay[0].state)
		devices_data.lamp_d1 = 4095;
	else
		devices_data.lamp_d1 = 0;
	if(relay[1].state)
		devices_data.lamp_d2 = 4095;
	else
		devices_data.lamp_d2 = 0;

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {

  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
