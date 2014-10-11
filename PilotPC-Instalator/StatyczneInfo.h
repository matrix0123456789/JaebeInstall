#pragma once
#include "stdafx.h"
using namespace std;
enum Kompresja :byte{ Brak, Zlib };
class StatyczneInfo
{
public: static WCHAR* nazwa;
public:static Kompresja kompresja;
public: static WCHAR* wersja;
public: static WCHAR* autor;
public: static WCHAR* licencja;
public: static WCHAR* plikWykonywalny;
public: static WCHAR* SciezkaDomyslna;
public:static fstream *plikBin;
public:static unsigned long dlugoscPliku;
public: static bool otwartyPlik;
public: static bool koniec;
public:static int otwartyPlikId;
public:static HWND koniecB;
public:static HBITMAP obrazek;
public:static BITMAPINFO obrazekInfo;
public:static HWND okno;
public:static long NaglowkiDl;
public:
	StatyczneInfo();
	~StatyczneInfo();
};

