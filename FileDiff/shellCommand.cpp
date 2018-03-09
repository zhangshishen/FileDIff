#include "shellCommand.h"
using namespace std;
vector<std::string> exec(const char *cmd) {

    std::vector<std::string> resvec;
    FILE *pp = popen(cmd, "r"); //建立管道
    if (!pp) {
        return resvec;
    }
    //char tmp[102400]; //设置一个合适的长度，以存储每一行输出
    while (fgets(tmp, sizeof(tmp), pp) != NULL) {
        if (tmp[strlen(tmp) - 1] == '\n') {
            tmp[strlen(tmp) - 1] = '\0'; //去除换行符
        }
        resvec.push_back(tmp);
    }
    pclose(pp); //关闭管道
    return resvec;
}