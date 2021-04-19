#include "NumberWithUnits.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
using namespace std;


namespace ariel{
  
			map<string, map<string, double> > NumberWithUnits::units;
      
      NumberWithUnits::NumberWithUnits(double u,string t){
        unit=u;
        type=t;
      }
			
      void NumberWithUnits::read_units(ifstream &text){
          double num1,num2;
          string from, to, op;
          while(text >> num1 >> from >> op >> num2 >> to){
            //add to the map the units
            units[from][to]=num2;
            units[to][from]=(double)1/num2;
            //create new proportion
            for(auto [unit, type] : units[to]){
              units[from][unit] = type*units[from][to];
              units[unit][from] = (double)1/type*units[from][to];
            }
            for(auto [unit, type] : units[from]){
              units[to][unit] = type*units[to][from];
              units[unit][to] = (double)1/type*units[to][from];
            }
          }
      }

      double NumberWithUnits::convert (const string from, const string to, double num){
            if (!(units.at(from).contains(to))){
              throw invalid_argument{"illeagal operation"};
            }
            return num*units.at(to).at(from);
      }

			NumberWithUnits operator + (const NumberWithUnits &num1, const NumberWithUnits &num2){
        double n2= NumberWithUnits::convert(num2.type, num1.type, num2.unit);
        double sum= num1.unit+n2;
        return NumberWithUnits(sum,num1.type);
      }
			NumberWithUnits operator += (NumberWithUnits &num1,const NumberWithUnits &num2){
        double n2= NumberWithUnits::convert(num2.type, num1.type, num2.unit);
        num1.unit+=n2;
        return num1;
      }
			NumberWithUnits operator + (const NumberWithUnits& num1){
        return num1;
      }
			NumberWithUnits operator - (const NumberWithUnits &num1, const NumberWithUnits &num2){
        double n2= NumberWithUnits::convert(num2.type, num1.type, num2.unit);
        double sum= num1.unit-n2;
        return NumberWithUnits(sum,num1.type);
      }
			NumberWithUnits operator -= (NumberWithUnits &num1,const NumberWithUnits &num2){
        double n2= NumberWithUnits::convert(num2.type, num1.type, num2.unit);
        num1.unit-=n2;
        return num1;
      }
			NumberWithUnits operator - (const NumberWithUnits& num1){
        return NumberWithUnits(num1.unit*(-1),num1.type);
      }
			NumberWithUnits operator* (const double mult, const NumberWithUnits &num){
        
        return NumberWithUnits(num.unit*mult,num.type);
      }
      NumberWithUnits operator* (const NumberWithUnits &num, const double mult){
        return NumberWithUnits(num.unit*mult,num.type);
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