
#include "Menu.h"
#include "iProduct.h"
#include "AidManFileIOHelper.h"
#include <string>

#ifndef SDDS_AID_H
#define SDDS_AID_H

namespace sdds {

    class AidMan {
        
        Menu m_menu;
		AidManFileIOHelper m_helper;
		
		unsigned menu(void);
		void run_remove_proc(void);
		void run_add_proc(void);
		void run_update_proc(void);
		void run_open_or_create_new_data_file_proc(void);

        

    public:

		AidMan(void); // default ctor
		AidMan(const AidMan & other) = delete; // copy ctor
		~AidMan(void);
		AidMan &operator=(const AidMan & other) = delete; // copy assignment operator
        void run(void);
       

    };

}

#endif // !SDDS_AID_H