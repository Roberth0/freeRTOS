#include <Arduino_FreeRTOS.h>
#include "event_groups.h"

#define RED 7
#define BLUE 8
#define YELLOW 9

#define TASKA_BIT (1UL<<0UL)
#define TASKB_BIT (1UL<<1UL)
#define TASKC_BIT (1UL<<2UL)

EventGroupHandle_t xEventGroup;
const TickType_t xDelay500ms = pdMS_TO_TICKS(50);

EventBits_t allSyncBits = (TASKA_BIT | TASKB_BIT | TASKC_BIT);

void setup(){

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  xEventGroup = xEventGroupCreate();
  xTaskCreate(xTaskA, "Task a", 100, NULL, 1, NULL);
  xTaskCreate(xTaskB, "Task b", 100, NULL, 1, NULL);
  xTaskCreate(xTaskC, "Task c", 100, NULL, 1, NULL);
  

} 
void xTaskA(void *pvParameters){
  EventBits_t uxReturn;
  while(1){
    uxReturn = xEventGroupSync(xEventGroup, TASKA_BIT, allSyncBits, portMAX_DELAY);
    if((uxReturn & allSyncBits) == allSyncBits){
      digitalWrite(RED, digitalRead(RED)^1);
      vTaskDelay(xDelay500ms);
    }
  }
}
void xTaskB(void *pvParameters){
  EventBits_t uxReturn;
  while(1){
    uxReturn = xEventGroupSync(xEventGroup, TASKB_BIT, allSyncBits, portMAX_DELAY);
    vTaskDelay(xDelay500ms);
    if((uxReturn & allSyncBits) == allSyncBits){
      digitalWrite(BLUE, digitalRead(BLUE)^1);
      vTaskDelay(xDelay500ms);
    }
  }
}
void xTaskC(void *pvParameters){
  EventBits_t uxReturn;
  while(1){
    uxReturn = xEventGroupSync(xEventGroup, TASKC_BIT, allSyncBits, portMAX_DELAY);
    vTaskDelay(xDelay500ms);
    if((uxReturn & allSyncBits) == allSyncBits){
      digitalWrite(YELLOW, digitalRead(YELLOW)^1);
      vTaskDelay(xDelay500ms);
    }
  }
}
void loop(){}
