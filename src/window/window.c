#include "window.h"

#if INTERFACE
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Structures
    struct win32_api_window{
        HWND hwnd;
        HMODULE hinstance;
        MSG msg;
        const char* class_name;
        const char* title;
        int pos_x;
        int pos_y;
        int width;
        int height;
        unsigned short max_number_menus;
        unsigned short current_index_menus;
        win32_api_menu* menus;
        bool ready;
    };
#endif

// Functions

/*
 * Create a window in memory
 */
bool win32_api_create_window(
    const char* in_window_class_name,
    const char* in_window_title,
    const int in_pos_x,
    const int in_pos_y,
    const int in_width,
    const int in_height,
    const unsigned int in_number_menus
){
        // Test if the number_windows of the windows array is equal to the max_number_windows (that means that the default allocation of 10 windows for this application is passed, and we need to reallocate the windows array of the window_manager)
    if(window_manager.number_windows >= window_manager.max_number_windows){
        // Test if the reallocation has correclty been done
        if(!win32_api_reallocate_windows_array()){
            return false;
        }
    }
    
    win32_api_window* current_window = &window_manager.windows[window_manager.number_windows];
     
    // Allocate the memory for the menus 
    if(in_number_menus > 0){
        current_window->menus = (win32_api_menu*) calloc(in_number_menus, sizeof(win32_api_menu));
        
        // Test if the allocation has been correclty done
        if(current_window->menus == NULL){
            printf("ERROR: A Problem occured when initializing the menus of the %s window, inside the \"win32_api_begin_window\" function.\n", in_window_title);
            return false;
        }
    }

    current_window->hinstance = GetModuleHandle(0);
    current_window->class_name = in_window_class_name;
    current_window->title = in_window_title;
    current_window->pos_x = in_pos_x;
    current_window->pos_y = in_pos_y;
    current_window->width = in_width;
    current_window->height = in_height;
    current_window->max_number_menus = in_number_menus;
    current_window->current_index_menus = 0;
    current_window->ready = false;

    printf("window %s correclty added at index %d\n", current_window->title, window_manager.number_windows);
    // Increment the number_windows of the window_manager
    window_manager.number_windows++;

    return true;
}

/*
 * Initialize a window
 */
bool win32_api_initialize_window(win32_api_window* out_window){
    // Create the window using the win32 api
    WNDCLASSEX wc;

    // Step 1: Registering the window class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = win32_api_window_proc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = out_window->hinstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = out_window->class_name;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // Handle the case where an error occured
    // during the step 1
    if(!RegisterClassEx(&wc)){
        MessageBox(NULL, "Window Registration Failed !", "Error !", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    // Step 2: Creating the window
    out_window->hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        out_window->class_name,
        out_window->title,
        WS_POPUP | WS_SYSMENU | WS_THICKFRAME | WS_CAPTION | WS_VISIBLE,
        out_window->pos_x,
        out_window->pos_y,
        out_window->width,
        out_window->height,
        NULL,
        NULL,
        out_window->hinstance,
        NULL
    );

    // Handle the case where an error occured 
    // during the step 2
    if(out_window->hwnd == NULL){
        MessageBox(NULL, "Window Creation Failed !", "Error !", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    STARTUPINFOA startup_info;
    GetStartupInfoA(&startup_info);
    ShowWindow(out_window->hwnd, SW_SHOWDEFAULT);
    UpdateWindow(out_window->hwnd);

    // The window is now ready to be drawn on the screen
    out_window->ready = true;

    return true;
}

/*
 * Window default procedure function
 */
LRESULT CALLBACK win32_api_window_proc(
    HWND in_hwnd,
    UINT in_msg,
    WPARAM in_wparam,
    LPARAM in_lparam
){
    PAINTSTRUCT ps;
    HDC hdc;
    HMENU submenu, menu;
    char window_title[256];
    unsigned short window_index;

    switch(in_msg){
        case WM_CREATE:
            GetWindowTextA(in_hwnd, window_title, sizeof(window_title));
            for(unsigned short i = 0; i < window_manager.max_number_windows; i++){
                win32_api_window* current_window = &window_manager.windows[i];
                if(current_window != NULL){
                    if(strcmp(current_window->title, window_title) == 0){
                        if(current_window->menus != NULL){
                        }
                    }
                }       
            }
            break;
        case WM_COMMAND:
            break;
        case WM_PAINT:
            hdc = BeginPaint(in_hwnd, &ps);
            TextOut(hdc, 5, 5, "Test text on the main window", strlen("Test text on the main window"));
            EndPaint(in_hwnd, &ps);
            break;
        case WM_WINDOWPOSCHANGED:
            if((in_lparam == 0) || ((((PWINDOWPOS) in_lparam)->flags & SWP_NOSIZE) == 0)){
                InvalidateRect(in_hwnd, 0, TRUE);
            }
            break;
        case WM_KEYDOWN:
            break;
        case WM_CLOSE:
            // Get the title of the current window
            GetWindowTextA(in_hwnd, window_title, sizeof(window_title));
            // Get the index of the current window, in the windows array
            // of the window_manager, and test if this current window is actually
            // in this array
            if(win32_api_get_window_index(window_title, &window_index)){
                // If the window index has been found, the window is indeed in the  
                // windows array, so destroy it (and free the memory)
                win32_api_destroy_window(window_index);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_NCACTIVATE:
            return DefWindowProc(in_hwnd, in_msg, TRUE, in_lparam);
        default:
            return DefWindowProc(in_hwnd, in_msg, in_wparam, in_lparam);
    }
    return 0;
}

/*
 * Get the index of a window in the windows array (inside the window_manager)
 */
bool win32_api_get_window_index(
    const char* in_window_title,
    unsigned short* out_window_index
){
    // For each window in the array, check if the in_window_title 
    // match one of the window title
    for(unsigned short i = 0; i < window_manager.number_windows; i++){
        if(strcmp(in_window_title, window_manager.windows[i].title) == 0){
            *out_window_index = i;
            return true;
        }
    }
    return false;
}

/*
 * Destroy and free the memory allocated for the given window
 */
bool win32_api_destroy_window(const short in_index_window){
    win32_api_window* current_window = &window_manager.windows[in_index_window];
    win32_api_menu* current_menu;    

   
    // Free every menu inside the window
    for(unsigned short i = 0; i < current_window->max_number_menus; i++){
        current_menu = &current_window->menus[i];
        win32_api_destroy_menu(current_menu);
    }
    
    // Call win32 api to free the memory of the hwnd pointer
    DestroyWindow(current_window->hwnd);
   
    // Shift the windows pointers in the windows array (inside the window_manager), before freeing the window from memory
    win32_api_shift_windows_indexes(in_index_window);   
    // Decrement the number of windows in the windows array (inside the window_manager)
    window_manager.number_windows--;
   
    return true;
}
