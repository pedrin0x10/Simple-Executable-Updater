#include <string>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include "http.h"

namespace cfg {
    std::string versionurl = ""; 
    std::string downloadurl = "";
}

std::string getexepath() {
    char path[MAX_PATH];
    wchar_t wtext[20];
    mbstowcs(wtext, path, strlen(path) + 1);
    LPWSTR ptr = wtext;
    ::GetModuleFileName(0, ptr, MAX_PATH);
    return path;
}

std::string getexename() {
    std::string path = getexepath();
    std::string exename = path.substr(path.rfind("\\") + 1);
    return exename;
}

void RequestUpdate() {
    std::string version = http(cfg::versionurl);
    Sleep(500);
    if (version != "1.0") {
        std::string cmd = "start curl " + cfg::downloadurl + " -o " + getexename();
        system(cmd.c_str());
        ExitProcess(0);
    }
}