/* This file was automatically generated.  Do not edit! */
#include <stdlib.h>
void win32_api_create_menu(const char *in_window_title,const char *in_text,const unsigned short in_number_submenus,void(*in_on_click)());
typedef struct win32_api_submenu win32_api_submenu;
typedef struct win32_api_menu win32_api_menu;
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
struct win32_api_submenu {
        unsigned short id;
        const char* text;
        win32_api_menu* parent_menu;
        void (*on_click)();
    };
void win32_api_destroy_submenu(win32_api_submenu *out_submenu);
void win32_api_destroy_menu(win32_api_menu *out_menu);
#define INTERFACE 0
