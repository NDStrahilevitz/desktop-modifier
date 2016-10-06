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

using namespace std;

void CreateDir()
{
		if (CreateDirectory((LPCWSTR)"D:\\deskMod\\images", NULL)) 
		{
			cout << "success";
		}
		else 
		{
			cout << "error";
		}
}

vector<LPCSTR> CreateDownloadPaths(vector<LPCSTR> &urls)
{
	vector<LPCSTR> paths;
	for (u_int i = 0; i < urls.size(); i++)
	{
		char fp[20];
		int n;
		n = sprintf(fp, "D:\\img%d.jpg", i);
		HRESULT hr = URLDownloadToFileA(NULL, urls[i], fp, 0, NULL);
		if (SUCCEEDED(hr))
		{
			paths.push_back(fp);
			cout << paths[i];
			if (i > 0)
			{
				cout << paths[i - 1];
			}
		}
	}
	for (u_int i = 0; i < urls.size(); i++)
	{
		cout << paths[i];
	}
	return paths;
}
void ChangeBackground(vector<LPCSTR> paths)
{
	u_int i = 0;
//if (paths.size() > 0)
//	cout << paths[0];
	while (true)
	{
		SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)paths[i%paths.size()], SPIF_UPDATEINIFILE);
		i++;
		Sleep(500);
	}
}

void MinimizeCurrentWindow()
{	
	while (true)
	{
		//ShowWindow(GetForegroundWindow(), SW_FORCEMINIMIZE);
		CloseWindow(GetForegroundWindow());
	}
}

int main()
{
	//FreeConsole();
	vector<LPCSTR> urls = { "https://4.bp.blogspot.com/-TmA6nbLk9XQ/UxIoVsqYNLI/AAAAAAAAoRg/4rHuQWzbJdI/s0/Battlefield+4_HD.jpg", "https://images.alphacoders.com/505/505347.jpg", "http://www.mindblowingpicture.com/wp_highres/aviation/WP7LX772.jpg" };
	/*thread thread1 = thread(ChangeBackground(CreateDownloadPaths(urls)));
	thread thread2 = thread(MinimizeCurrentWindow);
	thread1.join();
	thread2.join();
	CreateDir();*/
	vector<LPCSTR> paths = CreateDownloadPaths(urls);
	cout << paths[0];
	return 0;
}

