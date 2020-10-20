#include <Arduino_FreeRTOS.h>
#include "timers.h"

#define RED 7
#define BLUE 8
#define YELLOW 9

TimerHandle_t xTimer1;
TimerHandle_t xTimer2;
const TickType_t xTimer1Period = pdMS_TO_TICKS(800);
const TickType_t xTimer2Period = pdMS_TO_TICKS(200);
BaseType_t xTimer1Started;
BaseType_t xTimer2Started;

void setup (){
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);
  xTimer1 = xTimerCreate("Auto Reload Timer 1",xTimer1Period, pdTRUE, 0, prvTimerCallbackFunction);
  xTimer2 = xTimerCreate("Auto Reload Timer 2",xTimer2Period, pdTRUE, 0, prvTimerCallbackFunction);

  if((xTimer1 != NULL) && (xTimer2 != NULL)){
    xTimer1Started = xTimerStart(xTimer1, 0);
    xTimer2Started = xTimerStart(xTimer2, 0);
  }
  while((xTimer1Started != pdPASS) && (xTimer2Started != pdPASS)){}
  
}
void loop (){}


uint32_t timerOneExecutionTime;

void  prvTimerCallbackFunction(TimerHandle_t xTimer){

  TickType_t xTimeNow;
  xTimeNow = xTaskGetTickCount();

  if (xTimer == xTimer1){
    timerOneExecutionTime++;
    Serial.print("Timer 1 Running");
    Serial.println(xTimeNow);
    digitalWrite(RED, digitalRead(RED)^1);
      if (timerOneExecutionTime == 7){
        xTimerStop(xTimer1, 0);
      }
  } else {
    Serial.print("Timer 2 Running");
    Serial.println(xTimeNow);
    digitalWrite(BLUE, digitalRead(BLUE)^1);
  }
}
