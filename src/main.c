#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int main(int argc, char* argv[]){ 
    win32_api_initialize();
    win32_api_create_window("window_class_name", "1_window", 600, 300, 800, 600, 1);
    win32_api_create_window("window_class_name2", "2_window", 600, 300, 800, 600, 0);
    
    while(1){
        win32_api_show_windows();
    }

    win32_api_end();
    return 0; 
}
