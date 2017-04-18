#include "mbed.h"

Ticker ticker;

DigitalOut led_red(P0_22);
DigitalOut led_green(P3_25);
DigitalOut led_blue(P3_24);
DigitalOut led_external1(P2_11);
DigitalOut led_external2(P2_12);


CAN can1(P0_4, P0_5);
char counter = 0;

void test(void) {
    led_green = !led_green;
    return;
}

bool send() {
    printf("send()\n");
    char canmsg[3];
    canmsg[0] = 0x3D;
    canmsg[1] = 0x30;
    canmsg[2] = 0x00;
    bool success = can1.write(CANMessage(0x211, canmsg, 3));
    return success;
}

int main() {
    led_green = 0;
    led_blue = 0;
    led_red = 0;
    CANMessage msg;
    
    while(1) {
        if(can1.read(msg)){
            led_red = !led_red;
            DigitalOut led_external2(P2_12);
        }
        wait(0.2);
    }
}
