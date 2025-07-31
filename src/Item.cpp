
/*  Item.cpp Version 1 */

#include "Item.h"
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;

namespace sdds {
	bool Item::linear(void) const{
		return m_description_linear;
	}
	Item::Item(void){
		//std::cout << "Item default ctor" << std::endl;

		m_price = 0;
		m_qty = 0;
		m_qty_needed = 0;
		m_description_linear = 0;
		m_sku_number = 0;
	}
	Item::~Item(){
		//std::cout << "Item dtor" << std::endl;
	}

	void Item::clear(void){
		m_status.clear();
	}

	int Item::qtyNeeded()const {
		return m_qty_needed;
	}
	int Item::qty()const {
		return m_qty;
	}
	Item::operator double()const {
		return m_price;
	}
	Item::operator bool()const {
		return m_status == nullptr;
	}
	int Item::operator-=(int qty) {
		m_qty -= qty;
		return m_qty;
	}
	int Item::operator+=(int qty) {
		m_qty += qty;
		return m_qty;
	}

	void Item::linear(bool isLinear) {
		m_description_linear = isLinear;
	}

	bool Item::operator==(int sku)const {
		return m_sku_number == sku;
	}
	bool Item::operator==(const char* desc)const {
		int comp = m_description.compare(desc);
		return comp == 0;;
	}



	std::ostream& Item::save(std::ostream& ostr)const {

		if (m_status) {
			ostr << m_sku_number << "\t" << m_description << "\t" << m_qty << "\t" << m_qty_needed << "\t" << m_price;
		}else {
			cout << "save state bad " << endl;
		}
		
		return ostr;
	}

	std::ifstream& Item::load(std::ifstream& ifstr) {


		try{
			Utils::parse_item_line(ifstr, *this);

			//cout << "item parse ok" << endl;
			m_status.clear();

		}catch (const std::exception & ex){

			//cout << "item parse exception" << endl;
			m_status = "Input file stream read failed : ";
			m_status = 5;

		}

		//ifstr.exceptions(ex_mask);
		return ifstr;
	}

	std::ostream& Item::display(std::ostream& ostr)const {
		
		if (!m_status) {
			cout << "status bad " << m_status << endl;
		}else {

			if (m_description_linear){
				ostr << m_sku_number << " | " << m_description << " | " << m_qty << " | " << m_qty_needed << " | " << m_price;
			} else {
				ostr << "AMA Item:" << endl;
				ostr << m_sku_number << " : " << m_description  << endl;

				ostr << "Quantity Needed : " << m_qty_needed << endl;
				ostr << "Quantity Available : " << m_qty << endl;
				ostr << "Unit Price: : " << m_price << endl;
				
				double needed_money = (m_qty_needed - m_qty) * m_price;
				ostr << "Needed Purchase Fund : " << needed_money << endl;

			}


		}

		return ostr;
	}

	int Item::readSku(std::istream& istr) {
		int sku = Utils::get_int(istr, 40000, 99999, "SKU : ");

		m_sku_number = sku;
		return sku;
	}


	
	
	
	std::istream& Item::read(std::istream& istr) {
		

		std::ios_base::iostate ex_mask = istr.exceptions();

		istr.exceptions(std::istream::failbit | std::istream::badbit | std::istream::eofbit);

		try{

			if (ut.m_skip_sku) {
				//std::cout << typeid(*this).name() << std::endl;

				if (typeid(*this) == typeid(Item)) {
					m_sku_number = Utils::get_int(istr, 40000, 99999, "SKU : ");
				}
				else { // perishable
					m_sku_number = Utils::get_int(istr, 10000, 39999, "SKU : ");
				}
				
			}else{
				cout << "SKU : " << m_sku_number << endl;
			}
			
			cout << "Description : ";
			istr.ignore();
			std::getline(istr, m_description);

			m_qty_needed = Utils::get_int(istr, 1, 9999, "Quantity Needed : ");
			m_qty = Utils::get_int(istr, 0, 22, "Quantity On Hand : ");

			m_price = Utils::get_double(istr, 0, 9999, "Unit Price : ");

			//cout << "Item read ok" << endl;
			m_status.clear();


		}catch (const std::exception &ex){
			cout << "Item read exception" << endl;

			m_status = "Console entry failed!";
			m_status = 6;

		}


		istr.exceptions(ex_mask);
		return istr;

	}


	void Item::set_sku(int sku){
		m_sku_number = sku;
	}

	std::ostream & Item::operator<<(std::ostream & os) { // member toString
		return display(os);
	}

	std::istream & Item::operator>>(std::istream & is) { // member from String
		return read(is);
	}

	const char* Item::get_desc(void) const{
		return m_description.c_str();
	}

	int Item::get_sku(void) const {
		return m_sku_number;
	}

}
