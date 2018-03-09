
#include "dockerCommand.h"

using namespace std;

string dockerGetImageName(string containerId){
    string command = dockerCreateCommand({"docker","inspect","--format='{{.Config.Image}}'",containerId},' ');
    auto res = exec(command.c_str());
    if(res.size()!=1){
        cerr<<"fatal error!"<<endl;
    }
    return res[0];
}

vector<string> dockerGetId(){        // get all container id 

    string command = dockerCreateCommand({"docker","ps","-aq"},' ');
    vector<string> res;

    return exec(command.c_str());

}