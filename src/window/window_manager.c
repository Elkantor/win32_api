#include "window_manager.h"

#if INTERFACE
#include <stdio.h>
#include <windows.h>

// Structures
    typedef struct win32_api_window_manager{
        win32_api_window* windows;
        char max_number_windows;
        char current_index_window;
    } win32_api_window_manager;
#endif

// Global variables
win32_api_window_manager window_manager;


// Functions

// Initialize the window_manager global variable, with a 'in_number_windows' 
// max number of windows
void win32_api_initialize(const unsigned int in_number_windows){
    window_manager.windows = (win32_api_window*) calloc(in_number_windows, sizeof(win32_api_window));
    if(window_manager.windows == NULL){
        printf("ERROR: A problem occured in \"win32_api_initialize\" function when allocate memory for the windows.\n");
        exit(1);
    }
    window_manager.max_number_windows = in_number_windows;
    window_manager.current_index_window = 0;
}


// Free the memory allocated to use this win32_api module
void win32_api_end(){
    win32_api_window* current_window;
    for(unsigned int i = 0; i < window_manager.max_number_windows; i++){
        current_window = &window_manager.windows[i];
        win32_api_destroy_window(current_window);
    }
}

// Show every window in the windows array of the window_manager
void win32_app_show_windows(){
    for(unsigned short i = 0; i < window_manager.max_number_windows; i++){
        win32_api_window* current_window = &window_manager.windows[i];
        if(current_window != NULL){
            if(current_window->hinstance != NULL){
                if(!current_window->ready){
                    win32_api_initialize_window(current_window); 
                }
                // Show the window by calling win32 api
                if(GetMessage(&(current_window->msg), NULL, 0, 0) > 0){
                    TranslateMessage(&current_window->msg);
                    DispatchMessage(&current_window->msg);
                }
            }
        }
    }
}
