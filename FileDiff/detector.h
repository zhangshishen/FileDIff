//
//  detector.h
//  FileDiff
//
//  Created by Shishen Zhang on 2017/10/19.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef detector_h
#define detector_h
#include <stdio.h>
#include "vector"
#include "string"


#endif /* detector_h */

int stringMatch(const std::string& src,const std::string& dest);
int isURL(const std::string& s);
int classify(const std::string& s);
int isPrivacy(std::vector<std::string>& words);
