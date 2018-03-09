#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "string"
#include "vector"
#include "iostream"
#include "diffGenerator.hpp"
#include "shellCommand.h"

string dockerGetImageName(string containerId);
vector<string> dockerGetId();
vector<string> dockerDiff(const string& id);