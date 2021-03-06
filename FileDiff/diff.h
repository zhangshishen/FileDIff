//
//  diff.h
//  FileDiff
//
//  Created by Shishen Zhang on 2017/10/19.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef diff_h
#define diff_h


#endif /* diff_h */

#include <stdio.h>
#include <unordered_set>
#include "vector"
#include "string.h"
#include "parser.h"
#include "keyExtract.h"
#include "fstream"
#include "sqLiteReader.h"
#include "diffGenerator.h"
#include "sqlDiff.h"

#include "tools.h"

#define FLAT 0x00
#define SIMPLE 0x01

#pragma once

struct Diff;
template<class T> void initSeparator(std::initializer_list<T>& t);
char* getName(char* word);
const char* getFormat(const char* word);
std::vector<Diff> mainDetector(std::ifstream &file);
int diff(char **word,int n,std::vector<Diff>& resVec,int flag);
std::vector<std::pair<std::string,int>> testKey(std::unordered_map<std::string,int>&key1,std::unordered_map<std::string,int>&key2);
//int testDiff(std::string str1,std::string str2);
void commonDiff(std::ifstream& file,Diff& dif,int flag);

std::string getDir(char* word);
Diff stringToDiff(const string& str);
//struct which saving differ file's info



struct Diff{
    
    std::string name;
    
    std::string path1;
    std::string path2;
    
    std::string content1;   //full file 
    std::string content2;
    
    std::vector<std::pair<std::string,int>> diffContent;
    
    void print();
    
    
};
