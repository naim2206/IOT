#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    FILE* urand, * led;
    int on;
    unsigned char value;

    int i = 0;
    while (1)
    {
        urand = fopen("/dev/urandom", "r");
        led = fopen("leds", "w"); // LED CONTROLLER
        value = fgetc(urand);

        if ((int)value > 128)
        {  //LED ON
            on = 1;
            fprintf(led, "%d", on);
        }
        else
        {                  //LED OFF
            on = 0;
            fprintf(led, "%d", on);
        }
        sleep(1);
        fclose(led);
        fclose(urand);
    }

    return 0;
}