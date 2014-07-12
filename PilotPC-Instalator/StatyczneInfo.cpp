#include "StatyczneInfo.h"

using namespace std;

StatyczneInfo::StatyczneInfo()
{
}


StatyczneInfo::~StatyczneInfo()
{
}
WCHAR* StatyczneInfo::nazwa = L"testtest";
WCHAR* StatyczneInfo::wersja = L"TestTest";
WCHAR* StatyczneInfo::autor = L"TestTest";
WCHAR* StatyczneInfo::licencja = L"TestTest";
unsigned long StatyczneInfo::dlugoscPliku = 0xffffffffffffffff;
fstream* StatyczneInfo::plikBin = new fstream[1];