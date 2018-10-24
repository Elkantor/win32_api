#include "menu.h"

#if INTERFACE
#include <stdlib.h>
    // Structures
    typedef struct win32_api_menu{
        unsigned short id;
        const char* text;
        unsigned short max_number_submenus;
        unsigned short max_number_menus;
        struct win32_api_menu* menus;
        struct win32_api_submenu* submenus;
        struct win32_api_menu* parent_menu;
        void (*on_click)();
    } win32_api_menu;
#endif

// Functions

// Destroy and free the memory allocated for the given menu
void win32_api_destroy_menu(win32_api_menu* out_menu){
    if(out_menu->max_number_submenus > 0){
        win32_api_submenu* current_submenu;
        // free every submenu inside the menu
        for(unsigned short i = 0; i < out_menu->max_number_submenus; i++){
            current_submenu = &out_menu->submenus[i];
            win32_api_destroy_submenu(current_submenu);
        }
    }

    if(out_menu->max_number_menus > 0){
        win32_api_menu* current_menu;
        // free every child menu inside the menu
        for(unsigned short i = 0; i < out_menu->max_number_menus; i++){
            current_menu = &out_menu->menus[i];
            win32_api_destroy_menu(current_menu);
        }
    }
    free(out_menu);
}
