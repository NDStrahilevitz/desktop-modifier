// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <Windows.h>
#include <urlmon.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h> 
#include <thread>

#pragma comment(lib, "urlmon.lib")
#pragma warning(disable : 4996)

using namespace std;

void split(const std::string &s, char delim, std::vector<string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

string CreateDownloadPaths(vector<LPCSTR> urls)
{
	string paths;
	for (u_int i = 0; i < urls.size(); i++)
	{
		stringstream fpStrm;
		string fp;
		fpStrm << "D:\\img" << i << ".jpg";
		fp = fpStrm.str();
		HRESULT hr = URLDownloadToFileA(NULL, urls[i], fp.c_str() , 0, NULL);
		if (SUCCEEDED(hr))
		{
			paths += fp + ";";
		}
	}
	return paths;
}

void ChangeBackground(const string &paths)
{
	u_int i = 0;
	vector<string> vpaths;
	split(paths, ';', vpaths);
	cout << vpaths.size();
	while (true)
	{
		SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)vpaths[i%vpaths.size()].c_str(), SPIF_UPDATEINIFILE);
		i++;
		Sleep(1250);
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
	FreeConsole();
	vector<LPCSTR> urls = { "https://4.bp.blogspot.com/-TmA6nbLk9XQ/UxIoVsqYNLI/AAAAAAAAoRg/4rHuQWzbJdI/s0/Battlefield+4_HD.jpg", "https://images.alphacoders.com/505/505347.jpg", "http://www.mindblowingpicture.com/wp_highres/aviation/WP7LX772.jpg" };
	string paths = CreateDownloadPaths(urls);
	thread thread1(ChangeBackground,paths);
	thread thread2(MinimizeCurrentWindow);
	thread1.join();
	thread2.join();	
	return 0;
}

