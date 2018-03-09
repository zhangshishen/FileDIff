
#include "dockerCommand.h"

using namespace std;

string dockerGetImageName(string containerId){
    string command = dockerCreateCommand({"docker","inspect","--format='{{.Config.Image}}'",containerId},' ');
    auto res = exec(command.c_str());

    if(res.size()!=1){
        std::cerr<<"fatal error!"<<endl;
    }

    return res[0];
}

vector<string> dockerGetId(){        // get all container id 

    string command = dockerCreateCommand({"docker","ps","-aq"},' ');
    vector<string> res;

    return exec(command.c_str());

}

vector<string> dockerDiff(const string& id){        // get all diff content

    string command = dockerCreateCommand({"docker","diff",id},' ');
    

    return exec(command.c_str());

}