#include <Arduino_FreeRTOS.h>
#include "queue.h"

typedef int TaskProfiler;
TaskProfiler SenderProfiler;
TaskProfiler ReceiveProfiler;

typedef enum {
  eSender1,
  eSender2,
} DataSource_t;

typedef struct {
  uint8_t ucValue;
  DataSource_t eDataSource;
} Data_t;

static const Data_t xStructToSend[2] = {
  {100, eSender1},
  {50, eSender2},
};

QueueHandle_t numQueue;

void setup() {
  Serial.begin(9600);
  BaseType_t qSenderStatus;
  numQueue = xQueueCreate(3, sizeof(Data_t));
  xTaskCreate(vSenderTask, "Sender 1 Task", 100, &(xStructToSend[0]), 2, NULL);
  xTaskCreate(vSenderTask, "Sender 2 Task", 100, &(xStructToSend[1]), 2, NULL);
  xTaskCreate(vReceiverTask, "Receiver Task", 100, NULL, 1, NULL);
}

void vSenderTask(void *pvParameters) {
  BaseType_t qSenderStatus;
  const TickType_t xSenderTicksToWait = pdMS_TO_TICKS(100);
  while (1) {
    qSenderStatus = xQueueSend(numQueue, pvParameters, xSenderTicksToWait);
    if (qSenderStatus != pdPASS) {
      Serial.println("Error sending the structure");
    }
  }
}

void vReceiverTask (void *pvParameters) {
  BaseType_t qReceiverStatus;
  Data_t dataReceived;
  while (1) {
    qReceiverStatus = xQueueReceive(numQueue, &dataReceived, 0);
    if (qReceiverStatus == pdPASS) {
      if (dataReceived.eDataSource == eSender1) {
        Serial.print("Data from sender 1:");
        Serial.println(dataReceived.ucValue);
      } else {
        Serial.print("Data from sender 2:");
        Serial.println(dataReceived.ucValue);
      }
    } else {
      Serial.println("No data received");
      }

  }
}


void loop() {}
