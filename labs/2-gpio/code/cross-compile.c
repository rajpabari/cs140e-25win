// tests that your gpio_input works.
// hardware:
//   1. connect pin 18 and 19 using a jumper ("loopback").
//   2. leave your LEDs connected to 20 and 21.
//   3. if the test succeeds they should blink in unison.  either
//      both on or both off.
//
// we do "true" embedded system debugging without any printk
// available by using LEDs to show what the system is doing:
//  iterate, alternating the value of <v> \in {0,1}
//  1. set LED on 20 to current value of <v> (ground truth)
//  2. set pin 18 (the loopback output) to <v>
//  3. read pin 19 (the loopback input) and set pin 21
//     to this value.
//
//  - if both LEDs match (both on at the same time, both off
//    at the same time) you are correct.
//   - if not: first try the staff binary to make sure your
//     pi is wired correctly.
#include "rpi.h"

void notmain(void)
{
    const int wormhole = 20;
    const int led = 21;

    gpio_set_output(wormhole);
    gpio_set_output(led);

    unsigned v = 0;
    for (int i = 0; i < 100; i++)
    {
        gpio_set_on(led);
        gpio_set_on(wormhole);
        delay_cycles(1000000);
        gpio_set_off(led);
        gpio_set_off(wormhole);
        delay_cycles(1000000);
    }
}
