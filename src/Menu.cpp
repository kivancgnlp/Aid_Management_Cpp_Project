#include "Menu.h"
#include <iostream>

namespace sdds {

	Menu::Menu(unsigned item_count, const char* items) {
		m_items = items;
		m_item_count = item_count;

	}

	unsigned Menu::run(void){

		unsigned selection = 0;

		while (true){

			std::cout << m_items << std::endl;
			std::cout << "--------------------------------" << std::endl;
			std::cout << "0- Exit" << std::endl;
			std::cout << "> ";
			std::cin >> selection;

			if (std::cin){

				if (selection <= m_item_count) {
					break;
				}else {
					std::cout << "Value out of range. [ 0 <= val <= " << m_item_count << " ] " << std::endl;
				}

			}
			else {
				std::cout << "Invalid Integer, retry" << std::endl;
				std::cin.clear();
				std::cin.ignore(10, '\n');
				
			}


			
			

		}

		

		return selection;
	}


}
