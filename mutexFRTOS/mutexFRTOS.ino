#include <Arduino_FreeRTOS.h>
#include "semphr.h"

SemaphoreHandle_t xMutex;

void setup (){
  Serial.begin(9600);
  xMutex = xSemaphoreCreateMutex();
  xTaskCreate(OutputTask, "Output task", 100, "Task ##########1 text", 1, NULL);
  xTaskCreate(OutputTask, "Output task", 100, "Task ----------2 text", 2, NULL);
}
void OutputTask(void *pvParameters){
  char *pcStringToPrint;
  pcStringToPrint = (char *) pvParameters;
  while(1){
    printer(pcStringToPrint);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
void loop(){
}
void printer(const char* pcString){
  xSemaphoreTake(xMutex, portMAX_DELAY);
  Serial.println(pcString);
  xSemaphoreGive(xMutex);
}
