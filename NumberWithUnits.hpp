#pragma once
#include <iostream>
#include <string>
#include <map>

namespace ariel{
		class NumberWithUnits{
	
		private:
			double unit;
			std::string type;
			static std::map<std::string, std::map<std::string, double> > units;


		public:
			NumberWithUnits(double, std::string);
			static void read_units(std:: ifstream&);

			friend NumberWithUnits operator + (const NumberWithUnits &num1, const NumberWithUnits &num2);
			friend NumberWithUnits operator += (NumberWithUnits &num1,const NumberWithUnits &num2);
			friend NumberWithUnits operator + (const NumberWithUnits& num1, double add);
			friend NumberWithUnits operator - (const NumberWithUnits &num1, const NumberWithUnits &num2);
			friend NumberWithUnits operator -= (NumberWithUnits &num1,const NumberWithUnits &num2);
			friend NumberWithUnits operator - (const NumberWithUnits& num1);
			friend NumberWithUnits operator* (const double mult, const NumberWithUnits &num);
        	friend NumberWithUnits operator* (const NumberWithUnits &num, const double mult);

			bool operator>(const NumberWithUnits &num) const;
        	bool operator>=(const NumberWithUnits &num) const;
        	bool operator<(const NumberWithUnits &num) const;
        	bool operator<=(const NumberWithUnits &num) const;
			bool operator==(const NumberWithUnits &num) const;
        	bool operator!=(const NumberWithUnits &num) const;

			NumberWithUnits& operator++();         
        	const NumberWithUnits operator++(int); 
        	NumberWithUnits& operator--();         
        	const NumberWithUnits operator--(int); 

			friend std::ostream& operator<<(std::ostream &os, const NumberWithUnits &num);
        	friend std::istream& operator>>(std::istream &is, NumberWithUnits &num);

	};
}