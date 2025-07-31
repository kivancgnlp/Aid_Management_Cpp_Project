
/*  iProduct.cpp Version 2 */

#include "iProduct.h"
#include <iostream>
#include <string>


namespace sdds {





	iProduct::~iProduct(){

		//std::cout << "iProduct dtor" << std::endl;
	}

	std::ostream & operator<<(std::ostream & os, const iProduct & iproduct){ // toString
		return iproduct.display(os);
	}

	std::istream & operator>>(std::istream & is, iProduct & iproduct){ // fromString
		return iproduct.read(is);
	}

}