#include "mbed.h"

Timeout to_1;
//InterruptIn button(P2_12);
DigitalOut red(P0_22);
DigitalOut blue(P3_26);
DigitalOut green(P3_25);
 
void flipred() {
    red = !red;
}
void holdled() {
    red = 0;
    wait(3);
}
 
int main() {
    to_1.attach(&holdled,2);
    while(1) {           // wait around, interrupts will interrupt this!
        flipred();
        wait(0.25);
    }
}