#include<Arduino.h>
#include "Definition.h"

void blink(bool final_state,int delay_time=BLINK_DELAY)
{
      digitalWrite(LED,!final_state);
      delay(delay_time);
      digitalWrite(LED,final_state);
      delay(delay_time);
      digitalWrite(LED,!final_state);
      delay(delay_time);
      digitalWrite(LED,final_state);
      delay(delay_time);
}