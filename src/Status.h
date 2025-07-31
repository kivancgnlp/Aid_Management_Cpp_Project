
/*  Status.h Version 3 */

#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

#include <string>

namespace sdds {
	
	class Status {
		int m_status_code;
		char *m_err_text_c_ptr;


	public:
		Status(int status_code = 0, const char *err_text = nullptr); // default ctor
		Status(const Status &srcStatus); // copy ctor
		Status &operator=(const Status &); // copy assignment operator
		~Status(void); // dtor

		Status &operator=(const int); //assignment from int operator
		Status &operator=(const char *err_text); // assignment from string operator
		//std::ostream &operator<<(std::ostream &os, const Status & status);
	
		operator bool() const; // convert to bool operator. True if ok
		operator const char* () const; // convert to char* operator
		operator int() const; // convert to int operator

		int getStatusCode(void) const;
		std::string getStatusErrText(void) const;

		void clear(void);
	};
	
	std::ostream & operator<<(std::ostream & os, const Status & status);
}

#endif // !SDDS_STATUS_H