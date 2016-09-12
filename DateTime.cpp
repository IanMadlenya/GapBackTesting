//
// Copyright (c) 2016 Yatpang Cheung. All rights reserved.
//

#include "DateTime.h"

ostream& operator<<(ostream& os, const Date &rhsObj)
{
    //forward slash for formatting (mm/dd/yyyy)
    os << rhsObj.mm;
    os << "-";
    os << rhsObj.dd;
    os << "-";
    os << rhsObj.yyyy;
    return os;
}

istream& operator>>(istream& is, Date &rhsObj)
{
    //this function assumes that dates will be in the format (yyyy/mm/dd)
    char ch;
    
    is >> rhsObj.yyyy;
    is >> ch; //extract the forward slash, not need to be stored
    
    is >> rhsObj.mm;
    is >> ch; //extract the forward slash
    
    is >> rhsObj.dd;
    
    
    return is;
}

//constructor with parameters
Date::Date(int year, int month, int day)
{
    yyyy = year;
    mm = month;
    dd = day;
}

//copy constructor
Date::Date(const Date& otherObj)
{
    setDate(otherObj);
}

void Date::setDate(int year, int month, int day)
{
    yyyy = year;
    mm = month;
    dd = day;
}

//helper function with copy constructor
void Date::setDate(const Date & otherObj)
{
    this->dd=otherObj.dd;
    this->mm=otherObj.mm;
    this->yyyy=otherObj.yyyy;
}

int Date::getDate() const
{
    return dd;
}

int Date::getMonth() const
{
    return mm;
}

int Date::getYear() const
{
    return yyyy;
}

bool Date::operator==(const Date& rhsObj) const
{
    bool Answer = false;
    
    if ( this->yyyy == rhsObj.yyyy && this->mm == rhsObj.mm && this->dd == rhsObj.dd )
    {
        Answer = true;
    }
    
    
    return Answer;
}

bool Date::operator!=(const Date& rhsObj) const
{
    bool Answer = true;
    
    if( this->yyyy == rhsObj.yyyy && this->mm == rhsObj.mm && this->dd == rhsObj.dd )
    {
        Answer = false;
    }
    
    return Answer;
}

bool Date::operator<=(const Date & rhsObj) const
{
    bool Answer = false;
    if( (this->yyyy == rhsObj.yyyy && this->mm == rhsObj.mm && this->dd <= rhsObj.dd)
        || (this->yyyy == rhsObj.yyyy && this->mm < rhsObj.mm)
        || (this->yyyy < rhsObj.yyyy))
       {
           Answer = true;
       }
       return Answer;
}

bool Date::operator< (const Date & rhsObj) const
{
    bool Answer = false;
    if( (this->yyyy == rhsObj.yyyy && this->mm == rhsObj.mm && this->dd < rhsObj.dd)
       || (this->yyyy == rhsObj.yyyy && this->mm < rhsObj.mm)
       || (this->yyyy < rhsObj.yyyy))
    {
        Answer = true;
    }
    return Answer;
}

bool Date::operator>=(const Date & rhsObj) const
{
    bool Answer = false;
    if( (this->yyyy == rhsObj.yyyy && this->mm == rhsObj.mm && this->dd >= rhsObj.dd)
       || (this->yyyy == rhsObj.yyyy && this->mm > rhsObj.mm)
       || (this->yyyy > rhsObj.yyyy))
    {
        Answer = true;
    }
    return Answer;
}

bool Date::operator> (const Date & rhsObj) const
{
    bool Answer = false;
    if( (this->yyyy == rhsObj.yyyy && this->mm == rhsObj.mm && this->dd > rhsObj.dd)
       || (this->yyyy == rhsObj.yyyy && this->mm > rhsObj.mm)
       || (this->yyyy > rhsObj.yyyy))
    {
        Answer = true;
    }
    return Answer;
}

const Date& Date::operator= (const Date& rhsObj)
{
    if (this != &rhsObj)
    {
        //not a self assignment, OK to proceed
        dd = rhsObj.dd;
        mm = rhsObj.mm;
        yyyy = rhsObj.yyyy;
    }
    
    return rhsObj;
    
}


















