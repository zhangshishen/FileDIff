//
//  keyExtract.h
//  FileDiff
//
//  Created by Shishen Zhang on 2017/10/19.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef keyExtract_h
#define keyExtract_h

#include <stdio.h>
#include "unordered_set"
#include "unordered_map"
#include "string"
#endif /* keyExtract_h */

int isHeader(char* word);

int extractKey(std::string& str,char separator[],std::unordered_map<std::string,int>& map,int line);
