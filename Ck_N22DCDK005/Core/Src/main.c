/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "string.h"
#include "stdio.h"
//khai bao chan cam
#define LCD_RS_Pin 		GPIOB,GPIO_PIN_5
#define LCD_E_Pin 		GPIOB,GPIO_PIN_4
#define LCD_D4_Pin 		GPIOB,GPIO_PIN_3
#define LCD_D5_Pin 		GPIOB,GPIO_PIN_2
#define LCD_D6_Pin 		GPIOB,GPIO_PIN_1
#define LCD_D7_Pin 		GPIOB,GPIO_PIN_0


#define LCD_Set_Pin(LCD_Pin) 			HAL_GPIO_WritePin(LCD_Pin,GPIO_PIN_SET)
#define LCD_Reset_Pin(LCD_Pin) 			HAL_GPIO_WritePin(LCD_Pin,GPIO_PIN_RESET)
#define LCD_Write_Pin(LCD_Pin,value) 		HAL_GPIO_WritePin(LCD_Pin,value)
#define LCD_Delay_ms(time)				HAL_Delay(time)
#define LCD_GetBit(value,bit)			((value>>bit) & 1)

#define LCD_Send_cmd(Value)				LCD_Write_8bit(Value,0)
#define LCD_Send_cmd_4bit(Value)		LCD_Write_4bit(Value,0)
#define LCD_Send_data(Value)			LCD_Write_8bit(Value,1)
#define LCD_SetCursor(row,col)			LCD_Send_cmd(0x80+(row*64)+col)
#define LCD_clear()						LCD_Write_8bit(0x01,0)
// Ham gui du lieu 4-bit toi LCD
void LCD_Write_4bit(uint8_t value, uint8_t cmd_data) {
	LCD_Write_Pin(LCD_RS_Pin, cmd_data); // Xac dinh la lenh (0) hay du lieu(1)
	LCD_Set_Pin(LCD_E_Pin);//Kich hoat chan E
	LCD_Delay_ms(1);
	//Gui tung bit toi cac chan D4-D7
	LCD_Write_Pin(LCD_D4_Pin, LCD_GetBit(value,0));
	LCD_Write_Pin(LCD_D5_Pin, LCD_GetBit(value,1));
	LCD_Write_Pin(LCD_D6_Pin, LCD_GetBit(value,2));
	LCD_Write_Pin(LCD_D7_Pin, LCD_GetBit(value,3));
	LCD_Delay_ms(1);
	LCD_Reset_Pin(LCD_E_Pin);//Tat chan E
	LCD_Delay_ms(1);
}
// ham gui du lieu 8-bit toi LCD
void LCD_Write_8bit(uint8_t value, uint8_t cmd_data) {
	LCD_Write_4bit((value >> 4) & 0x0F, cmd_data);//Gui 4-bit cao
	LCD_Write_4bit(value & 0x0F, cmd_data);//Gui 4-bit thap
}

void LCD_Send_string(char *ptr) {
	int i;
	int len;
	len = strlen(ptr); // tinh do dai chuoi
	for (i = 0; i < len; i++) {
		LCD_Write_8bit(ptr[i], 1); // gui tung ky tu len LCD
	}
}
void LCD_init() {
	LCD_Send_cmd_4bit(0x03); //Che do khoi tao LCD
	LCD_Delay_ms(5);
	LCD_Send_cmd_4bit(0x03);
	LCD_Delay_ms(1);
	LCD_Send_cmd_4bit(0x03);
	LCD_Delay_ms(1);
	LCD_Send_cmd_4bit(0x02); // Chuyen ve che do 4-bit
	LCD_Delay_ms(1);
	LCD_Send_cmd(0x28); //4-bit, 2 dong, fort 5x8
	LCD_Delay_ms(1);
	LCD_Send_cmd(0x0C); //Bat hien thi, tat con tro
	LCD_Delay_ms(1);
}
uint32_t adc_val; // Gia tri doc tu ADC
char temp_str[16]; // CHuoi hien thi nhiet do
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
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
int a = 2;
int b = 3;


    //HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);

uint32_t Read_ADC_Value(void) {
    uint32_t adcValue = 0;
    HAL_ADC_Start(&hadc1); // Start Chuyen doi ADC
    if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK) {
        adcValue = HAL_ADC_GetValue(&hadc1); // Lay gia trị ADC
    }
    HAL_ADC_Stop(&hadc1); // Stop ADC
    return adcValue;
}


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) { //Ham ngat ngoai
	if ( GPIO_Pin == GPIO_PIN_1) { // Nut Start de hoat dong STM32
		 a = 1;
	} else if ( GPIO_Pin == GPIO_PIN_2) { // Nut Stop de Ngat hoat dong STM32
		a = 0;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) { // Ham timer
	if ( a == 1) { // start thi den Pin_13 se nhay theo
	UNUSED(htim);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
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
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  LCD_init();

  char uartBuf[50];    // Bộ đệm để lưu dữ liệu gửi qua UART
     uint32_t adcValue = 0; // Luu gia tri doc tu ADC
     float voltage = 0.0; // Luu gia tri dien ap
     float temperature = 0.0; // Luu gia tri nhiet do
     HAL_TIM_Base_Start_IT(&htim2); // Start tim2 va Mode ngat
     LCD_init(); //Khoi tao man hinh LCD
     char rx_data; // Luu du lieu nhan tu UART


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (HAL_UART_Receive(&huart1, (uint8_t*)&rx_data, 1, 1000) == HAL_OK) {
	     		if ( rx_data == '8') { // Start Giao dien
	     			a = 1;
	     		} else if ( rx_data == '9') { //Stop Giao dien
	     			a = 0;
	     		} else if ( rx_data == '0') {
	     			__HAL_TIM_SET_AUTORELOAD(&htim2,499);
	     			__HAL_TIM_SET_COUNTER(&htim2,0);
	     		} else if ( rx_data == '1') {
	     			__HAL_TIM_SET_AUTORELOAD(&htim2,999);
	     			__HAL_TIM_SET_COUNTER(&htim2,0);
	     	} else if ( rx_data == '2') {
     			__HAL_TIM_SET_AUTORELOAD(&htim2,1999);
     			__HAL_TIM_SET_COUNTER(&htim2,0);
	     	}
	  }
	  if ( a == 1 || b == 4) { // Neu gia trị a==1 thi se thoai man dieu kien va kich hoạc trong ngoặc
	  adcValue = Read_ADC_Value(); // doc giá trị ADC
	        voltage = (adcValue * 3.3) / 4095.0; //Dien tu ADC
	        temperature = voltage * 100;        //Nhiet do tu LM35

	        sprintf(uartBuf, "%.2f\r\n", temperature);// dinh dang chuoi nhiet do de hien thi va gui qua UART
	        HAL_UART_Transmit(&huart1, (uint8_t*)uartBuf, strlen(uartBuf),1000);//Gui chuoi qua UART1
	        //Dinh dang chuoi nhiet do cho LCD
	        char lcdBuf[16];
	        sprintf(lcdBuf, "Nhiet Do: %.2f", temperature);
	        LCD_SetCursor(0, 0);
	        LCD_Send_string(lcdBuf);
	        HAL_Delay(1000);
	        if (temperature > 16.0 && temperature < 32.0) { // < 20% (80°C * 0.2)
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);  // Chỉ PB9 sáng
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	            LCD_clear();
	            LCD_SetCursor(0,0);
	            LCD_Send_string("Nhiet do tot");
	        } else if (temperature > 32.0 && temperature < 48.0 ) { // 20-40% (80°C * 0.4)
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET); // PB9, PB10 sáng
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	            LCD_clear();
	            LCD_SetCursor(0,0);
	            LCD_Send_string("Nhiet do kha on");
	        } else if (temperature > 48.0 && temperature < 64.0) { // 40-60% (80°C * 0.6)
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET); // PB9, PB10, PB11 sáng
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	            LCD_clear();
	            LCD_SetCursor(0,0);
	            LCD_Send_string("Nhiet do bat on");
	        } else if (temperature > 64.0 && temperature < 80.0) { // 60-80% (80°C * 0.8)
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);// Tất cả PB9-PB12 sáng
	            LCD_clear();
	            LCD_SetCursor(0,0);
	            LCD_Send_string("Nhiet do qua muc");
	        } else if (temperature > 80.0) {
	            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9); // Tất cả đèn nhấp nháy
	            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
	            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
	            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
	            LCD_clear();
	            LCD_SetCursor(0,0);
	            LCD_Send_string("Qua Nhietttt!!");
	        }

	        HAL_Delay(500); // Chu kỳ đc ADC
} else if ( a == 0 || b == 5) {
	LCD_clear();//xoa man LCD
	LCD_SetCursor(0,0);
    LCD_Send_string("Stop system");
    HAL_Delay(500);
}
HAL_Delay(500); // Chu kỳ đc ADC

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  htim2.Init.Prescaler = 8000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
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
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D7_Pin|D6_Pin|D5_Pin|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_15
                          |D4_Pin|E_Pin_Pin|RS_Pin_Pin|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D7_Pin D6_Pin D5_Pin PB10
                           PB11 PB12 PB13 PB15
                           D4_Pin E_Pin_Pin RS_Pin_Pin PB9 */
  GPIO_InitStruct.Pin = D7_Pin|D6_Pin|D5_Pin|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_15
                          |D4_Pin|E_Pin_Pin|RS_Pin_Pin|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
