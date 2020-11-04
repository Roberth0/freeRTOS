#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define RED 7
#define BLUE 8
#define YELLOW 9

SemaphoreHandle_t xCountingSemaphore;

void setup (){
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);
  xCountingSemaphore = xSemaphoreCreateCounting(1, 0);
  xTaskCreate(redLedControllerTask, "Red led task", 100, NULL, 1, NULL);
  xTaskCreate(blueLedControllerTask, "Blue led task", 100, NULL, 1, NULL);
  xTaskCreate(yellowLedControllerTask, "Yellow led task", 100, NULL, 1, NULL);

  xSemaphoreGive(xCountingSemaphore);

}
void redLedControllerTask (void *pvParameters){
  while(1){
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(RED, digitalRead(RED)^1);
    Serial.println("Red Task" );
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}

void blueLedControllerTask (void *pvParameters){
  while(1){
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(BLUE, digitalRead(RED)^1);
    Serial.println("Blue task");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}

void yellowLedControllerTask (void *pvParameters){
  while(1){
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(YELLOW, digitalRead(RED)^1);
    Serial.println("Yellow task");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}
void loop(){}
