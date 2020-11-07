#include <Arduino_FreeRTOS.h>

#define RED 7
#define BLUE 8
#define YELLOW 9

void setup(){
  xTaskCreate(vTask1, "Task 1", 100, NULL, 1, NULL);
  xTaskCreate(vTask2, "Task 2", 100, NULL, 1, NULL);
  xTaskCreate(vTask3, "Task 3", 100, NULL, 1, NULL);
}

void vTask1(void *pvParameters){
  pinMode(RED, OUTPUT);
  while(1){
    digitalWrite(RED, digitalRead(RED)^1);
    
  }
}
void vTask2(void *pvParameters){
  pinMode(BLUE, OUTPUT);
  while(1){
    digitalWrite(BLUE, digitalRead(BLUE)^1);
    
  }
}
void vTask3(void *pvParameters){
  pinMode(YELLOW, OUTPUT);
  while(1){
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);
   
  }
}
void loop(){}
