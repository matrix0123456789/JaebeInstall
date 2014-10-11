#include "StatyczneInfo.h"

using namespace std;

StatyczneInfo::StatyczneInfo()
{
}


StatyczneInfo::~StatyczneInfo()
{
}
long StatyczneInfo::NaglowkiDl;
WCHAR* StatyczneInfo::nazwa = L"testtest";
WCHAR* StatyczneInfo::wersja = L"TestTest";
Kompresja StatyczneInfo::kompresja=Zlib;
WCHAR* StatyczneInfo::autor = L"TestTest";
WCHAR* StatyczneInfo::licencja = L"TestTest";
WCHAR* StatyczneInfo::plikWykonywalny = L"";
WCHAR* StatyczneInfo::SciezkaDomyslna = L"C:\Program Files\Program";
int StatyczneInfo::otwartyPlikId = 1;
HBITMAP StatyczneInfo::obrazek = NULL;
BITMAPINFO StatyczneInfo::obrazekInfo;
bool StatyczneInfo::otwartyPlik = true;
HWND StatyczneInfo::okno;
HWND StatyczneInfo::koniecB;
bool StatyczneInfo::koniec = false;
unsigned long StatyczneInfo::dlugoscPliku = 0xffffffffffffffff;
fstream* StatyczneInfo::plikBin = new fstream[1];