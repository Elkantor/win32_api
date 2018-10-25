/* This file was automatically generated.  Do not edit! */
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct win32_api_window win32_api_window;
bool win32_api_initialize_window(win32_api_window *out_window);
bool win32_api_show_windows();
void win32_api_destroy_window(win32_api_window *out_window);
void win32_api_end();
bool win32_api_reallocate_windows_array();
bool win32_api_initialize();
typedef struct win32_api_window_manager win32_api_window_manager;
struct win32_api_window_manager {
        win32_api_window* windows;
        char max_number_windows;
        char current_index_windows;
    };
extern win32_api_window_manager window_manager;
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
