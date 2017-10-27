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

struct Diff;
template<class T> void initSeparator(std::initializer_list<T>& t);
char* getName(char* word);
char* getFormat(char* word);
int diff(char **word,int n,std::vector<Diff>& resVec);
std::vector<std::pair<std::string,int>> testKey(std::unordered_map<std::string,int>&key1,std::unordered_map<std::string,int>&key2);
//int testDiff(std::string str1,std::string str2);

std::vector<Diff> mainDetector(std::ifstream &file);
std::string getDir(char* word);

//struct which saving differ file's info

struct Diff{
    
    std::string name;
    
    std::string path1;
    std::string path2;
    
    std::string content1;   //full file 
    std::string content2;
    
    std::vector<std::pair<std::string,int>> diffContent;
    
    
    
};
