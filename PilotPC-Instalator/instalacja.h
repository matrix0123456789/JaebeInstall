#pragma once
#include "stdafx.h"
using namespace std;

BOOL IsRunAsAdmin();
class instalacja
{
public: static int postepFaktyczny;
public:static HINSTANCE hins;
public: static int postepAnim;
public:HWND StanInstalacji;
public:	instalacja(bool systemStart, bool wszyscy, LPCWSTR folder, bool skrotPulpit, bool skrotMenuStart,wstring wfolder,HWND);
public: void instalacja::start(wstring fol);
public: void instalacja::start(HWND hWnd);
public: static bool odinstal;
public: static void instalacja::odinstaluj(HINSTANCE, HWND);
public: void __cdecl instalacja::start(void * Args);
		HWND okno;
	HWND progressbar;
	bool systemStart; bool wszyscy; LPCWSTR folder; wstring wfolder;
	bool skrotPulpit; bool skrotMenuStart;
	wstring folderStr;
	int ilePlikow;
	int ilePlikowGotowe;
	//WCHAR* lacz(LPCWSTR a, string b);
	~instalacja();
	void instalacja::pobierz(string nazwa, wstring fold, instalacja*);

};
//HRESULT CreateLink(LPCWSTR lpszPathObj, LPCSTR lpszPathLink, LPCWSTR lpszDesc,LPCWSTR workingDir);
#include "start.h"