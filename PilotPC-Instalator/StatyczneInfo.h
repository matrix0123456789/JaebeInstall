#pragma once
#include "stdafx.h"
using namespace std;
class StatyczneInfo
{
public: static WCHAR* nazwa;
public: static WCHAR* wersja;
public: static WCHAR* autor;
public: static WCHAR* licencja;
public: static WCHAR* plikWykonywalny;
public: static WCHAR* SciezkaDomyslna;
public:static fstream *plikBin;
public:static unsigned long dlugoscPliku;
public: static bool otwartyPlik;
public:static int otwartyPlikId;
public:static HBITMAP obrazek;
public:static BITMAPINFO obrazekInfo;
public:
	StatyczneInfo();
	~StatyczneInfo();
};

