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
            units[to][from]=1/num2;
          }
      }

      double NumberWithUnits::convert (const string from, const string to, double num){
            double sum;
            if (units.at(from).contains(to)==true){
              return num*units.at(from).at(to);
            }
            else{
              sum=1;
              string local_from=from;
              string local_to=units.find(from)->first;
              while(local_to==to){
                sum*=units.at(local_from).at(local_to);
                try{
                  local_from=local_to;
                  local_to=units.find(local_from)->first;
                }
                catch(const exception& e) {
                  throw invalid_argument{"illeagal operation"};
                }
              }
              sum*=units.at(local_from).at(to);
            }
            return sum*num;
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
        unit++;
        return *this;
      }         
      const NumberWithUnits NumberWithUnits::operator++(int){
        int u=unit;
        unit++;
        return NumberWithUnits(u,type);
      }
      NumberWithUnits& NumberWithUnits::operator--(){
        unit--;
        return *this;
      }       
      const NumberWithUnits NumberWithUnits::operator--(int){
        int u=unit;
        unit--;
        return NumberWithUnits(u,type);
      }

			ostream& operator<<(ostream &os, const NumberWithUnits &num){
        os << num.unit << "[" << num.type << "]";
        return os;
      }
      istream& operator>>(istream &is, NumberWithUnits &num){
        char a1='[';
        char a2=']';
        is>>num.unit>>a1>>num.type;
        return is;
      }

};