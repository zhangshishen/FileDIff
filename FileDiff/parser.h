//
//  parser.h
//  FileDiff
//
//  Created by Shishen Zhang on 2017/10/19.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef parser_h
#define parser_h

#include <stdio.h>
#include "stdlib.h"
#include "string"
#include "cstring"
#endif /* parser_h */

#define DIFFER 0
#define BIN 1
#define DIFF 2
#define DIR 3
#define ONLY 4

int sentenceFormat(char **word);
char lineNum(const std::string& s,int res[4]);
int readLine(char **word,char* buf);
