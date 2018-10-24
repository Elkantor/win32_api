#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){ 
    win32_api_initialize(1);
    win32_api_begin_window("window_class_name", "main_window", 600, 300, 800, 600, 1);
    win32_api_end_window();

    while(1){
        win32_app_show_windows();
    }

    win32_api_end();
    return 0; 
}
