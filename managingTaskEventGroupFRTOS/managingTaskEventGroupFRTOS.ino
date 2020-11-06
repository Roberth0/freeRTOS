#include <Arduino_FreeRTOS.h>
#include "event_groups.h"

#define RED 7
#define BLUE 8
#define YELLOW 9

EventGroupHandle_t xEventGroup;

const TickType_t xDelay500ms = pdMS_TO_TICKS(500);

#define TASK1_BIT (1UL << 0UL)
#define TASK2_BIT (1UL << 1UL)
#define TASK3_BIT (1UL << 2UL)

void setup(){
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  xEventGroup = xEventGroupCreate();
  xTaskCreate(xTask1, "Task 1", 100, NULL, 1, NULL);
  xTaskCreate(xTask2, "Task 2", 100, NULL, 1, NULL);
  xTaskCreate(xTask3, "Task 3", 100, NULL, 1, NULL);
  xTaskCreate(OutputTask, "Output task", 100, NULL, 1, NULL);

}
void xTask1(void *pvParameters){
  while(1){
    xEventGroupSetBits(xEventGroup, TASK1_BIT);
    vTaskDelay(xDelay500ms);

  }
}
void xTask2(void *pvParameters){
  while(1){
    xEventGroupSetBits(xEventGroup, TASK2_BIT);
    vTaskDelay(xDelay500ms);

  }
}
void xTask3(void *pvParameters){
  while(1){
    xEventGroupSetBits(xEventGroup, TASK3_BIT);
    vTaskDelay(xDelay500ms);

  }
}
void OutputTask(void *pvParameters){
    const EventBits_t xBitsToWaitFor = (TASK1_BIT | TASK2_BIT | TASK3_BIT );
    EventBits_t xEventGroupValue;
  while(1){
    xEventGroupValue = xEventGroupWaitBits(xEventGroup, xBitsToWaitFor, pdTRUE, pdTRUE, portMAX_DELAY);
    if (xEventGroupValue & TASK1_BIT != 0){
      digitalWrite(RED, digitalRead(RED)^1);
    }
    if (xEventGroupValue & TASK2_BIT != 0){
      digitalWrite(BLUE, digitalRead(BLUE)^1);
    }
    if (xEventGroupValue & TASK3_BIT != 0){
      digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    }
    



  }
}
void loop (){
}
