#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

void app_main(void)
{
	unsigned char i = 0;

    while (1) {
        printf("Hello from app_main!\n");
        printf("%d\n", i);
        sleep(1);
    }
}
