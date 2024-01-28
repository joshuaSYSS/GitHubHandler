// NativeCppLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h"
#include "framework.h"
// Standard Library imports
#include <iostream>

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    }
    catch (...) {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);
    return result;
}
bool checkgitauth() {
    std::string status = exec("gh auth status");
    return (status == "You are not logged into any GitHub hosts. Run gh auth login to authenticate.");
}

void gitauth(const char* authTokenPath) { //Assume GitHub.com, HTTPS and with credentials
    char cmd[10000];
    strcpy_s(cmd, "gh auth login --with-token < ");
    strcat_s(cmd, authTokenPath);
    std::string res = exec(cmd);
}
std::string gitpush(const char filePath[]) {
    bool authed = checkgitauth();
    if (!authed) {
        return "AUTH REQUIRED";
    }
    char cmd[10000];
    strcpy_s(cmd, "gh gist create ");
    strcat_s(cmd, filePath);
    std::string result = exec(cmd);
    return result;
}
