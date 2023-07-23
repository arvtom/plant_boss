
#include "main.h"

void app_main(void)
{   
    xTaskCreate(thread_app, "thread_app", 
        STACK_THREAD_APP, NULL, PRIORITY_THREAD_APP, NULL);
    xTaskCreate(thread_input, "thread_input", 
        STACK_THREAD_INPUT, NULL, PRIORITY_THREAD_INPUT, NULL);
    xTaskCreate(thread_output, "thread_output", 
        STACK_THREAD_OUTPUT, NULL, PRIORITY_THREAD_OUTPUT, NULL);
    xTaskCreate(thread_network, "thread_network", 
        STACK_THREAD_NETWORK, NULL, PRIORITY_THREAD_NETWORK, NULL);
    xTaskCreate(thread_memory, "thread_memory", 
        STACK_THREAD_MEMORY, NULL, PRIORITY_THREAD_MEMORY, NULL);
}
