/*  Item.h Version 1 */

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "iProduct.h"
#include "Item.h"
#include "Status.h"
#include "Utils.h"

namespace sdds {

	class Item : public iProduct {
		double m_price;
		int m_qty;
		int m_qty_needed;
		std::string m_description; // TODO : cstring
		bool m_description_linear;

	protected:
		Status m_status;
		int m_sku_number;

		bool linear(void) const;
	public:

		Item(void);
		virtual ~Item();
		void clear(void);

		// ------------------------  from Readme file begin -----------------------  

		// to read the Stock-Keeping Unit from console before
		// main data entry
		int readSku(std::istream& istr) override;
		// to reduce the quantity on hand
		int operator-=(int qty) override;
		// to increase the quantity on hand
		int operator+=(int qty) override;
		// returns the price of the produce
		operator double() const override;
		// returns if the iProduct is in a good state
		operator bool() const override;
		// returns the number of products needed
		int qtyNeeded() const override;
		// retuns the quantity on hand


		int qty() const override;
		// determines if the iProduct is displayed in a linear format or
		// descriptive format
		void linear(bool isLinear) override;
		// saves the iProduct into a file
		std::ostream& save(std::ostream& ofstr) const override;
		// loads an iProduct from a file
		std::ifstream& load(std::ifstream& ifstr) override;
		// displays the iProduct on the screen
		std::ostream& display(std::ostream& ostr) const override;
		// reads the iProduct from the console
		std::istream& read(std::istream& istr) override;
		// return true if the sku is a match to the iProduct's sku
		bool operator==(int sku) const override;
		// rtrns true if the description is found in the iPorduct's description
		bool operator==(const char* description) const override;

		// ------------------------  from Readme file end -----------------------  

		void set_sku(int sku) override;

		virtual std::ostream &operator<<(std::ostream & os); // member toString
		virtual std::istream &operator>>(std::istream & is); // member fromStream

		//friend static void Utils::parse_item_line(std::ifstream& ifstr, Item &item);

		virtual const char* get_desc() const override;
		virtual int get_sku(void) const override;

		friend class Utils;
	};


}

#endif // !SDDS_ITEM_H