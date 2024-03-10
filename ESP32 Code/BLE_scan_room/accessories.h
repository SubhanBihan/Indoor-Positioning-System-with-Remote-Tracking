#include<Arduino.h>
#include "Definition.h"

void blink(bool final_state)
{
      digitalWrite(LED,!final_state);
      delay(BLINK_DELAY);
      digitalWrite(LED,final_state);
      delay(BLINK_DELAY);
      digitalWrite(LED,!final_state);
      delay(BLINK_DELAY);
      digitalWrite(LED,final_state);
      delay(BLINK_DELAY);
}