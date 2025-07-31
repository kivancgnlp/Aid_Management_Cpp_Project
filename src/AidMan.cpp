

#include "AidMan.h"
#include "Date.h"
#include "Item.h"
#include "Perishable.h"
#include <iostream>
#include <fstream>
#include <string>

namespace sdds {
	


	unsigned AidMan::menu(void){
		Date date;
		unsigned selection = 0;


		std::cout << "Aid Management System Version 0.1" << std::endl;
		std::cout << "Date: " << date << std::endl;
		
		if (m_helper.m_data_file_name.length() != 0) {
			std::cout << "Data file: " << m_helper.m_data_file_name << std::endl;
		}else {
			std::cout << "Data file: No file" << std::endl;
		}

		std::cout << "--------------------------------" << std::endl;
		
		
		selection = m_menu.run();


		return selection;
	}


	

	

	AidMan::AidMan(void) : m_menu(7, "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database"){

		//std::cout << "AidMan ctor" << std::endl;
	}



	AidMan::~AidMan(void){

		m_helper.save();
		m_helper.deallocate();
	}

	void AidMan::run_remove_proc(void) {
		std::string search_sku_input;

		std::cout << "SKU ? : ";
		std::cin >> search_sku_input;

		unsigned sku = std::stoi(search_sku_input);

		int index = m_helper.search(sku);

		if (index == -1) {
			std::cout << "SKU not found." << std::endl;
			return;
		}

		m_helper.remove(index);
	}

	void AidMan::run_add_proc(void){

		Menu add_menu(2, "1- Perishable \n2- Non-Perishable");

		int selection = add_menu.run();

		iProduct *product;
		if (selection == 1) {
			product = new Perishable();

		}else if (selection == 2) {

			product = new Item();
		}
		else {
			return;
		}

		product->read(std::cin);

		if (*product) {
			if (m_helper.search(product->get_sku()) == -1) {
				m_helper.add_product_to_array(product);
				std::cout << "Product added" << std::endl;
			}
			else {
				std::cout << "Product already exists" << std::endl;
				delete product;
			}
			
		}
		else {
			delete product;
		}

	}

	void AidMan::run_update_proc(void){

		std::string search_sku_input;

		std::cout << "SKU ? : ";
		std::cin >> search_sku_input;

		unsigned sku = std::stoi(search_sku_input);

		int index = m_helper.search(sku);

		if (index == -1) {
			std::cout << "SKU not found." << std::endl;
			return;
		}

		Menu add_menu(2, "1- Add \n2- Reduce");

		int quantity = 0; 
		int selection = add_menu.run();

		std::cout << "Quantity : ";
		std::cin >> quantity;


		if (selection == 1) {
			*m_helper.m_products[index] += quantity;
		}
		else if (selection == 2) {
			*m_helper.m_products[index] -= quantity;
			
		}
		else {
			return;
		}




	}


	void AidMan::run_open_or_create_new_data_file_proc(void) {


		if (m_helper.m_number_of_products_in_the_array > 0) {
			m_helper.save();
			m_helper.deallocate();
		}
	

		std::cout << "Enter file name : ";
		std::cin >> m_helper.m_data_file_name;

		m_helper.load();

	}
	void AidMan::run(void){

		unsigned selection = menu();

		int list_item_count;

		if (m_helper.m_data_file_name.empty()) {
			selection = 7;
		}

		while (selection != 0) {

			std::cout << std::endl;

			switch (selection){
			case 1:
				list_item_count = m_helper.list();
				std::cout << "Record count : " << list_item_count << std::endl;
				break;
			case 2:
				run_add_proc();
				break;
			case 3:
				run_remove_proc();
				break;
			case 4:
				run_update_proc();
				break;
			case 5:
				m_helper.sort();
				break;
			case 6:
				m_helper.ship();
				break;
			case 7:
				run_open_or_create_new_data_file_proc();
				break;

			default:
				std::cout << "invalid option selected" << std::endl;
				break;
			}

	
			

			selection = menu();
		}
	}

}

/*

switch (selection) {
case 0: std::cout << "Exiting Program!" << std::endl; break;
case 1: std::cout << "****List Items****" << std::endl; break;
case 2: std::cout << "****Add Item****" << std::endl; break;
case 3: std::cout << "****Remove Item****" << std::endl; break;
case 4: std::cout << "****Update Quantity****" << std::endl; break;
case 5: std::cout << "****Sort****" << std::endl; break;
case 6: std::cout << "****Ship Items****" << std::endl; break;
case 7: std::cout << "****New/Open Aid Database****" << std::endl; break;
}
*/