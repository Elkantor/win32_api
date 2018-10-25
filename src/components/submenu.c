#include "submenu.h"

#if INTERFACE
#include <stdlib.h>
    // Structures
    typedef struct win32_api_submenu{
        unsigned short id;
        const char* text;
        win32_api_menu* parent_menu;
        void (*on_click)();
    } win32_api_submenu;
#endif

// Functions

/*
 * Destroy and free the memory allocated for the given submenu
 */
void win32_api_destroy_submenu(win32_api_submenu* out_submenu){
    free(out_submenu);
}
