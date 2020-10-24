#include <Arduino.h>
#include <clickwheel.h>

//#define F_CPU 8000000UL // 8 MHz

int count;
char buffer[32];
void setup()
{
  Serial.begin(9600); // start serial for output
  uiinit();
  Serial.println("Starting");
}

void loop()
{
  switch (uiaction())
  {
  case CW_CMD_CW:
    Serial.print("clockwise ");
    count = count + 10;
    Serial.println(count);
    uireset();
    break;
  case CW_CMD_CCW:
    Serial.print("counterclockwise ");
    count = count - 10;
    Serial.println(count);
    uireset();
    break;
  case CW_CMD_PP:
    Serial.println("play/pause ");
    uireset();
    break;
  case CW_CMD_MENU:
    Serial.println("menu");
    uireset();
    break;
  case CW_CMD_BACK:
    Serial.println("back");
    count--;
    Serial.println(count);
    uireset();
    break;
  case CW_CMD_FORWARD:
    Serial.println("forward");
    count++;
    Serial.println(count);
    uireset();
    break;
  case CW_CMD_CBTN:
    Serial.println("center");
    uireset();
    count = 0;
    Serial.println(count);
    break;
  default:
    1;
  }
}
