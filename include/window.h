/* This file was automatically generated.  Do not edit! */
#include <stdlib.h>
typedef struct win32_api_menu win32_api_menu;
typedef struct win32_api_submenu win32_api_submenu;
struct win32_api_submenu {
        unsigned short id;
        const char* text;
        win32_api_menu* parent_menu;
        void (*on_click)();
    };
struct win32_api_menu {
        unsigned short id;
        const char* text;
        unsigned short max_number_submenus;
        unsigned short max_number_menus;
        struct win32_api_menu* menus;
        struct win32_api_submenu* submenus;
        struct win32_api_menu* parent_menu;
        void (*on_click)();
    };
void win32_api_destroy_menu(win32_api_menu *out_menu);
#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct win32_api_window win32_api_window;
void win32_api_destroy_window(win32_api_window *out_window);
LRESULT CALLBACK win32_api_window_proc(HWND in_hwnd,UINT in_msg,WPARAM in_wparam,LPARAM in_lparam);
bool win32_api_initialize_window(win32_api_window *out_window);
typedef struct win32_api_window_manager win32_api_window_manager;
struct win32_api_window_manager {
        win32_api_window* windows;
        char max_number_windows;
        char current_index_windows;
    };
extern win32_api_window_manager window_manager;
bool win32_api_create_window(const char *in_window_class_name,const char *in_window_title,const int in_pos_x,const int in_pos_y,const int in_width,const int in_height,const unsigned int in_number_menus);
struct win32_api_window {
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
#define INTERFACE 0
