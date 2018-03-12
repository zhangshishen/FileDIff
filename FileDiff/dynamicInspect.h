

#include "vector"
#include "string"
#include "unistd.h"
#include "iostream"
#include "stdio.h"
#include <sys/types.h>
#include "string.h"

#include "diffGenerator.hpp"
#include "shellCommand.h"
#include "dockerCommand.h"

#include "fstream"
#include "tools/getTime.h"
#include "tools/fileOperate.h"

using namespace std;





void makeFileByLine(const string& outName,vector<string> &content);
vector<string> getDiff();
void getDiffByDefault();