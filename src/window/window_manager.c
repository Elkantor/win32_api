#include "window_manager.h"

#if INTERFACE
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

// Structures
    typedef struct win32_api_window_manager{
        win32_api_window* windows;
        char max_number_windows;
        char number_windows;
    } win32_api_window_manager;
#endif

// Global variables
win32_api_window_manager window_manager;


// Functions

/*
 * Initialize the window_manager global variable, with 10 max number of windows by default (reallocated if needed)
 */
bool win32_api_initialize(){
    window_manager.windows = (win32_api_window*) calloc(10, sizeof(win32_api_window));
    
    // Test if the allocation of memory of the windows array has correclty been done
    if(window_manager.windows == NULL){
        printf("ERROR: A problem occured in \"win32_api_initialize\" function when allocate memory for the windows.\n");
        return false;
    }
    window_manager.max_number_windows = 10; 
    window_manager.number_windows = 0;
    return true;
}

/*
 * Reallocate the windows array of the window_manager 
 */
bool win32_api_reallocate_windows_array(){
    win32_api_window* new_windows_array = realloc(window_manager.windows, (window_manager.max_number_windows + 1) * sizeof(win32_api_window));
    // Test if the new_windows_array is correclty reallocated
    if(new_windows_array == NULL){
        printf("ERROR: A problem occured when trying to allocate more memory to handle more windows (inside the window_manager), try to free some memory before trying again.\n");
        return false;
    }
    window_manager.windows = new_windows_array;
    window_manager.max_number_windows++;
    return true;
}

/*
 * Free the memory allocated to use this win32_api module
 */
void win32_api_end(){
    win32_api_window* current_window;
    for(unsigned int i = 0; i < window_manager.max_number_windows; i++){
        win32_api_destroy_window(i);
    }
}

/*
 * Show every window in the windows array of the window_manager
 */
bool win32_api_show_windows(){
    // Try to show each window of the windows array of the window_manager 
    for(unsigned short i = 0; i < window_manager.number_windows; i++){
        win32_api_window* current_window = &window_manager.windows[i];
        
        // Test if the current_window is null
        if(current_window == NULL){
            printf("ERROR: A problem occured when trying to show the window at index %d in the win32_api_show_windows function [window_manager.c] (the window is null).\n");
            return false;
        }
        
        // Test if the current window is ready to be drawn on the screen
        if(!current_window->ready){
            // If not, then initialize the window correctly
            win32_api_initialize_window(current_window); 
        }
            
        // Test if the hinstance of the current_window is null
        if(current_window->hinstance == NULL){
            printf("ERROR: A problem occured when trying to show the window at index %d in the win32_api_show_windows function [window_manager.c] (the hinstance of the window is null).\n");
            return false;
        }
        
        // Show the window by calling the win32 api functions
        if(GetMessage(&(current_window->msg), NULL, 0, 0) > 0){
            TranslateMessage(&current_window->msg);
            DispatchMessage(&current_window->msg);
        }
    }
    return true;
}

/*
 * Shift the windows indexes (after the destruction of a window at in_index_window index) of the windows array
 */
void win32_api_shift_windows_indexes(const char in_index_window_destroyed){
    // Test if the index of the destroyed window (in_index_window)
    // was the last index of the array
    if(in_index_window_destroyed == window_manager.number_windows-1){
        // No need to shift the array in that case
        return;      
    }

    // Test if the destroyed window was the only one window in the array
    if(window_manager.number_windows == 1){
        // No need to shift the array in that case too
        return;
    }

    // In any other case, shift the array by changing 
    for(unsigned short i = in_index_window_destroyed; i < window_manager.number_windows-1; i++){
        // The pointer to the current window is now pointing to the next window in the array
        window_manager.windows[i] = window_manager.windows[i+1];
    }
    return;
}
