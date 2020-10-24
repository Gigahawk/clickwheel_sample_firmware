#include <Arduino.h>
#include "clickwheel.h"

volatile unsigned char cmd;
volatile char posn1, db_compare;
volatile union
{
    unsigned char byte[4];
    unsigned long int word;
} cmd_packet;

void isr()
{
    if (digitalRead(19))
    {
        cmd_packet.byte[0] |= 0x80;
    }

    if (((cmd_packet.byte[0] == 128) || (cmd_packet.byte[0] == 192)) && (cmd_packet.byte[3] == 26))
    {
        cmd = 0x20;
    }
    else
    {

        cmd_packet.byte[3] = (cmd_packet.byte[3] >> 1);
        cmd_packet.byte[3] |= (cmd_packet.byte[2] << 7);

        cmd_packet.byte[2] = (cmd_packet.byte[2] >> 1);
        cmd_packet.byte[2] |= (cmd_packet.byte[1] << 7);

        cmd_packet.byte[1] = (cmd_packet.byte[1] >> 1);
        cmd_packet.byte[1] |= (cmd_packet.byte[0] << 7);

        cmd_packet.byte[0] = (cmd_packet.byte[0] >> 1);
    }
}

void uiinit() {
    Serial.println("uiinit");
    pinMode(20, INPUT_PULLUP);
    pinMode(19, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(20), isr, RISING);
}

unsigned char uiaction(void)
{
    if (cmd == CW_CMD_FLAG)
    {

        if (cmd_packet.byte[CW_BTN_CMD] != 0)
        {
            cmd = cmd_packet.byte[2];
            return;
        }
        else
        {
            if (cmd_packet.byte[CW_WHEEL_CMD] > posn1)
            {
                while (db_compare > CW_DEADBAND)
                {
                    cmd = CW_CMD_CW;
                    db_compare = CW_DEADBAND / 2;
                    break;
                }
                db_compare += 1;
            }
            if (cmd_packet.byte[CW_WHEEL_CMD] < posn1)
            {
                while (db_compare <= 0)
                {
                    cmd = CW_CMD_CCW;
                    db_compare = CW_DEADBAND / 2;
                    break;
                }
                db_compare -= 1;
            }
            posn1 = cmd_packet.byte[CW_WHEEL_CMD];
        }
        cmd &= ~CW_CMD_FLAG;
        cmd_packet.word = 0x00000000;
    }
    //EIMSK |= 0x02;
    return cmd;
}

void uireset()
{
    cmd_packet.word = 0x00000000;
    cmd = 0;
}