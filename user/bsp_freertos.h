#ifndef __BSP_FREERTOS_H_
#define __BSP_FREERTOS_H_
#include "stm32f1xx.h"


#define LED_Blue_ON HAL_GPIO_WritePin(GPIOA, LED_BLUE_Pin, GPIO_PIN_SET)
#define LED_Green_ON HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_SET)
#define LED_Red_ON HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET)

#define LED_Blue_OFF HAL_GPIO_WritePin(GPIOA, LED_BLUE_Pin, GPIO_PIN_RESET)
#define LED_Green_OFF HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_RESET)
#define LED_Red_OFF HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET)

#define KEY1_Read HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)
#define KEY2_Read HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)

/*
vTask_LED :À¶ÂÌµÆÁÁ
vTask_KEY :ºìµÆÁÁ
Éæ¼°£ºxTaskCreate,vTaskStartScheduler
*/

void Task_Create(void);
void vTask_LED(void * pvParameters);
void vTask_KEY(void * pvParameters);

//vTaskDelete
//vTaskDelete_LED µÆÈÎÎñÉ¾³ý
//vTask
void vTaskDelete_LED(void * pvParameters);
void vTaskCreate_KEY(void * pvParameters);


//vTaskResume
//vTaskSuspend
void vTask_KEY_ResumeAndSuspend(void * pvParameters);

//11.2 vTaskList  vTaskGetRunTimeStats
void vTask_KEY_List_GetRunTimeStats(void * pvParameters);

//11.4 vTaskCritical
void vTask_Critical(void * pvParameters);

#endif 