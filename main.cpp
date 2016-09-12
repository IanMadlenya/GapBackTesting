//
// Copyright (c) 2016 Yatpang Cheung. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "DailyRecord.h"
#include <algorithm>
using namespace std;

// file access paths for data
const string equitiesDataBase = "/Users/.../equitiesData/";
const string allTickersPath = "/Users/.../exchangeData/Tickers.txt";

// struct to store a transaction details
struct trade{
    string ticker;
    double marketCap;
    string sector;
    
    //close to close return
    double CTC;
    
    //close to open return
    double returnCTO;
    
    //overloading < operator so C++ algorithm will sort the struct properly
    bool operator<(const trade& rhs) const { return CTC < rhs.CTC;}
};

// function to load the data
void loadData(vector<string> & tickers, vector<double> & marketCaps, vector<string> & sectors,
              vector<vector<DailyRecord>> & daily_record){
    
    //opens ticker file to read all the tickers
    ifstream listFile;
    listFile.open(allTickersPath.c_str());
    
    string ticker_name;
    string sector;
    double marketCap;
    int line = 1;
    string fileline;
    
    if(!listFile){
        cout<<"Failed to open Ticker list"<<endl;
    }else{
    
        while(getline(listFile, fileline)){
//            if(line > 50){
//                break;
//            }
            
            //parse out ticker file line content
            stringstream ss(fileline);
            ss>>ticker_name>>marketCap>>sector;
            
            //for every ticker, open the historical data file and parse and store
            ifstream indFile;
            indFile.open((equitiesDataBase+ticker_name+".csv"));
            
            if(!indFile){
                cout<<ticker_name<<" failed to open."<<endl;
            }else{
                vector<DailyRecord> tempVec;
                DailyRecord tempRec;
                
                string header;
                getline(indFile, header);
                while(indFile>>tempRec){
                    tempVec.push_back(tempRec);
                }
                
                //only stocks with at least some number of trading data
                if(tempVec.size() > 1000){
                    tickers.push_back(ticker_name);
                    sectors.push_back(sector);
                    marketCaps.push_back(marketCap);
                    daily_record.push_back(tempVec);
                }
                
                indFile.close();
                cout<<line<<" "<<"opened: "<<ticker_name<<endl;
            }
            line++;
        }
        listFile.close();
    }
}

//daily strategy to buy the worst performers and sell at next day market open
void buyWorstCTO(vector<string> & tickers, vector<double> & marketCaps, vector<string> & sectors,
                 vector<vector<DailyRecord>> & daily_record, vector<double> & dailyReturnOfStrat){
    
    dailyReturnOfStrat.push_back(1);
    
    //for each day
    for( int i =1000; i>0; i--){
        
        vector<trade> returnDay;
        
        //for each ticker
        for(int j=0; j<tickers.size(); j++){
            
            //only consider stocks that traded the following criteria (feel free to adjust):
            //such as trading at least $1m that day
            if(daily_record[j][i].volume * daily_record[j][i].adjustedClose > 1000000){
                
                //calculation also calculates for adjusted open based on adjusted close
                double returnVal = daily_record[j][i].adjustedClose/daily_record[j][i+1].adjustedClose;
                double pnlretCTO =
                    (daily_record[j][i-1].open*daily_record[j][i-1].adjustedClose/daily_record[j][i-1].close)
                    /daily_record[j][i].adjustedClose;

                //store the transaction
                trade aTrade;
                aTrade.ticker = tickers[j];
                aTrade.marketCap = marketCaps[j];
                aTrade.sector = sectors[j];
                aTrade.CTC = returnVal;
                aTrade.returnCTO = pnlretCTO;
    
                returnDay.push_back(aTrade);
            }
        }
        
        //sort based on worst performer
        sort(returnDay.begin(), returnDay.end());
        
        double totalWeight = 0;
        for(int j = 0; j<15; j++){
            if(returnDay[j].CTC < 1){
                totalWeight += (1-returnDay[j].CTC);
            }
        }
        
        //purchase worst performers based on a weight directly proportional to
        //magnitude of price drop
        double totalDayRet = 0;
        if(totalWeight != 0){
            for(int j = 0; j<15; j++){
                if(returnDay[j].CTC < 1){
                    totalDayRet += ((1-returnDay[j].CTC)/totalWeight)*returnDay[j].returnCTO;
                    //print to terminal the worst performers that we are buying
                    cout<<returnDay[j].ticker<<":"<<returnDay[j].CTC<<"   ";
                }
            }
        }else{
            //in the event of no negative performers
            totalDayRet = 1;
        }
        cout<<endl<<endl;
        
        dailyReturnOfStrat.push_back((totalDayRet)*dailyReturnOfStrat[dailyReturnOfStrat.size()-1]);
    }
}

int main(int argc, const char * argv[]) {
    
    vector<string> tickers;
    vector<double> marketCaps;
    vector<string> sectors;
    vector<vector<DailyRecord>> daily_record;
    vector<double> dailyReturnOfStrat;
    vector<double> strat_total_return;
    
    loadData(tickers, marketCaps, sectors, daily_record);
    buyWorstCTO(tickers, marketCaps, sectors, daily_record, dailyReturnOfStrat);
    
    //outputs daily return values of the strategy to a file as well as terminal
    ofstream output;
    string outputfile = "/Users/.../output.txt";
    output.open(outputfile.c_str());
    
    for(int i =0; i<dailyReturnOfStrat.size(); i++){
        cout<<dailyReturnOfStrat[i]<<endl;
        output << dailyReturnOfStrat[i]<<endl;
    }
    return 0;
}

