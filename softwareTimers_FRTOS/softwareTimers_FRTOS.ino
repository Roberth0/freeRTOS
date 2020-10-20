#include <Arduino_FreeRTOS.h>
#include "timers.h"

#define RED 7
#define BLUE 8
#define ONE_SHOT_TIMER_PERIOD (pdMS_TO_TICKS(500))
#define AUTO_RELOAD_TIME_PERIOD (pdMS_TO_TICKS(300))

TimerHandle_t xTimer1, xTimer2;
BaseType_t xTimer1Started, xTimer2Started;

void setup(){
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);
  xTimer1 = xTimerCreate("One shot", ONE_SHOT_TIMER_PERIOD, pdFALSE,0 , prvOneShotTimerCallback);
  xTimer2 = xTimerCreate("Auto Reload", AUTO_RELOAD_TIME_PERIOD, pdTRUE,0 , prvAutoReloadTimer);

  if((xTimer1 != NULL) && (xTimer2 != NULL)){
    xTimer1Started = xTimerStart(xTimer1, 0);
    xTimer2Started = xTimerStart(xTimer2, 0);
  }
  while((xTimer1Started != pdPASS) && (xTimer2Started != pdPASS)){}

}
void prvOneShotTimerCallback(TimerHandle_t xTimer){
  static TickType_t xTimeNow;
  xTimeNow = xTaskGetTickCount();
  Serial.print("One shot timer callback execution:");
  Serial.println(xTimeNow);
  digitalWrite(RED, digitalRead(RED)^1);
  
}
void prvAutoReloadTimer(TimerHandle_t xTimer){
  static TickType_t xTimeNow;
  xTimeNow = xTaskGetTickCount();
  Serial.print("Auto reload timer callback execution:");
  Serial.println(xTimeNow);
  digitalWrite(BLUE, digitalRead(BLUE)^1);
  

}
void loop(){}
