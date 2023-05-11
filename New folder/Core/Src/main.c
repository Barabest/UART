/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t RxBuffer[20];
uint8_t TxBuffer[40];
uint8_t UI[500];
uint8_t CheckLedMenu=0;
uint8_t LED_On = 1;
uint8_t Hz=1;
uint8_t press=0;
uint8_t OK = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void DummyTask();
void UARTInterruptConfig();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  UARTInterruptConfig();
  sprintf((char*)UI,"\r\n------------- Welcome to main menu ------------\r\n\n"
		  "**Please enter information to select a function.**\r\n"
		  "Select 0 To LED Control\r\n"
		  "Select 1 To Button Status\r\n"
		  "==============================================\r\n"
		  "Enter you select this one : \r\n");
  HAL_UART_Transmit_IT(&huart2, UI, strlen((char*)UI));
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  static uint32_t timestamp =0;
	  if(HAL_GetTick()>timestamp &&LED_On==1){
		  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
		  timestamp = HAL_GetTick()+500/Hz; //500ms=1Hz
	  }
	  else if (LED_On==0){
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 57600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void UARTInterruptConfig(){
	HAL_UART_Receive_IT(&huart2, RxBuffer, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart2){
		OK = 1;
		if(CheckLedMenu==0 && OK == 1){
		if(RxBuffer[0] == '0'){
			sprintf((char*)TxBuffer,"%s\r\n----------- Welcome to LED Control -----------\r\n\n" //mode led
					"**Please enter information to select a function.**\r\n"
					"Select a To Speed Up +1Hz\r\n"
					"Select s To Speed Down -1Hz\r\n"
					"Select d To On/OFF\r\n"
					"Select x To Back to main menu\r\n"
					"==================================================\r\n"
					"Enter you select this one : ",RxBuffer);
			HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
			CheckLedMenu=1;
			OK = 0;
		}
		else if(RxBuffer[0]=='1'){
					sprintf((char*)TxBuffer,"%s\r\n---------- Welcome to Button Status -----------\r\n\n" //mode button
										"**Please enter information to select a function.**\r\n"
										"Select x To Back to main menu\r\n"
										"Button Status is UNPRESS\r\n"
										"================================================\r\n"
										"Enter you select this one : \r\n\n",RxBuffer);
								HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
								CheckLedMenu=2;
								OK=0;
				}
		else{
			sprintf((char*)UI,"%s\r\n**Please select to choice**\r\n" //check choice to select incorrect
				  "Select 0 To LED Control\r\n"
				  "Select 1 To Button Status\r\n"
				  "=================================================\r\n"
				  "Enter you select this one : \r\n",RxBuffer);
			HAL_UART_Transmit_IT(&huart2, UI, strlen((char*)UI));
			}
		}
		if(CheckLedMenu == 1 && OK == 1){ //check choice menu led

			if(RxBuffer[0] == 'a'){
				Hz=Hz+1;
				sprintf((char*)TxBuffer,"%s\r\nLED Current is %d\r\n"
						"Enter you select this one : "
						,RxBuffer,Hz);
				HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
			}
			else if(RxBuffer[0] == 's'){
				Hz=Hz-1;
				sprintf((char*)TxBuffer,"%s\r\nLED Current is %d\r\n"
						"Enter you select this one : "
						,RxBuffer,Hz);
				HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
			}
			else if(RxBuffer[0] == 'd'){
				if(LED_On==0){
					LED_On=1;
					sprintf((char*)TxBuffer,"%s\r\nLED ON\r\n"
							"Enter you select this one : ",RxBuffer);
					HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
				}
				else if(LED_On==1){
					LED_On=0;
					sprintf((char*)TxBuffer,"%s\r\nLED OFF\r\n"
							"Enter you select this one : ",RxBuffer);
					HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
				}
			}
			else if(RxBuffer[0] == 'x'){
				 sprintf((char*)UI,"%s\r\n-------------- Welcome to main menu -------------\r\n\n"
						  "**Please enter information to select a function.**\r\n"
						  "Select 0 To LED Control\r\n"
						  "Select 1 To Button Status\r\n"
						  "=================================================\r\n"
						  "Enter you select this one : ",RxBuffer);
				  HAL_UART_Transmit_IT(&huart2, UI, strlen((char*)UI));
				  CheckLedMenu=0;
			}
			else{
				sprintf((char*)UI,"%s\r\n**Please select to choice**\r\n" //check choice to select incorrect
						"Select a To Speed Up +1Hz\r\n"
						"Select s To Speed Down -1Hz\r\n"
						"Select d To On/OFF\r\n"
						"Select x To Back to main menu\r\n"
						"==================================================\r\n"
						"Enter you select this one : ",RxBuffer);
				HAL_UART_Transmit_IT(&huart2, UI, strlen((char*)UI));
				}
		}
		if(CheckLedMenu == 2 && OK == 1){
		if(RxBuffer[0] == 'x'){ //check choice button
								 sprintf((char*)UI,"%s\r\n-------------- Welcome to main menu -------------\r\n\n"
										  "**Please enter information to select a function.**\r\n"
										  "Select 0 To LED Control\r\n"
										  "Select 1 To Button Status\r\n"
										  "================================================\r\n"
										  "Enter you select this one : ",RxBuffer);
								  HAL_UART_Transmit_IT(&huart2, UI, strlen((char*)UI));
								  CheckLedMenu=0;
								  OK=0;
							}
		else{
			sprintf((char*)UI,"%s\r\n**Please select to choice**\r\n" //check choice to select incorrect
					"Select x To Back to main menu\r\n"
					"Button Status is UNPRESS\r\n"
					"================================================\r\n"
					"Enter you select this one : ",RxBuffer);
			HAL_UART_Transmit_IT(&huart2, UI, strlen((char*)UI));
					}
		}
		HAL_UART_Receive_IT(&huart2, RxBuffer, 1);
	}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){ //button ex interrupt
	if(GPIO_Pin == GPIO_PIN_13){
		if(CheckLedMenu == 2)press = press+1;
		if(CheckLedMenu == 2 && press == 1){
			sprintf((char*)TxBuffer,"%s\r\n---------- Welcome to Button Status ----------\r\n\n"
								"**Please enter information to select a function.**\r\n"
								"Select x To Back to main menu\r\n"
								"Button Status is PRESS\r\n"
								"================================================\r\n"
								"Enter you select this one : ",RxBuffer);
						HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
				}
		else if(CheckLedMenu == 2 && press == 2){
			sprintf((char*)TxBuffer,"%s\r\n---------- Welcome to Button Status ----------\r\n\n"
								"**Please enter information to select a function.**\r\n"
								"Select x To Back to main menu\r\n"
								"Button Status is UNPRESS\r\n"
								"================================================\r\n"
								"Enter you select this one : ",RxBuffer);
						HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
			press=0;
		}
	}
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
