#include "mbed.h"

Ticker ticker;

DigitalOut led_red(P0_22);
DigitalOut led_green(P3_25);
DigitalOut led_blue(P3_24);

CAN can1(P0_4, P0_5);
char counter = 0;
Serial pc(USBTX, USBRX);

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
    led_blue = !led_blue;
    return success;
    /*if(can1.write(CANMessage(0x211, &counter, 1))) {
        printf("wloop()\n");
        counter++;
        printf("Message sent: %d\n", counter);
        led_red = 0;
        led_green = 1;
    } else {
        led_red = 1;
        led_green = 0;
    }*/
}

int main() {
    led_green = 0;
    led_blue = 0;
    led_red = 0;
    pc.baud(115200);
    wait(0.2);
    can1.frequency(250000);
    wait(0.2);
    can1.attach(&test, CAN::RxIrq);
    
    while(1) {
        
        wait(1);
        if(send());
        wait(1);
        if(send());
        /*
        printf("main()\n");
        ticker.attach(&send,1);
        CANMessage msg;
        send();
        wait(0.2);*/
    }
}
