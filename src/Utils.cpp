/*  Utils.cpp Version 3  (Extra parse functions) */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstring>
#include "Utils.h"
#include <fstream>
#include <stdexcept>
#include "Perishable.h"
using namespace std;

namespace sdds {
   Utils ut;
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }

   void Utils::skip_sku(bool skip){
	   m_skip_sku = skip;
   }

   void Utils::alocpy(char *& destination, const char * src) {

	   if (destination != nullptr) {
		   delete[] destination;
		   destination = nullptr;
	   }

	   if (src == nullptr) {
		   destination = nullptr;
		   return;
	   }


	   size_t str_len = std::strlen(src);
	   destination = new char[str_len + 1];

	   memcpy(destination, src, str_len + 1);

   }

   

   void Utils::parse_item_line(std::ifstream & ifs, Item & item){
	   //char *token = nullptr;
	   std::size_t line_size = 0;
	   std::string token_str;

	   ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
	
	   if (!ut.m_skip_sku) {
		   std::getline(ifs, token_str, '\t');
		   item.m_sku_number = std::stoi(token_str);
	   }	   

	   std::getline(ifs, token_str, '\t');
	   item.m_description = token_str;

	   std::getline(ifs, token_str, '\t');
	   item.m_qty = std::stoi(token_str);

	   std::getline(ifs, token_str, '\t');
	   item.m_qty_needed = std::stoi(token_str);

	   Perishable* pers = dynamic_cast<Perishable*>(&item); // downcast possible ?

	   if (pers == nullptr) {
		   std::getline(ifs, token_str, '\n');
		   item.m_price = std::stod(token_str);
	   } else {
		   std::getline(ifs, token_str, '\t');
		   item.m_price = std::stod(token_str);
	   }
	   	   

	   if (pers) {
		   std::getline(ifs, token_str, '\t');
		   pers->m_handling_instructions = token_str;

		   std::getline(ifs, token_str, '\n');
		   std::istringstream date_str_stream(token_str);
		   date_str_stream >> pers->m_expiry; 
	   }

	   


	  
   }

 
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }

   int Utils::get_int(std::istream & istr, const unsigned min_limit, const unsigned max_limit, const char * prompt){
	   unsigned integer_input = 0;

	   std::ios_base::iostate ex_mask = istr.exceptions();
	   istr.exceptions(std::istream::failbit | std::istream::badbit | std::istream::eofbit);

	   std::ostringstream err_message_str;
	   err_message_str << "Value out of range [" << min_limit << " <= val <= " << max_limit << "]";
	   
	   while (true) {
		   try{

			   cout << prompt;
			   istr.clear();
			   istr >> integer_input;
		
			   if (integer_input >= min_limit && integer_input <= max_limit) {
				   break;
			   } else {
				   cout << err_message_str.str() << endl;
			   }

			}catch (const std::exception &ex){
			   cout << "Invalid Integer, retry" << endl;
			   istr.clear();
			   istr.ignore(10, '\n');

		   }
		  
		 
	   }

	   istr.exceptions(ex_mask);
	   return integer_input;
   }

   double Utils::get_double(std::istream & istr, const double min_limit, const double max_limit, const char * prompt){
	   double double_input = 0;

	   std::ios_base::iostate ex_mask = istr.exceptions();
	   istr.exceptions(std::istream::failbit | std::istream::badbit | std::istream::eofbit);

	   std::ostringstream err_message_str;
	   err_message_str << "Value out of range [" << min_limit << " <= val <= " << max_limit << "]";

	   while (true) {
		   try {

			   cout << prompt;
			   istr.clear();
			   istr >> double_input;



			   if (double_input >= min_limit && double_input <= max_limit) {
				   break;
			   }
			   else {
				   cout << err_message_str.str() << endl;
			   }



		   }
		   catch (const std::exception &ex) {
			   cout << "Invalid double, retry" << endl;
			   istr.clear();
			   istr.ignore(10, '\n');

		   }


	   }

	   istr.exceptions(ex_mask);
	   return double_input;
   }
   
}
