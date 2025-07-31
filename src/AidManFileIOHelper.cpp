

#include "AidManFileIOHelper.h"
#include "Date.h"
#include "Item.h"
#include "Perishable.h"
#include <iostream>
#include <fstream>
#include <cstring>

namespace sdds {
	
	int AidManFileIOHelper::list(const char* sub_desc) {

		int filtered_record_count = 0;

		if (sub_desc == nullptr) {
			for (unsigned i = 0; i < m_number_of_products_in_the_array; i++) {
				m_products[i]->linear(true);
				m_products[i]->display(std::cout);
				std::cout << std::endl;
				filtered_record_count++;
			}
		}
		else { // if it contains search desc

			const char* desc;
			for (unsigned i = 0; i < m_number_of_products_in_the_array; i++) {
				desc = m_products[i]->get_desc();

				const char* result = desc;

				if ((result = std::strstr(result, sub_desc)) != nullptr) {
					std::cout << "Found '" << sub_desc << "' starting at '" << result << "'\n";
					m_products[i]->display(std::cout);
					filtered_record_count++;
				}
				
			}
			//while ()

			
		}

		return filtered_record_count;
	
	}
	int AidManFileIOHelper::search(int sku) const {

		std::cout << "Searching for sku : " << sku << std::endl;

		for (unsigned i = 0; i < m_number_of_products_in_the_array; i++) {
			
			if (*m_products[i] == sku) {
				return i;
			}
		}

		std::cout << "No match for sku : " << sku << std::endl;

		return -1;
	}

	void AidManFileIOHelper::remove(int index){

		delete m_products[index];

		m_products[index] = nullptr;

		
		for (unsigned i = index; i < m_number_of_products_in_the_array - 1; ++i){
			m_products[i] = m_products[i + 1]; 
		}

		m_number_of_products_in_the_array--;

		m_products[m_number_of_products_in_the_array] = nullptr;
			

	}

	void AidManFileIOHelper::for_each_product(std::ostream & ostr, void(*forech_function)(iProduct *product, std::ostream & ostr)) {

		for (unsigned i = 0; i < m_number_of_products_in_the_array; ++i) {
			forech_function(m_products[i],ostr);
		}

	}


	void AidManFileIOHelper::ship(void) {
		std::ofstream shipment_file("shippingOrder.txt");

		if (!shipment_file) {
			std::cout << "Coudn't open shipment file " << std::endl;
		}

		Date date;
		shipment_file << "Shipping Order, Date : " << date << std::endl;

		shipment_file << "ROW | SKU | Description| Have | Need |Price | Expiry" << std::endl;
		shipment_file << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;

		auto save_func = [](iProduct *prd, std::ostream &ostr) {
			if (prd->qty() == prd->qtyNeeded()) {
				prd->linear(true);
				prd->save(ostr);
				ostr << std::endl;

			}
			
		};

		for_each_product(shipment_file,save_func);


		shipment_file << std::endl <<  "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;

		std::cout << "Products shipped" << std::endl;



	}

	void AidManFileIOHelper::sort(void){

		int difference_1 = 0;
		int difference_2 = 0;
		bool change_occured = false;
		iProduct *temp_p_ptr = nullptr;

		do {
			change_occured = false;
			for (unsigned i = 0; i < m_number_of_products_in_the_array - 1; i++) {
				difference_1 = m_products[i]->qtyNeeded() - m_products[i]->qty();
				difference_2 = m_products[i + 1]->qtyNeeded() - m_products[i + 1]->qty();

				if (difference_1 < difference_2) {
					temp_p_ptr = m_products[i];
					m_products[i] = m_products[i + 1];
					m_products[i + 1] = temp_p_ptr;
					change_occured = true;
				}
			}

		} while (change_occured);
		
	}


	void AidManFileIOHelper::deallocate(void) {

		for (unsigned i = 0; i < m_number_of_products_in_the_array; i++) {
			delete m_products[i];
			m_products[i] = nullptr;
		}

		m_number_of_products_in_the_array = 0;
	}



	bool AidManFileIOHelper::add_product_to_array(iProduct* product_ptr){

		if (m_number_of_products_in_the_array < sdds_max_num_items) {

			m_products[m_number_of_products_in_the_array++] = product_ptr;
			return true;
		}
		

		return false;
		
	}

	


	bool AidManFileIOHelper::load(void) {

		bool load_ok = false;
		unsigned read_record_count = 0;

		if (m_data_file_name.empty()) {
			std::cout << "File name empty" << std::endl;
			return false;
		}


		std::ifstream load_file(m_data_file_name);

		if (!load_file) {
			std::cout << "Failed to open FN for reading! : " << m_data_file_name << std::endl;
			std::cout << "Would you like to create a new data file ? " << std::endl;

			Menu m1(1, "1- Yes");
			int selection = m1.run();

			if (selection == 1) {
				std::ofstream ofs(m_data_file_name);
			}
			return false;
		}

		unsigned sku = 0;
		iProduct* product = nullptr;
		std::string token_str;

		try {

			while (load_file) {

				std::getline(load_file, token_str, '\t');
				sku = std::stoi(token_str);

				if (sku < 40000) {// perisable
					product = new Perishable;
				}
				else { // Item
					product = new Item;
				}

				product->set_sku(sku);
				product->load(load_file);
				//product->s

				if (*product) {
					add_product_to_array(product);
					load_ok = true;
					read_record_count++;
				}
				else {
					std::cout << "Product load error." << std::endl;
					delete product;
					break;
				}
			}


		}catch (const std::exception& ex) {
			//std::cout << "Inventory load exception : " << ex.what() << std::endl;
	

		}
		
		
		std::cout << read_record_count << " records read" << std::endl;

		return load_ok;

	}

	void AidManFileIOHelper::save(void) {

		if (m_data_file_name.empty()) {
			std::cout << "Save file name missing." << std::endl;
			return;
		}

		std::ofstream save_file(m_data_file_name);

		if (!save_file) {
			std::cout << "Coudn't open write file : " << m_data_file_name << std::endl;
			return;
		}

		for (unsigned i = 0; i < m_number_of_products_in_the_array; i++) {
			if (m_products[i]->save(save_file)) {
				save_file << std::endl;

			}
			else {
				std::cout << "Product save error " << std::endl;
				break;
			}
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
