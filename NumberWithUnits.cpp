#include "NumberWithUnits.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
using namespace std;


namespace ariel{
  
			NumberWithUnits::NumberWithUnits(double u,string t){
        unit=u;
        type=t;
      }
			void NumberWithUnits::read_units(ifstream &text){

      }

			NumberWithUnits operator + (const NumberWithUnits &num1, const NumberWithUnits &num2){
        return NumberWithUnits(0,"");
      }
			NumberWithUnits operator += (NumberWithUnits &num1,const NumberWithUnits &num2){
        return NumberWithUnits(0,"");
      }
			NumberWithUnits operator + (const NumberWithUnits& num1){
        return NumberWithUnits(0,"");
      }
			NumberWithUnits operator - (const NumberWithUnits &num1, const NumberWithUnits &num2){
        return NumberWithUnits(0,"");
      }
			NumberWithUnits operator -= (NumberWithUnits &num1,const NumberWithUnits &num2){
        return NumberWithUnits(0,"");
      }
			NumberWithUnits operator - (const NumberWithUnits& num1){
        return NumberWithUnits(0,"");
      }
			NumberWithUnits operator* (const double mult, const NumberWithUnits &num){
        return NumberWithUnits(0,"");
      }
      NumberWithUnits operator* (const NumberWithUnits &num, const double mult){
        return NumberWithUnits(0,"");
      }

			bool NumberWithUnits::operator>(const NumberWithUnits &num) const{
        return false;
      }
      bool NumberWithUnits::operator>=(const NumberWithUnits &num) const{
        return false;
      }
      bool NumberWithUnits::operator<(const NumberWithUnits &num) const{
        return false;
      }
      bool NumberWithUnits::operator<=(const NumberWithUnits &num) const{
        return false;
      }
			bool NumberWithUnits::operator==(const NumberWithUnits &num) const{
        return false;
      }
      bool NumberWithUnits::operator!=(const NumberWithUnits &num) const{
        return false;
      }

			NumberWithUnits& NumberWithUnits::operator++(){
        return *this;
      }         
      const NumberWithUnits NumberWithUnits::operator++(int){
        return NumberWithUnits(0,"");
      }
      NumberWithUnits& NumberWithUnits::operator--(){
        return *this;
      }       
      const NumberWithUnits NumberWithUnits::operator--(int){
        return NumberWithUnits(0,"");
      }

			ostream& operator<<(ostream &os, const NumberWithUnits &num){
        os << num.unit << "[" << num.type << "]";
        return os;
      }
      istream& operator>>(istream &is, NumberWithUnits &num){
        return is;
      }

};