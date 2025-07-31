#include <string>

#ifndef SDDS_MENU_H
#define SDDS_MENU_H
namespace sdds {

    class Menu {
        std::string m_items;
        unsigned m_item_count;
        
    public:
        Menu(unsigned item_count = 0, const char *items="");

		Menu(const Menu & other) = delete; // copy ctor
		Menu &operator=(const Menu & other) = delete; // copy assignment operator

        unsigned run(void);
        
    };

}

#endif // !SDDS_MENU_H