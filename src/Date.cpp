
/*  Date.cpp Version 3 */

#define _CRT_SECURE_NO_WARNINGS


#include "Date.h"

#include "Utils.h"

#include <ctime>
#include <cstdio>
#include <iostream>



namespace sdds {

	bool Date::validate(void){

		if (m_year < c_year_min || m_year > c_year_max) {

			m_status = Status(1, "Invalid year in date");
			return false;
		}

		
		if (m_month < c_month_min || m_month > c_month_max) { 

			m_status = Status(2, "Invalid month in date");
			return false;
		}

		unsigned month_max = ut.daysOfMon(m_month,m_year);

		if (m_day < c_day_min || m_day > month_max) { 

			m_status = Status(3, "Invalid day in date");
			return false;
		}


		m_status = Status(0);

		return true;
	}

	Date::Date(void) {

		m_formatted = true;

		set_to_now();

		validate();//
		
	}

	Date::Date(int year, int month, int day){
		m_day = day;
		m_month = month;
		m_year = year;

		validate();
	}

	

	void Date::set_to_now(void) {
		std::time_t m_current_time;

		m_current_time = std::time(0);   // get time now

		std::tm* local_time = std::localtime(&m_current_time);

		m_day = local_time->tm_mday;
		m_month = local_time->tm_mon + 1 ;
		m_year = local_time->tm_year + 1900;

	}

	int Date::unique_date_value(void) const {

		return m_year * 372 + m_month * 31 + m_day;
	}

	bool Date::operator<(const Date & other) const{
		return unique_date_value() < other.unique_date_value();
	}

	bool Date::operator<=(const Date & other) const{
		return unique_date_value() <= other.unique_date_value();
	}

	bool Date::operator>(const Date & other) const{
		return unique_date_value() > other.unique_date_value();
	}

	bool Date::operator>=(const Date & other) const{
		return unique_date_value() >= other.unique_date_value();
	}

	bool Date::operator==(const Date & other) const{
		return unique_date_value() == other.unique_date_value();
	}

	bool Date::operator!=(const Date & other) const{
		return unique_date_value() != other.unique_date_value();
	}

	Date::operator bool() const{

		return m_status.getStatusCode() == 0;
	}

	Date & Date::formatted(bool fmt){
		m_formatted = fmt;
		return *this;
	}

	bool Date::is_formatted(void) const{
		return m_formatted;
	}

	int Date::get_day() const
	{
		return m_day;
	}

	int Date::get_mon() const
	{
		return m_month;
	}

	int Date::get_year() const
	{
		return m_year;
	}

	void Date::set_day(int day){
		m_day = day;
	}

	void Date::set_mon(int mon){
		m_month = mon;
	}

	void Date::set_year(int year){
		m_year = year;
	}

	void Date::set_state(Status status){
		m_status = status;
	}

	Status Date::state(void) const{
		return m_status;
	}



	std::ostream & operator<<(std::ostream & os, const Date & date){
		char buffer[20];

		if (date.is_formatted()) {
			snprintf(buffer, sizeof(buffer), "%04d/%02d/%02d", date.get_year(), date.get_mon(), date.get_day());
		}else {
			snprintf(buffer, sizeof(buffer), "%02d%02d%02d", date.get_year() % 100, date.get_mon(), date.get_day());
		}

		os << buffer;
		return os;
	}

	std::istream & operator>>(std::istream & is, Date & date){
		int day, mon, year;
		char day_c[3] = { 0 };
		char mon_c[3] = { 0 };
		char year_c[3] = { 0 };
		int scanf_ret;
		bool year_parse_ok = false;
		bool mon_parse_ok = false;
		bool day_parse_ok = false;


		is.get(year_c, 3);

		if (is) {
			scanf_ret = sscanf(year_c, "%d", &year);
			if (scanf_ret == 1) {
				year_parse_ok = true;
			}
		}

		if (!year_parse_ok) goto parse_err_exit;

		is.get(mon_c, 3);

		if (is) {
			scanf_ret = sscanf(mon_c, "%d", &mon);
			if (scanf_ret == 1) {
				mon_parse_ok = true;
			}
		}

		if (!mon_parse_ok) goto parse_err_exit;

		is.get(day_c, 3);

		if (is) {
			scanf_ret = sscanf(day_c, "%d", &day);
			if (scanf_ret == 1) {
				day_parse_ok = true;
			}
		}

		if (!day_parse_ok) goto parse_err_exit;
		
		//std::cout << "parse full ok exit" << std::endl;

		date.set_year(2000 + year);
		date.set_mon(mon);
		date.set_day(day);

		date.set_state(Status(0));
		date.validate();

		if (!date) {
			is.setstate(std::ios::badbit);
		}
		else {
			is.clear();
		}

		is.ignore();

		return is;


	parse_err_exit:
		

		if (year_parse_ok && mon_parse_ok  /* but not day */) {

			std::cout << "parse exit 2 ( no year )" << std::endl;

			date.set_year(2022); // TODO : get current year
			date.set_mon(year);
			date.set_day(mon);

			date.set_state(Status(0));
			date.validate();

			if (!date) {
				is.setstate(std::ios::badbit);
			}
			else {
				is.clear();
			}
		}
		else {
			std::cout << "parse exit 3 ( invalid input )" << std::endl;

			date.set_state(Status(4, "Invalid date value"));
			is.setstate(std::ios::badbit);

		}



		is.ignore();
		return is;
	}

}

