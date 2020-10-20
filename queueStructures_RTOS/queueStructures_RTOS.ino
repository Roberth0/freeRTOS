#include <Arduino_FreeRTOS.h>

#define RED 7
#define BLUE 8
#define YELLOW 9

typedef int TaskProfiler;
TaskProfiler RedLedProfiler;
TaskProfiler BlueLedProfiler;
TaskProfiler YellowLedProfiler;

void setup (){
    Serial.begin(9600);
    xTaskCreate(RedLedControllerTask, "Red led Task", 100, NULL, 1, NULL);
    xTaskCreate(BlueLedControllerTask, "Blue led Task", 100, NULL, 1, NULL);


}

void RedLedControllerTask (void *pvParameters) {
    while(1){
        RedLedProfiler++;
        Serial.print("Red led profiler:");
        Serial.println(RedLedProfiler);
    }
}

void BlueLedControllerTask(void *pvParameters){
    while(1){
        BlueLedProfiler++;
        Serial.print("Blue led Profiler:");
        Serial.println(BlueLedProfiler);

    }

}

void loop () {}