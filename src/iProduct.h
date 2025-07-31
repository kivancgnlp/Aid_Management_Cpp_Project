/*  iProduct.h Version 1 */

#ifndef SDDS_IPROD_H
#define SDDS_IPROD_H

#include <iostream>
#include <string>

namespace sdds {

	class iProduct {

	public:
		virtual ~iProduct();


		// ------------------------  from Readme file (converted to pure virtual ) begin -----------------------
		// to read the Stock-Keeping Unit from console before
		// main data entry
		virtual int readSku(std::istream& istr) = 0;
		// to reduce the quantity on hand
		virtual int operator-=(int qty) = 0;
		// to increase the quantity on hand
		virtual int operator+=(int qty) = 0;
		// returns the price of the produce
		virtual operator double()const = 0;
		// returns if the iProduct is in a good state
		virtual operator bool()const = 0;
		// returns the number of products needed
		virtual int qtyNeeded()const = 0;
		// retuns the quantity on hand

		virtual int qty()const = 0;
		// determines if the iProduct is displayed in a linear format or
		// descriptive format
		virtual void linear(bool isLinear) = 0;
		// saves the iProduct into a file
		virtual std::ostream& save(std::ostream& ofstr)const = 0;
		// loads an iProduct from a file
		virtual std::ifstream& load(std::ifstream& ifstr) = 0;
		// displays the iProduct on the screen
		virtual std::ostream& display(std::ostream& ostr)const = 0;
		// reads the iProduct from the console
		virtual std::istream& read(std::istream& istr) = 0;
		// return true if the sku is a match to the iProduct's sku
		virtual bool operator==(int sku)const = 0;
		// rtrns true if the description is found in the iPorduct's description
		virtual bool operator==(const char* description)const = 0;

		// ------------------------  from Readme file end -----------------------

		virtual void set_sku(int sku) = 0;
		virtual const char* get_desc() const = 0;
		virtual int get_sku(void) const = 0;

		
	};

	std::ostream &operator<<(std::ostream & os, const iProduct & iproduct); // toString
	std::istream &operator>>(std::istream & is, iProduct & iproduct); // fromStream

}

#endif // !SDDS_IPROD_H