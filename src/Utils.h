/*  Utils.h Version 3 (Extra parse functions) */

#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

#include "Item.h"
namespace sdds {
   const int sdds_testYear = 2022;
   const int sdds_testMon = 03;
   const int sdds_testDay = 31;

   class Item; // forward declaration to break cyclic compile dependency

   class Utils {
      bool m_testMode = false;
	  

	public:
      int daysOfMon(int mon, int year)const;
      void testMode(bool testmode = true);
	  void skip_sku(bool skip = true);

	  static void alocpy(char* & destination, const char *src);
	  
	  static void parse_item_line(std::ifstream& ifstr, Item &item);

	  static int get_int(std::istream & istr, const unsigned min, const unsigned max, const char * prompt = nullptr);
	  static double get_double(std::istream & istr, const double min, const double max, const char * prompt = nullptr);

	  bool m_skip_sku = false;
   };
   extern Utils ut;
}

#endif // !SDDS_UTILS_H
