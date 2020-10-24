#ifndef CLICKWHEEL_H
#define CLICKWHEEL_H

//clickwheel data lines
#define DATA_PORT PORTD
#define DATA_PIN PIND
#define CW_SDA_PIN 2
#define CW_SCL_PIN 1 //INT1
#define CW_SDA PIND &(1 << CW_SDA_PIN)
#define CW_SCL PIND &(1 << CW_SCL_PIN)
//#define CW_SCL_LOW    ((PIND & _BV(7)))
//clickwheel packets
#define CW_CMD_P1 3    //first byte sent in packet
#define CW_BTN_CMD 2   //second byte sent in packet
#define CW_WHEEL_CMD 1 //second byte sent in packet
#define CW_CMD_P4 0    //second byte sent in packet

//clickwheel command ‘cmd’ formatting
#define CW_CMD_CW 0x80      //clockwise scroll event (used for ‘cmd’ stuffing only)
#define CW_CMD_CCW 0x40     //counter-clockwise scroll event (used for ‘cmd’ stuffing only)
#define CW_CMD_FLAG 0x20    //clickwheel new packet arrived flag
#define CW_CMD_PP 0x08      //clickwheel play >>|| pause button pressed
#define CW_CMD_MENU 0x10    //clickwheel menu button pressed
#define CW_CMD_BACK 0x04    //clickwheel back button pressed
#define CW_CMD_FORWARD 0x02 //clickwheel forward button pressed
#define CW_CMD_CBTN 0x01    //clickwheel center button pressed

#define CW_DEADBAND 7 //adjust the sensitivity/speed of the clickwheel. lower=more sensitive

//initialize interrupt and port
void uiinit(void);

//function return cmd byte following the clickwheel ‘cmd’ formatting defines
extern unsigned char uiaction(void);

//reset the ui action recieve buffer and cnd flag byte
//this function should be called after responding the the new action
extern void uireset(void);
#endif