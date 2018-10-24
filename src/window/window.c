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

void win32_api_begin_window(
    const char* in_window_class_name,
    const char* in_window_title,
    const int in_pos_x,
    const int in_pos_y,
    const int in_width,
    const int in_height,
    const unsigned int in_number_menus
){
    win32_api_window* current_window = &window_manager.windows[window_manager.current_index_window];

    current_window->hinstance = GetModuleHandle(0);
    current_window->class_name = in_window_class_name;
    current_window->title = in_window_title;
    current_window->pos_x = in_pos_x;
    current_window->pos_y = in_pos_y;
    current_window->width = in_width;
    current_window->height = in_height;
    current_window->max_number_menus = in_number_menus;
    current_window->current_index_menus = 1;
    current_window->ready = false;
    
    // Allocate the memory for the menus 
    if(in_number_menus > 0){
        current_window->menus = (win32_api_menu*) calloc(in_number_menus, sizeof(win32_api_menu));
        // Test if the allocation has been correclty done
        if(current_window->menus == NULL){
            printf("ERROR: A Problem occured when initializing the menus of the %s window, inside the \"win32_api_begin_window\" function.\n", in_window_title);
            exit(1);
        }
    }
}

// Initialize a window
void win32_api_initialize_window(win32_api_window* out_window){
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
        return;
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
        return;
    }

    STARTUPINFOA startup_info;
    GetStartupInfoA(&startup_info);
    ShowWindow(out_window->hwnd, SW_SHOWDEFAULT);
    UpdateWindow(out_window->hwnd);

    out_window->ready = true;
}

// Window default procedure function
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
            DestroyWindow(in_hwnd);
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

// End the creation of a window
void win32_api_end_window(){
    window_manager.current_index_window++;
}

// Destroy and free the memory allocated for the given window
void win32_api_destroy_window(win32_api_window* out_window){
    win32_api_menu* current_menu;
    // free every menu inside the window
    for(unsigned short i = 0; i < out_window->max_number_menus; i++){
        current_menu = &out_window->menus[i];
        win32_api_destroy_menu(current_menu);
    }
    free(out_window);
}
