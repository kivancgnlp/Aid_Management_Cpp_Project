/*  Perishable.h Version 1 */

#ifndef SDDS_PERISH_H
#define SDDS_PERISH_H

#include "iProduct.h"
#include "Item.h"
#include "Status.h"
#include "Utils.h"
#include "Date.h"
#include <string>

namespace sdds {

	class Perishable : public Item {
		Date m_expiry;
		std::string m_handling_instructions;

	public:
		std::ostream& display(std::ostream& ostr) const override;
		Date expiry(void) const;
		std::ifstream& load(std::ifstream& ifstr)  override;
		std::istream& read(std::istream& istr) override;
		int readSku(std::istream& istr)  override;
		std::ostream& save(std::ostream& ofstr) const override;

		friend class Utils;
	};


}

#endif // !SDDS_PERISH_H