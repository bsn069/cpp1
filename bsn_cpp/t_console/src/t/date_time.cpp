#include <bsn/template_console/include/t/t.h>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

T_void
date_time_()
{
	auto printDate = [](date& d){
		cout << endl;
		cout << "to_simple_string(d)=" << to_simple_string(d) << endl;
		cout << "to_iso_string(d)=" << to_iso_string(d) << endl;
		cout << "to_iso_extended_string(d)=" << to_iso_extended_string(d) << endl;
		cout << "d.year()=" << d.year() << endl;
		cout << "d.month()=" << d.month() << endl;
		cout << "d.day()=" << d.day() << endl;
		//cout << "d.year_month_day()=" << d.year_month_day() << endl;
		cout << "d.is_special()=" << d.is_special() << endl;
		cout << "d.is_not_a_date()=" << d.is_not_a_date() << endl;
		cout << "d.is_infinity()=" << d.is_infinity() << endl;
		cout << "d.is_pos_infinity()=" << d.is_pos_infinity() << endl;
		cout << "d.is_neg_infinity()=" << d.is_neg_infinity() << endl;
		cout << "d.day_count()=" << d.day_count() << endl;
		cout << "d.as_special()=" << d.as_special() << endl;
		cout << "d.julian_day()=" << d.julian_day() << endl;
		cout << "d.modjulian_day()=" << d.modjulian_day() << endl;
		cout << "d.day_number()=" << d.day_number() << endl;
		cout << "d.day_of_year()=" << d.day_of_year() << endl;
		cout << "d.day_of_week()=" << d.day_of_week() << endl;
		cout << "d.week_number()=" << d.week_number() << endl;
		cout << "d.end_of_month()=" << d.end_of_month() << endl;

	};

	{
		cout << endl;
		cout << "date_time" << endl;
		
		date d(2014,5,6);
		printDate(d);

		d = from_string("2015-5-6");
		printDate(d);

		tm t = to_tm(d);
		d = date_from_tm(t);
		printDate(d);
	}
 
}
