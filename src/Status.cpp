
/*  Status.cpp Version 3 */

#include "Status.h"
#include "Utils.h"
#include <iostream>
#include <string>

namespace sdds {
	
	Status::Status(int status_code, const char *err_text) { // Default ctor
		m_status_code = status_code;
		m_err_text_c_ptr = nullptr;
		Utils::alocpy(m_err_text_c_ptr, err_text);

	}

	Status::Status(const Status & srcStatus) { // copy ctor
		m_status_code = srcStatus.m_status_code;
		m_err_text_c_ptr = nullptr;
		Utils::alocpy(m_err_text_c_ptr, srcStatus.m_err_text_c_ptr);
	}

	Status & Status::operator=(const Status & srcStatus){ // assign operator
		m_status_code = srcStatus.m_status_code;
		Utils::alocpy(m_err_text_c_ptr, srcStatus.m_err_text_c_ptr);
		return *this;
	}


	Status::~Status(void){
		//std::cout << "Status dtor" << std::endl;

		if (m_err_text_c_ptr) {
			delete[] m_err_text_c_ptr;
		}
		
		m_err_text_c_ptr = nullptr;

	}

	Status & Status::operator=(const int status_code) { // int assign operator
		m_status_code = status_code;
		return *this;
	}

	Status & Status::operator=(const char *err_text) { // text assign operator

		Utils::alocpy(m_err_text_c_ptr, err_text);

		return *this;
	}


	Status::operator bool() const{
		return m_err_text_c_ptr == nullptr;
	}

	Status::operator const char*() const{
		return m_err_text_c_ptr;
	}

	Status::operator int() const{
		return m_status_code;

	}

	int Status::getStatusCode(void) const{
		return m_status_code;
	}

	std::string Status::getStatusErrText(void) const{

		return m_err_text_c_ptr;
		
	}

	void Status::clear(void){
		m_status_code = 0;


		if (m_err_text_c_ptr) {
			delete[] m_err_text_c_ptr;
		}
		
		m_err_text_c_ptr = nullptr;

	}

	std::ostream & operator<<(std::ostream & os, const Status & status){
		os << status.getStatusCode() << " : " << status.getStatusErrText();
		return os;
	}


}