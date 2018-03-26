#ifndef sqLiteReader_hpp
#define sqLiteReader_hpp


#include <stdio.h>
#pragma once
#include "sqlite3.h"
#include "vector"
#include "string"
#include "functional"
#include "sqlDiff.h"
#include "tools.h"
#include "string.h"
#endif /* sqLiteReader_hpp */

#define sqliteClose() sqlite3_close(db)
using namespace std;
/**
 
 sqlReader("cookies.sqlite","out.txt");
 will output result to out.txt
 
 **/

vector<sqlQuery> sqlReader(const char* database,const char* out); //database: database file name ;



int readSqlCommand(sqlite3* db,int rc, const char *query,vector<sqlQuery>* ret);
int sqlInit(sqlite3** db,const char* database);
int getTableName(sqlite3* db,int rc);
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
static int getTableNameCallback(void *NotUsed, int argc, char **argv, char **azColName);
string getDiffOfSqlite(char** word,string& name);

extern vector<sqlQuery> sqlDiff;
