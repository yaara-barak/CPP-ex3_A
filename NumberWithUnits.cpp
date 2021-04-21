#include "NumberWithUnits.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
using namespace std;
const float EPS=0.001;


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
            if (!units.contains(from)){units[from][""]=double{};}
            if (!units.contains(to)){units[to][""]=double{};}
            units.at(from).insert({to,num2});
            units.at(to).insert({from,1/num2});
            for(auto const &map : units[from]){
                units[map.first][to]=1/(map.second * units[to][from]);
                units[to][map.first]=map.second * units[to][from];
            }
            for(auto const &map : units[to]){
                units[map.first][from]=1/(map.second *units[from][to] );
                units[from][map.first]=map.second * units[from][to];
            }
          }
      }

      double NumberWithUnits::convert (const string from, const string to, double num){
            double sum;
            try{
                sum=units.at(from).at(to);
            }
            catch(const exception& e){
              throw invalid_argument{"illeagal operation"};
            }
            //cout <<num <<" "<<from <<" is "<<num*units.at(from).at(to)<<" "<<to<<endl;
            return num*units.at(from).at(to);
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
          if (type!=num.type && !units.at(type).contains(num.type)){
            throw invalid_argument("illeagal operation");
          }
          if (type==num.type){
            return (unit>num.unit);
          }
          else{
            return convert(type,num.type,unit)>num.unit;
          }
      }
      bool NumberWithUnits::operator>=(const NumberWithUnits &num) const{
          if (type!=num.type && !units.at(type).contains(num.type)){
            throw invalid_argument("illeagal operation");
          }
          if (type==num.type){
            return (unit>=num.unit);
          }
          else{
            return convert(type,num.type,unit)>=num.unit;
          }
      }
      bool NumberWithUnits::operator<(const NumberWithUnits &num) const{
        if (type!=num.type && !units.at(type).contains(num.type)){
            throw invalid_argument("illeagal operation");
          }
          if (type==num.type){
            return (unit<num.unit);
          }
          else{
            return convert(type,num.type,unit)<num.unit;
          }
      }
      bool NumberWithUnits::operator<=(const NumberWithUnits &num) const{
        if (type!=num.type && !units.at(type).contains(num.type)){
            throw invalid_argument("illeagal operation");
          }
          if (type==num.type){
            return (unit<=num.unit);
          }
          else{
            return convert(type,num.type,unit)<=num.unit;
          }
      }
			bool NumberWithUnits::operator==(const NumberWithUnits &num) const{
        if (type!=num.type && !units.at(type).contains(num.type)){
            throw invalid_argument("illeagal operation");
        }
        if (type==num.type){
            return (unit==num.unit);
        }
        else{
            return abs(convert(type,num.type,unit)-num.unit)>EPS;
        }
      }
      bool NumberWithUnits::operator!=(const NumberWithUnits &num) const{
        if (type!=num.type && !units.at(type).contains(num.type)){
            throw invalid_argument("illeagal operation");
        }
        if (type==num.type){
            return (unit!=num.unit);
        }
        else{
            return convert(type,num.type,unit)!=num.unit;
        }
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
        if (!NumberWithUnits::units.contains(num.type))
          throw invalid_argument{"illeagal operation"};
        return is;
      }

};