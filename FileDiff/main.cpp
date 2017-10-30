#include "iostream"

#include "stdio.h"
#include "stdlib.h" 
#include "diff.h"

using namespace std;





int main(int argc, char *argv[])
{

    std::string path = "/Users/shishenzhang/log1.txt";
    ifstream fa(path);
    
    ofstream of("/Users/shishenzhang/out.txt");
    streambuf* fileBuf = of.rdbuf();
    
    cout.rdbuf(fileBuf);
    auto m = mainDetector(fa);
    for(auto& c:m){
        cout<<"File Name:\t"<<c.name<<endl;
        cout<<"Diff Content:\t"<<endl;
        for(auto& n:c.diffContent){
            cout<<n.first<<endl;
        }
        cout<<endl;
    }
    return 0;
}
