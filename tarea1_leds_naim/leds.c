#include<stdio.h>
#include<unistd.h>

int main(int argc, char const* argv[])
{
    FILE* random = fopen("/dev/random", "r");
    FILE* led = fopen("led", "w");
    int val;
    while (1)
    {
        val = fgetc(random);
        if (val > 128)
            fputc('1', led);
        else
            fputc('0', led);
        sleep(1);
    }
    return 0;
}
