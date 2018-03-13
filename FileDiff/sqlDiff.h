#pragma once

#include "string"
#include "map"
#include "vector"
#include "iostream"


using namespace std;


class sqlQuery{
    vector<string> column;
    vector<string> value;
public:
    int getDiff(const sqlQuery& sql) const;
    string outDiff(const sqlQuery& sql) const;
    void setValue(const string& key,const string& value);
    string outData() const;
};
string getDiffofSqldiff(const vector<sqlQuery> &d1,const vector<sqlQuery>& d2);

