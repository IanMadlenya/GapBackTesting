//
// Copyright (c) 2016 Yatpang Cheung. All rights reserved.
//

#ifndef __DailyRecord__
#define __DailyRecord__

#include <stdio.h>
#include "DateTime.h"

//class object to hold a day record
class DailyRecord{
    
    friend istream& operator>>(istream &, DailyRecord &);
    friend ostream& operator<<(ostream &, const DailyRecord &);
    
public:
    
    Date date;
    double open = 0;
    double high = 0;
    double low = 0;
    double close = 0;
    double volume = 0;
    double adjustedClose = 0;
    
    DailyRecord(){};
    
};

#endif /* defined(__DailyRecord__) */
