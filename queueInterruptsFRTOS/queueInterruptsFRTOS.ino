#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED 7
#define BLUE 8
#define YELLOW 9

int timer1_counter;
QueueHandle_t xInterQueue, xStringQueue;

void setup(){
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  Serial.begin(9600);
  xTaskCreate(vIntegerGenerator, "Integer Generator", 100, NULL, 1, NULL);
  xTaskCreate(vStringGenerator, "String Generator", 100, NULL, 1, NULL);
  xInterQueue = xQueueCreate(10, sizeof(uint32_t));
  xStringQueue = xQueueCreate(10, sizeof(char *));
  InterruptInit();
}
void vIntegerGenerator(void *pvParameters){
  TickType_t xLastExecutionTime;
  const TickType_t xDelay200ms = pdMS_TO_TICKS(200);
  uint32_t valueToSend = 0;
  xLastExecutionTime = xTaskGetTickCount();
  while(1){
    vTaskDelayUntil(&xLastExecutionTime, xDelay200ms);
    for (int i = 0; i < 5; i++){
      xQueueSendToBack(xInterQueue, &valueToSend, 0);
      valueToSend++;
    }
    
  }
}
void vStringGenerator(void *pvParameters){
  char *pcString;
  while(1){
    xQueueReceive(xStringQueue, &pcString, portMAX_DELAY);
    Serial.println(pcString); 
  }
}
void loop(){}
ISR(TIMER1_OVF_vect){
  TCNT1 = timer1_counter;
  uint32_t receivedNumber;
  static const char *pcString[]={
    "Hello\r\n",
    "Hi\r\n",
    "I\r\n", 
    "am\r\n",
    "here\r\n"
  };
  xQueueReceiveFromISR(xInterQueue, &receivedNumber, pdFALSE);
  receivedNumber &= 0x03;
  xQueueSendToBackFromISR(xStringQueue, &pcString[receivedNumber], pdFALSE);
}
void InterruptInit(){
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 34286;
  TCNT1 = timer1_counter;
  TCCR1B |= (1<<CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
  
}
