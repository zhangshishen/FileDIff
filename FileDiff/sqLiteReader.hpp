#ifndef sqLiteReader_hpp
#define sqLiteReader_hpp


#include <stdio.h>

#include <sqlite3.h>
#include "vector"
#include "string"
#endif /* sqLiteReader_hpp */

#define sqliteClose() sqlite3_close(db)

/**
 
 sqlReader("cookies.sqlite","out.txt");
 will output result to out.txt
 
 **/

int sqlReader(const char* database,const char* out); //database: database file name ;



int readSqlCommand(sqlite3* db,int rc, const char *query);
int sqlInit(sqlite3** db,const char* database);
int getTableName(sqlite3* db,int rc);
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
static int getTableNameCallback(void *NotUsed, int argc, char **argv, char **azColName);
