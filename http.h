#pragma once
#define _WIN32_DCOM

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <wininet.h>

using namespace std;
#pragma once
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "wbemuuid.lib")

string replaceAll(string subject, const string& search,
	const string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

string http(string URL) {
	HINTERNET interwebs = InternetOpenA("Pedrin/Websocket", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD readbtyes;
			do {
				InternetReadFile(urlFile, buffer, 2000, &readbtyes);
				rtn.append(buffer, readbtyes);
				memset(buffer, 0, 2000);
			} while (readbtyes);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			string p = replaceAll(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	string p = replaceAll(rtn, "|n", "\r\n");
	return p;
}