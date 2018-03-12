#include "fileOperate.h"

std::streampos filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}


void fileAppend(const string& dst,const string& src){   //append src to dst
    std::ifstream ifile("first_file.txt", std::ios::in);
    std::ofstream ofile("second_file.txt", std::ios::out | std::ios::app);

//check to see that it exists:
    if (!ifile.is_open()) {
        //file not found (i.e. it is not opened). Print an error message or do something else.
    }
    else {
        ofile << ifile.rdbuf();
    //then add more lines to the file if need be...
    }
}
