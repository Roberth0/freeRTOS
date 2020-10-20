#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED 7
#define BLUE 8
#define YELLOW 9


QueueHandle_t xQueue1;
QueueHandle_t xQueue2;

QueueSetHandle_t xQueueSet;

void setup (){
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);
  xQueue1 = xQueueCreate(1, sizeof(char *));
  xQueue2 = xQueueCreate(1, sizeof(char *));
  xQueueSet = xQueueCreateSet(1*2);
  xQueueAddToSet(xQueue1, xQueueSet);
  xQueueAddToSet(xQueue2, xQueueSet);

  xTaskCreate(vSenderTaskController1, "Sender task 1", 100, NULL, 1, NULL);
  xTaskCreate(vSenderTaskController2, "Sender task 2", 100, NULL, 1, NULL);

  xTaskCreate(vReceiverTaskController, "Receiver Task", 100, NULL, 2, NULL);
}

void vSenderTaskController1 (void *pvParameters){
  const TickType_t xSender1Block = pdMS_TO_TICKS(300);
  const char * const messageToSend = "Message from sender 1 ";
  while(1){
    vTaskDelay(xSender1Block);
    xQueueSend(xQueue1, &messageToSend, 0);
    digitalWrite(RED, HIGH);
    

}
}

void vSenderTaskController2 (void *pvParameters){
const TickType_t xSender2Block = pdMS_TO_TICKS(200);
const char * const message2Send = "Message form sender 2 ";
while(1){
  vTaskDelay(xSender2Block);
  xQueueSend(xQueue2, &message2Send, 0);
  digitalWrite(BLUE, HIGH);

  }
}

void vReceiverTaskController (void *pvParameters){
  QueueHandle_t xQueueDataContainer;
  char *pcReceivedString;
  while(1){
    xQueueDataContainer = (QueueHandle_t)xQueueSelectFromSet(xQueueSet, portMAX_DELAY);
    xQueueReceive(xQueueDataContainer, &pcReceivedString, 0);
    Serial.println(pcReceivedString);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, LOW);
  }
}
void loop (){}
