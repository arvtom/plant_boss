
/* ---------------------------- Includes ---------------------------- */
#include "thread_app.h"

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Global variables ---------------------------- */

/* ---------------------------- Public functions ---------------------------- */
void thread_app(void *arg)
{
    while(1)
    {
        printf("app\n");
        vTaskDelay(100);
    }
}

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

