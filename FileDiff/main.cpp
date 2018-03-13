#include "iostream"

#include "stdio.h"
#include "stdlib.h" 
#include "diff.h"

using namespace std;





int main(int argc, char *argv[])
{
    //initLog();
    commonGenerator("log.txt");
    std::string path = "log.txt";
    ifstream fa(path);
    ofstream of("outa.txt");
    streambuf* fileBuf = of.rdbuf();
    
    cout.rdbuf(fileBuf);
    
    auto m = mainDetector(fa);
    for(auto& c:m){
        c.print();
    }
    of.close();
    return 0;
    
}
