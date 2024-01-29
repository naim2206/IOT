#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char * argv []){
    FILE * urand, *led;
    int on;
    unsigned char value;
    
    int i = 0;
    while(1){

        urand = fopen("/dev/urandom","r");
        led = fopen("/sys/class/leds/gpio-led/brightness","w"); 
        //led = fopen("results.txt","w");
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
        //usleep(100000);
        sleep(1);
        fclose(led);
        fclose(urand);
    }

   

    return 0;


    //printf("unrand: %d",value);
}