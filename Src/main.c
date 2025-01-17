/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define PI (3.1415926f)
#include "ws2812.h"

#include "cmath"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t makeTriangle(uint16_t index)
{
	uint8_t rtn = (uint8_t)(index&0xff);
	if(index & 0x100)
	{
		rtn = 255-rtn;
	}

	return rtn;
}

uint8_t makeSmoothChange(uint16_t index)
{
	uint8_t rtn = (uint8_t)(index&0xff);
	if(index & 0x100)
	{
		rtn = 255-rtn;
	}
	
	double vtan = tan((	((double)((int)(rtn))-110) /300.f)*PI);
	vtan = (vtan+2.3)*10;
	vtan = vtan>255?255:vtan;
	vtan = vtan<0?0:vtan;
	rtn = (uint8_t)((int)vtan);
	return rtn;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t R=0xff,G=0xf,B=0xf;
	uint16_t count = 0;
	uint8_t color_stage = 0;
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
  MX_DMA_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	WS28xx_TypeStructInit();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		count++;
		if(count%512==0) color_stage++;
		R=0;G=0;B=0;
		switch(color_stage){
			case 0:
				R = makeSmoothChange(count);
				break;
			case 1:
				G = makeSmoothChange(count);
				break;
			case 2:
				B = makeSmoothChange(count);
				break;
			case 3:
				WS28xx.SetALLColor_RGB (0,0,0);WS28xx.show();HAL_Delay(200);
				WS28xx.SetALLColor_RGB (255,128,0);WS28xx.show ();HAL_Delay(80);
				WS28xx.SetALLColor_RGB (0,0,0);WS28xx.show();HAL_Delay(200);
				WS28xx.SetALLColor_RGB (255,128,0);WS28xx.show ();HAL_Delay(80);
				WS28xx.SetALLColor_RGB (0,0,0);WS28xx.show();HAL_Delay(500);
			
				WS28xx.SetALLColor_RGB (0,0,0);WS28xx.show();HAL_Delay(200);
				WS28xx.SetALLColor_RGB (0,255,128);WS28xx.show ();HAL_Delay(80);
				WS28xx.SetALLColor_RGB (0,0,0);WS28xx.show();HAL_Delay(200);
				WS28xx.SetALLColor_RGB (0,255,128);WS28xx.show ();HAL_Delay(80);
				WS28xx.SetALLColor_RGB (0,0,0);WS28xx.show();HAL_Delay(500);
			
				WS28xx.SetALLColor_RGB (0,0,0);WS28xx.show();HAL_Delay(200);
				WS28xx.SetALLColor_RGB (128,0,255);WS28xx.show ();HAL_Delay(80);
				WS28xx.SetALLColor_RGB (0,0,0);WS28xx.show();HAL_Delay(200);
				WS28xx.SetALLColor_RGB (128,0,255);WS28xx.show ();HAL_Delay(80);
				WS28xx.SetALLColor_RGB (0,0,0);WS28xx.show();HAL_Delay(500);
			
				color_stage = 0;
			
				break;
			
			default:
				color_stage = 0;
		}
		WS28xx.SetALLColor_RGB (R,G,B);	//R,G,B
		WS28xx.show ();	
		
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		HAL_Delay(1);
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
