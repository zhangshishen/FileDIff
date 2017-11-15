//
//  sqLiteReader.cpp
//  FileDiff
//
//  Created by Shishen Zhang on 2017/11/15.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#include "sqLiteReader.hpp"

int sqlReader(char* database,char* query){
    sqlite3* db;
    int rc = sqlInit(&db, database);
    readSqlCommand(db,rc,"");
    sqliteClose();
    return 0;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    
    for(i=0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int sqlInit(sqlite3** db,char* database){
    //sqlite3 *db;
    int rc = sqlite3_open(database, db);
    return rc;
    
}

int readSqlCommand(sqlite3* db,int rc, char *query){  //argv[1] database argv[2]
    
        //sqlite3 *db;
        char *zErrMsg = 0;
        //int rc;
    
    
        if( rc ){
              fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
              sqlite3_close(db);
              return(1);
        }
        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
        if( rc!=SQLITE_OK )
        {
              fprintf(stderr, "SQL error: %s\n", zErrMsg);
              sqlite3_free(zErrMsg);
        }
    
        sqlite3_close(db);
        return 0;
}


