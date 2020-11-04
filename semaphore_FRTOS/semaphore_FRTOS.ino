#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define RED 7
#define BLUE 8 
#define YELLOW 9
#define x1 10
#define x2 11
//#define x3 12
//#define x4 13
//#define x5 6
//#define x6 7
//#define x7 5
//#define x8 4
//#define x9 3
#define x10 2


typedef int TaskProfiler;
TaskProfiler RedTaskProfiler;
TaskProfiler BlueTaskProfiler;
TaskProfiler YellowTaskProfiler;

SemaphoreHandle_t xBinarySemaphore;

void setup (){
  Serial.begin(19200);
  xBinarySemaphore = xSemaphoreCreateBinary();
  xTaskCreate(redLedControllerTask, "Red led Contoller Task", 100, NULL, 4, NULL);
  xTaskCreate(blueLedControllerTask, "Blue led Controller Task", 100, NULL, 1, NULL);
  xTaskCreate(yellowLedControllerTask, "Yellow led Controller Task", 100, NULL, 4, NULL);
  xTaskCreate(x1LedControllerTask, "Yellow led Controller Task", 100, NULL, 1, NULL);
  xTaskCreate(x2LedControllerTask, "Yellow led Controller Task", 100, NULL, 2, NULL);
//  xTaskCreate(x3LedControllerTask, "Yellow led Controller Task", 100, NULL, 1, NULL);
//  xTaskCreate(x4LedControllerTask, "Yellow led Controller Task", 100, NULL, 1, NULL);
//  xTaskCreate(x5LedControllerTask, "Yellow led Controller Task", 100, NULL, 1, NULL);
//  xTaskCreate(x7LedControllerTask, "Yellow led Controller Task", 100, NULL, 1, NULL);
//  xTaskCreate(x8LedControllerTask, "Yellow led Controller Task", 100, NULL, 1, NULL);
//  xTaskCreate(x9LedControllerTask, "Yellow led Controller Task", 100, NULL, 1, NULL);
  xTaskCreate(x10LedControllerTask, "Yellow led Controller Task", 100, NULL, 1, NULL);
  
}

void redLedControllerTask (void *pvParameters){
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

void blueLedControllerTask (void *pvParameters){
  pinMode(BLUE, OUTPUT);
  while(1){
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("Blue led Tas");
    digitalWrite(BLUE, digitalRead(BLUE)^1);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}

void yellowLedControllerTask (void *pvParameters){
  pinMode(YELLOW, OUTPUT);
  while(1){
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("Yellow led task");
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}

void x1LedControllerTask (void *pvParameters){
  pinMode(x1, OUTPUT);
  while(1){
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("x1  led task");
    digitalWrite(x1, digitalRead(x1)^1);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}

void x2LedControllerTask (void *pvParameters){
  pinMode(x2, OUTPUT);
  while(1){
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("x2  led task");
    digitalWrite(x2, digitalRead(x2)^1);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}

void x10LedControllerTask (void *pvParameters){
  pinMode(x10, OUTPUT);
  while(1){
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("x10  led task");
    digitalWrite(x10, digitalRead(x10)^1);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}

//void x3LedControllerTask (void *pvParameters){
//  pinMode(x3, OUTPUT);
//  while(1){
//    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
//    Serial.println("x3  led task");
//    digitalWrite(x3, digitalRead(x3)^1);
//    xSemaphoreGive(xBinarySemaphore);
//    vTaskDelay(1);
//  }
//}

//void x4LedControllerTask (void *pvParameters){
//  pinMode(x4, OUTPUT);
//  while(1){
//    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
//    Serial.println("x4  led task");
//    digitalWrite(x4, digitalRead(x4)^1);
//    xSemaphoreGive(xBinarySemaphore);
//    vTaskDelay(1);
//  }
//}
//
//void x5LedControllerTask (void *pvParameters){
//  pinMode(x5, OUTPUT);
//  while(1){
//    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
//    Serial.println("x5  led task");
//    digitalWrite(x5, digitalRead(x5)^1);
//    xSemaphoreGive(xBinarySemaphore);
//    vTaskDelay(1);
//  }
//}
//
//void x6LedControllerTask (void *pvParameters){
//  pinMode(x6, OUTPUT);
//  while(1){
//    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
//    Serial.println("x6  led task");
//    digitalWrite(x6, digitalRead(x6)^1);
//    xSemaphoreGive(xBinarySemaphore);
//    vTaskDelay(1);
//  }
//}

//void x7LedControllerTask (void *pvParameters){
//  pinMode(x7, OUTPUT);
//  while(1){
//    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
//    Serial.println("x7  led task");
//    digitalWrite(x7, digitalRead(x7)^1);
//    xSemaphoreGive(xBinarySemaphore);
//    vTaskDelay(1);
//  }
//}
//
//void x8LedControllerTask (void *pvParameters){
//  pinMode(x8, OUTPUT);
//  while(1){
//    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
//    Serial.println("x8  led task");
//    digitalWrite(x8, digitalRead(x8)^1);
//    xSemaphoreGive(xBinarySemaphore);
//    vTaskDelay(1);
//  }
//}

//void x9LedControllerTask (void *pvParameters){
//  pinMode(x9, OUTPUT);
//  while(1){
//    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
//    Serial.println("x9  led task");
//    digitalWrite(x9, digitalRead(x9)^1);
//    xSemaphoreGive(xBinarySemaphore);
//    vTaskDelay(1);
//  }
//}


void loop(){}
