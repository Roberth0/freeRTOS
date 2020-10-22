#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define RED 7
#define BLUE 8 
#define YELLOW 9

typedef int TaskProfiler;
TaskProfiler RedTaskProfiler;
TaskProfiler BlueTaskProfiler;
TaskProfiler YellowTaskProfiler;

SemaphoreHandle_t xBinarySemaphore;

void setup (){
  Serial.begin(9600);
  xBinarySemaphore = xSemaphoreCreateBinary();
  xTaskCreate(redLedControllerTask, "Red led Contoller Task", 100, NULL, 1, NULL);
  xTaskCreate(blueLedControllerTask, "Blue led Controller Task", 100, NULL, 1, NULL);
  xTaskCreate(yellowLedControllerTask, "Yellow led Controller Task", 100, NULL, 1, NULL);
}

void redLedControllerTask (void *pvPvParameters){
  xSemaphoreGive(xBinarySemaphore);
  pinMode(RED, OUTPUT);
  while(1){
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("Red led task");
    digitalWrite(RED, digitalRead(RED)^1);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}

void blueLedControllerTask (void *pvPvParameters){
  pinMode(BLUE, OUTPUT);
  while(1){
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("Blue led Tas");
    digitalWrite(BLUE, digitalRead(BLUE)^1);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}

void yellowLedControllerTask (void *pvPvParameters){
  pinMode(YELLOW, OUTPUT);
  while(1){
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("Yellow led task");
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}
void loop(){}
