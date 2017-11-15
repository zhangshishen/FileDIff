//
//  sqLiteReader.hpp
//  FileDiff
//
//  Created by Shishen Zhang on 2017/11/15.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef sqLiteReader_hpp
#define sqLiteReader_hpp


#include <stdio.h>

#include <sqlite3.h>

#endif /* sqLiteReader_hpp */

#define sqliteClose() sqlite3_close(db)
int sqlReader(char* database,char* query); //database: database name ;

int readSqlCommand(sqlite3* db,int rc, char *query);
int sqlInit(sqlite3** db,char* database);
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
