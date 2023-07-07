idf_component_register(
    SRCS "main.c" 
    "../src/thread_app.c" 
    "../src/thread_input.c" 
    "../src/thread_output.c" 
    "../src/thread_network.c" 
    "../src/thread_memory.c" 
    "../src/error_wrapper.c" 
    INCLUDE_DIRS "../inc")
