#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char * argv []){
    FILE * urand, *led;
    int on;
    unsigned char value;
    urand = fopen("/dev/urandom","r");
    led = fdopen("/sys/class/leds/gpio-led/brightness"); 
    //led = fopen("results.txt","wa");
    int i = 0;
    while(1){
        value = fgetc(urand);
        if((int)value > 128){
            printf("LED ON");
            on = 1;
            fprintf(led,"%d",on);
        }
        else{
            printf("LED OFF");
            on = 0;
            fprintf(led,"%d",on);
        }
        usleep(1000000);
    }

   
    

    return 0;


    //printf("unrand: %d",value);
}