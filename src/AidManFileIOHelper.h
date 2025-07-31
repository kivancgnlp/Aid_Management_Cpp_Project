
#include "Menu.h"
#include "iProduct.h"
#include <string>

#ifndef SDDS_AID_HELPER_H
#define SDDS_AID_HELPER_H

namespace sdds {

    const int sdds_max_num_items = 100;

    class AidManFileIOHelper {
        
        

        iProduct* m_products[sdds_max_num_items] = {nullptr};
        unsigned m_number_of_products_in_the_array = 0;
        
		void for_each_product(std::ostream & ostr, void (*forech_function)(iProduct *product, std::ostream & ostr));

		bool load(void);
		int list(const char* sub_desc = nullptr);
		void deallocate(void);
		void save(void);
		int search(int sku) const;
		void remove(int index);
		void sort(void);
		void ship(void);

		std::string m_data_file_name;
		bool add_product_to_array(iProduct* product_ptr);

    public:

        

		friend class AidMan;

       

    };

}

#endif // !SDDS_AID_HELPER_H