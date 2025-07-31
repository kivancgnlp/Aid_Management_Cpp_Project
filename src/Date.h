
/*  Date.h Version 3 */

#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include "Status.h"
#include <string>
#include <ctime>

namespace sdds {

	const unsigned c_year_min{ 2022 };
	const unsigned c_year_max{ 2030 };

	const unsigned c_month_min{ 1 };
	const unsigned c_month_max{ 12 };

	const unsigned c_day_min{ 1 };
	//const int c_day_max{ 31 };

	class Date {
		unsigned m_day;
		unsigned m_month;
		unsigned m_year;
		Status m_status;
		bool m_formatted;

		void set_to_now(void);
		
		int unique_date_value(void) const;
		

	public:
		Date(void);
		Date(int year, int month, int day);

		bool operator<(const Date &other) const;
		bool operator<=(const Date &other) const;

		bool operator>(const Date &other) const;
		bool operator>=(const Date &other) const;

		bool operator==(const Date &other) const;
		bool operator!=(const Date &other) const;

		operator bool() const;
		Date & formatted(bool fmt);
		bool is_formatted(void) const;

		int get_day(void) const;
		int get_mon(void) const;
		int get_year(void) const;

		void set_day(int day) ;
		void set_mon(int mon) ;
		void set_year(int year) ;
		void set_state(Status status);

		Status state(void) const;
		bool validate(void);
		
		
	};


	std::ostream & operator<<(std::ostream & os, const Date & date);
	std::istream & operator>>(std::istream & is, Date & date);

	
}

#endif // !SDDS_DATE_H