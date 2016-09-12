//
// Copyright (c) 2016 Yatpang Cheung. All rights reserved.
//

#include "DailyRecord.h"

istream& operator>>(istream & is, DailyRecord & someRecord){
    
    char holder;
    
    is>>someRecord.date;
    is>>holder;
    is>>someRecord.open;
    is>>holder;
    is>>someRecord.high;
    is>>holder;
    is>>someRecord.low;
    is>>holder;
    is>>someRecord.close;
    is>>holder;
    is>>someRecord.volume;
    is>>holder;
    is>>someRecord.adjustedClose;
    
    return is;
}

ostream& operator<<(ostream & os, const DailyRecord & someRecord){
    
    os<<someRecord.date;
    os<<" ";
    os<<someRecord.open;
    os<<" ";
    os<<someRecord.high;
    os<<" ";
    os<<someRecord.low;
    os<<" ";
    os<<someRecord.close;
    os<<" ";
    os<<someRecord.volume;
    os<<" ";
    os<<someRecord.adjustedClose;
    
    return os;
}