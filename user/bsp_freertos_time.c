#include "bsp_freertos.h"
#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#if 0
TaskHandle_t TaskLED_Handle;
TaskHandle_t TaskKEY_Handle;

TaskHandle_t TaskDeleteLED_Handle;
TaskHandle_t TaskCreateKEY_Handle;

TaskHandle_t TaskKEY_SuspendAndResume_Handle;
TaskHandle_t vTask_KEY_List_GetRunTimeStats_Handle;

TaskHandle_t vTaskLED_GetPriority_Handle;

TaskHandle_t vTask_Critical_Handle;

uint8_t vTask_Priority = 3;

void vTaskLED(void * pvParameters){

	while(1){
			LED_Blue_ON;
			LED_Green_ON;
			vTaskDelay(500);  // 延时500ms
			LED_Blue_OFF;
			LED_Green_OFF;
			vTaskDelay(500);  // 延时500ms
		}
}
void vTaskKEY(void * pvParameters){
	while(1){
		if(! KEY2_Read)
		{
			LED_Red_ON;
//			printf("ListTask begin\r\n");	
		}
		else 
		{
			LED_Red_OFF;
		}
		vTaskDelay(50);  // 延时50ms，提高按键响应速度
	}
}

void vTaskDelete_LED(void * pvParameters){
	// 闪烁10次
	for(int i = 0; i < 10; i++){
		LED_Blue_ON;
		LED_Green_ON;
		vTaskDelay(500);  // 延时500ms
		
		LED_Blue_OFF;
		LED_Green_OFF;
		vTaskDelay(500);  // 延时500ms
	}
	
	// 任务完成后删除自己
	TaskDeleteLED_Handle = NULL;  // 先清空句柄
	vTaskDelete(NULL);  // 删除当前任务
}

void vTaskCreate_KEY(void * pvParameters){
	while(1){	
		if(!KEY1_Read){
			if(TaskDeleteLED_Handle == NULL){ // 防止重复创建
				xTaskCreate(vTaskDelete_LED,"vTaskDelete_LED",256,NULL,5,&TaskDeleteLED_Handle);
			}
			vTaskDelay(300); // 去抖
		}
		vTaskDelay(50);
	}
}


void vTask_KEY_ResumeAndSuspend(void * pvParameters){
//	LED_Red_ON;	
	while(1){	
		if(KEY1_Read){
				vTaskSuspend(TaskLED_Handle);
				//vTaskSuspendAll();
		}
		else{
			vTaskResume(TaskLED_Handle);
			//xTaskResumeAll();
		}

		
		vTaskDelay(50);
	}
}

//11.2 vTaskList  vTaskGetRunTimeStats配置环境有点复杂
#if 0
void vTask_KEY_List_GetRunTimeStats(void * pvParameters){
	uint8_t pcWriteBuffer[500];
	while(1){	
		if(!KEY1_Read){
				printf("ListTask begin\r\n");
				vTaskList((char *)&pcWriteBuffer);
				printf("%s\r\n",pcWriteBuffer);
				printf("GetRunTimeTask Begin\r\n");
				vTaskGetRunTimeStats((char*)&pcWriteBuffer);
				printf("%s\r\n",pcWriteBuffer);
			}
			vTaskDelay(300); // 去抖
		}
		vTaskDelay(50);
	

}
#endif

//11.3 configMAX_PRIORITIES 设置优先级
void vTaskLED_GetPriority(void * pvParameters){

	while(1){
		if(!KEY1_Read){

			vTaskDelay(500);  // 延时500ms
			
			vTaskPrioritySet(vTaskLED_GetPriority_Handle,vTask_Priority);
			vTask_Priority = uxTaskPriorityGet(vTaskLED_GetPriority_Handle);
			printf("origin priority = %d\r\n",vTask_Priority);
			vTask_Priority++;
		
			vTaskPrioritySet(vTaskLED_GetPriority_Handle,vTask_Priority);
			vTask_Priority = uxTaskPriorityGet(vTaskLED_GetPriority_Handle);
			printf("NOW priority = %d\r\n",vTask_Priority);
		
			LED_Blue_OFF;
			LED_Green_OFF;
			vTaskDelay(500);  // 延时500ms
		
	}
			LED_Blue_ON;
			LED_Green_ON;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_15){
		printf("run exti,vTask_Priority set as 2\r\n");
		vTask_Priority = 2;
	
	}

}

void vTask_Critical(void * pvParameters){
		while(1){
		if(! KEY1_Read)
		{
			for(uint8_t i = 0; i < 10;i++)
			{
				printf("key1 run %d times\r\n",i);	
				vTaskDelay(200);
			}

		}
		else if(! KEY2_Read)
		{
			taskENTER_CRITICAL();
			for(uint8_t i = 0; i < 10;i++)
			{
				printf("key2 run %d times\r\n",i);	
				vTaskDelay(100/portTICK_PERIOD_MS);
			
			}
			taskEXIT_CRITICAL();
			vTaskDelay(10);

		}
		vTaskDelay(50);  // 延时50ms，提高按键响应速度
	}
}



void Task_Create(void){
	//xTaskCreate(vTaskLED,"vTaskLED",200,NULL,3,&TaskLED_Handle);
	
	//xTaskCreate(vTaskKEY,"vTaskKEY",200,NULL,4,&TaskKEY_Handle);
	
//	xTaskCreate(vTaskCreate_KEY,"vTaskCreate_KEY",200,NULL,4,&TaskCreateKEY_Handle);
	
//	xTaskCreate(vTaskDelete_LED,"vTaskDelete_LED",200,NULL,5,&TaskDeleteLED_Handle);

	//xTaskCreate(vTask_KEY_ResumeAndSuspend,"vTask_KEY_ResumeAndSuspend",200,NULL,5,&TaskKEY_SuspendAndResume_Handle);

	//xTaskCreate(vTask_KEY_List_GetRunTimeStats,"vTask_KEY_List_GetRunTimeStats",200,NULL,5,&vTask_KEY_List_GetRunTimeStats_Handle);

	//xTaskCreate(vTaskLED_GetPriority,"vTaskLED_GetPriority",200,NULL,4,&vTaskLED_GetPriority_Handle);
	xTaskCreate(vTask_Critical,"vTask_Critical",200,NULL,4,&vTask_Critical_Handle);


}
#endif