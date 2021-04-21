#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include "doctest.h"
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;


TEST_CASE("read_units"){
    ifstream units_file{"units.txt"};
    CHECK_NOTHROW(NumberWithUnits::read_units(units_file));
}

TEST_CASE ("math operators checks"){
    NumberWithUnits obj1{10,"cm"};
    NumberWithUnits obj2{32,"cm"};
    NumberWithUnits obj3{42,"cm"};
    NumberWithUnits obj4{100,"cm"};
    NumberWithUnits obj5{1,"m"};
    NumberWithUnits obj6{1.1,"m"};
    NumberWithUnits obj7{3,"kg"};
    NumberWithUnits obj8{0.1,"m"};


    //check +
    CHECK_EQ(obj1+obj2, obj3);//cm+cm=cm
    CHECK_EQ(obj5+obj1, obj6);//m+cm=m
    //check -
    CHECK_EQ(obj3-obj2, obj1);//cm-cm=cm
    CHECK_EQ(obj6-obj5, obj8);//m-m=m
    //check =+
    obj1+=obj2;//cm+=cm
    CHECK_EQ(obj1,obj3);
    obj5+=obj6;//m+=m
    CHECK_EQ(obj5,NumberWithUnits{2.1, "m"});
    //check =-
    obj3=-obj2;
    CHECK_EQ(obj3,NumberWithUnits{-32, "cm"});//cm=-cm=cm
    obj4=-obj3;
    CHECK_EQ(obj4,-obj3);//cm=-cm=cm
    //check unary +
    CHECK_EQ(+obj8,NumberWithUnits{0.1,"m"});//the object sould stay the same 
    ////check unary -
    CHECK_EQ(-obj7,NumberWithUnits{-3,"kg"});//the object suld be negative 
    //using math operator with different type
    CHECK_THROWS(obj4+obj7);//cm+kg-> exception
    CHECK_THROWS(obj7-obj1);//kg-cm-> exception
    CHECK_THROWS(obj4+=obj7);//cm+=kg-> exception
    CHECK_THROWS(obj4-=obj7);//cm-=kg-> exception

}

TEST_CASE ("basic comparison operators check"){
    NumberWithUnits obj10{60,"min"};
    NumberWithUnits obj11{10,"min"};
    NumberWithUnits obj12{1,"hour"};
    NumberWithUnits obj13{4,"hour"};
    NumberWithUnits obj14{420,"min"};
    NumberWithUnits obj15{600,"sec"};
    NumberWithUnits obj16{10,"sec"};
    NumberWithUnits obj17{5,"ton"};

    //check <
    CHECK_EQ(obj11<obj10, true);//min<min
    CHECK_EQ(obj13<obj12, false);//hour<hour
    CHECK_EQ(obj11<obj12, true);//min<hour
    CHECK_EQ(obj16<obj12, true);//sec<hour
    //check <=
    CHECK_EQ(obj10<=obj12, true);//min<=hour
    CHECK_EQ(obj14<=obj13, true);//min<=hour
    CHECK_EQ(obj11<=obj10, true);//min<=min
    CHECK_EQ(obj15<=obj16, false);//sec<=sec
    //check >
    CHECK_EQ(obj10>obj11, true);//min>min
    CHECK_EQ(obj12>obj13, false);//hour>hour
    CHECK_EQ(obj12>obj11, true);//min>hour
    CHECK_EQ(obj12>obj16, true);//sec>hour
    //check >=
    CHECK_EQ(obj12>=obj10, true);//min>=hour
    CHECK_EQ(obj13>=obj14, true);//min>=hour
    CHECK_EQ(obj10>=obj11, true);//min>=min
    CHECK_EQ(obj16>=obj15, false);//sec>=sec
    //check ==
    CHECK_EQ(obj10==obj12, true);//60 min==1 hour
    CHECK_EQ(obj13==obj14, true);//240 min==4 hour
    CHECK_EQ(obj12==obj15, true);//600 sec==1 hour
    CHECK_EQ(obj11==obj16, false);//10 sec!=10 min
    //check !=
    CHECK_EQ(obj10!=obj12, false);//60 min!=1 hour
    CHECK_EQ(obj13!=obj14, false);//240 min!=4 hour
    CHECK_EQ(obj11!=obj16, true);//10 sec!=10 min
}

TEST_CASE ("++ and -- operators checks"){
    NumberWithUnits obj20{1,"kg"}; 

    //pefix ++
    CHECK_EQ(++obj20,NumberWithUnits{2,"kg"});
    //postfix ++
    obj20++;
    CHECK_EQ(obj20,NumberWithUnits{3,"kg"});
    CHECK_EQ(obj20++,NumberWithUnits{3,"kg"});
    CHECK_EQ(obj20,NumberWithUnits{4,"kg"});
    //pefix --
    CHECK_EQ(--obj20,NumberWithUnits{3,"kg"});
    //postfix --
    obj20--;
    CHECK_EQ(obj20,NumberWithUnits{2,"kg"});
    CHECK_EQ(obj20--,NumberWithUnits{2,"kg"});
    CHECK_EQ(obj20,NumberWithUnits{1,"kg"});
}

TEST_CASE ("* operator checks"){
    NumberWithUnits obj30{1,"kg"}; 
    CHECK_EQ(obj30*4,NumberWithUnits{4,"kg"});
    CHECK_EQ(3*obj30,NumberWithUnits{3,"kg"});

}
