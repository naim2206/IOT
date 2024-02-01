#include<stdio.h>
#include<unistd.h>

int main(int argc, char const* argv[])
{

    int val;
    while (1)
    {
        FILE* random = fopen("/dev/random", "r");
        FILE* led = fopen("led", "w");
        val = fgetc(random);
        if (val > 128)
            fputc('1', led);
        else
            fputc('0', led);
        sleep(1);
        fclose(led);
        fclose(random);
    }
    return 0;
}
