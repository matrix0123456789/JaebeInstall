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
public:static fstream *plikBin;
public:static unsigned long dlugoscPliku;
public:
	StatyczneInfo();
	~StatyczneInfo();
};

