/*  Perishable.cpp Version 1 */

#include "Item.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Perishable.h"

using std::cout;
using std::endl;

namespace sdds {



	std::ostream & Perishable::display(std::ostream & ostr) const {
		Item::display(ostr);

		if (m_status) {
			
			if (linear()) {
				if (m_handling_instructions.empty() == false) {
					ostr << " | *";
				}else {
					ostr << " |  ";
				}
				ostr << " | " << m_expiry;
			}
			else {
			
				ostr << "Expiry date : " << m_expiry << endl;

				if (m_handling_instructions.empty() == false) {
					ostr << "Handling instructions : " << m_handling_instructions << endl;
				}

			}
		}
		
		return ostr;
	}

	Date Perishable::expiry(void) const{
		return m_expiry;
	}

	int Perishable::readSku(std::istream & istr) {
		int sku = Utils::get_int(istr, 10000, 39999, "SKU : ");

		m_sku_number = sku;
		return sku;
	}

	std::ifstream & Perishable::load(std::ifstream & ifstr){
		Item::load(ifstr);
		return ifstr;
	}

	std::istream & Perishable::read(std::istream & istr)
	{
		Item::read(istr);

		if (!m_status) {
			return istr;
		}

		std::ios_base::iostate ex_mask = istr.exceptions();

		istr.exceptions(std::istream::failbit | std::istream::badbit);

		try {

			istr.ignore();

			cout << "Expiriy date (YYMMDD) : ";
			istr >> m_expiry;

			cout << "Handling Instructions, ENTER to skip : ";

			std::getline(istr, m_handling_instructions);

			m_status.clear();


		}
		catch (const std::exception &ex) {
			cout << "Perishable read exception" << endl;

			m_status = "Console entry failed!";
			m_status = 7;

		}


		istr.exceptions(ex_mask);
		return istr;
	}



	std::ostream & Perishable::save(std::ostream & ofstr) const{
		Item::save(ofstr);

		if (m_status) {
			ofstr << "\t" << m_handling_instructions;
			ofstr << "\t" << m_expiry;

		}
		
		return ofstr;
	}

}