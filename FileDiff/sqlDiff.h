#pragma once

#include "string"
#include "map"
#include "vector"
#include "iostream"
#include "stdlib.h"
#include "fstream"
using namespace std;

#define INTERVAL 10000

std::string exec(const char* cmd) ;

class sqlQuery{
    vector<string> column;
    vector<string> value;
public:
    int getDiff(const sqlQuery& sql) const;
    string outDiff(const sqlQuery& sql) const;
    void setValue(const string& key,const string& value);
    string outData() const;
    string GetString() const;

    bool isNumber(const string& s){
        return s.find_first_not_of( "0123456789" ) == string::npos;
    }

    bool IsTimeStamp(const string& time){
        if(time.size()>16||time==""||!isNumber(time)) return false;
        auto temp = time;

        if(temp.size()>15)
            temp.erase(temp.end()-6,temp.end());
        if(temp.size()>=11)
            temp.erase(temp.end()-3,temp.end());
        if(temp.size()>=9)
            return false;
        string curTime = exec( "date +%s" );    //include \n
        curTime.pop_back();

        int runTimeStamp = stoi(temp);
        int curTimeStamp = stoi(curTime);

        return abs(curTimeStamp-runTimeStamp)<INTERVAL;
    }

    bool operator<(const sqlQuery& sql){
        return value<sql.value;
    }
    void toFile(const string& FileName){
        std::ofstream out(FileName,std::ios_base::app);
        for(int i = 0;i<value.size();i++){
            if(!IsTimeStamp(value[i])){
                out<<column[i]<<" = "<<value[i]<< ' ';
            }
        }
        out<<endl;
    }
};
class sqlCompare{
public:
    bool operator()(const sqlQuery& sql1,const sqlQuery& sql2);
};
string getDiffofSqldiff(const vector<sqlQuery> &d1,const vector<sqlQuery>& d2);

