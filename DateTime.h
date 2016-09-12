//
// Copyright (c) 2016 Yatpang Cheung. All rights reserved.
//

#ifndef __DateTime__
#define __DateTime__

#include <iostream>

using std::ostream;
using std::istream;

class Date
{
    friend ostream& operator<< (ostream&, const Date&);
    friend istream& operator>> (istream&, Date &);
    
public:
    
    //constructor to set date
    Date(int = 0, int=0, int =0);
    
    //constructor to copy date
    Date(const Date&);
    
    //function to set date
    void setDate(int, int, int);
    
    //function to set date through cooy
    void setDate(const Date&);
    
    //returns the day, month, year
    int getDate() const;
    int getMonth() const;
    int getYear() const;
    
    //overloading the operators
    bool operator== (const Date&) const;
    bool operator!= (const Date&) const;
    bool operator<= (const Date&) const;
    bool operator< (const Date&) const;
    bool operator>= (const Date&) const;
    bool operator> (const Date &) const;
    const Date& operator= (const Date&);
    
private:
    
    int mm;
    int dd;
    int yyyy;
    
};

#endif