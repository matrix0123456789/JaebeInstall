#include "instalacja.h"
#include <stdio.h>
#include <stdlib.h>
;
#include <shellapi.h>
;
#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
;
#include <Winsock2.h>
#include <comdef.h>
#include <Winbase.h>
#include "windows.h"
#include "winnls.h"
#include "shobjidl.h"
#include "objbase.h"
#include "objidl.h"
#include "shlguid.h"
#include <process.h>
#include <Shobjidl.h>
#include <Sddl.h>
#include "jezyk.h"
#include "StatyczneInfo.h"
#include "stdafx.h"
using namespace std;

/*WCHAR* lacz(LPCWSTR a, string b)
{
int i = 0;
for (; a[i] != 0; i++)
{
}
cstring ret = (WCHAR*)GlobalAlloc(GPTR, (i + b.length()) * 2);

for (int i = 0; a[i] != 0; i++)
{
ret[i] = a[i];
}
for (int i2 = 0; i2<b.length(); i++)
{
ret[i + i2] = a[i2];
}
return ret;
}*/

void koniec();

instalacja::instalacja(bool _systemStart, bool _wszyscy, LPCWSTR _folder, bool _skrotPulpit, bool _skrotMenuStart,  wstring _wfolder, HWND _StanInstalacji)
{

	systemStart = _systemStart;
	wszyscy = _wszyscy;
	folder = _folder;
	wfolder = _wfolder;
	skrotMenuStart = _skrotMenuStart;
	skrotPulpit = _skrotPulpit;
	folderStr = wstring(folder);
	StanInstalacji = _StanInstalacji;
	//MessageBox(okno, folder,wfolder.c_str(), MB_ICONINFORMATION);


}
void __cdecl watekStart(void * Args)
{
	// Check the current process's "run as administrator" status.
	BOOL fIsRunAsAdmin;
	try
	{
		fIsRunAsAdmin = IsRunAsAdmin();


		// Elevate the process if it is not run as administrator.
		if (!fIsRunAsAdmin)
		{
			wchar_t szPath[MAX_PATH];
			if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath)))
			{
				// Launch itself as administrator.
				SHELLEXECUTEINFO sei = { sizeof(sei) };
				sei.lpVerb = L"runas";
				sei.lpFile = szPath;
				wstring parametry = wstring(jezyk::napisy[Kod]) + wstring(L" \"") + (((instalacja*)Args)[0].wfolder) + wstring(L"\"");
				if (((instalacja*)Args)[0].systemStart)
					parametry = parametry + wstring(L" /s");
				if (((instalacja*)Args)[0].wszyscy)
					parametry = parametry + wstring(L" /w");
				if (((instalacja*)Args)[0].skrotMenuStart)
					parametry = parametry + wstring(L" /m");
				if (((instalacja*)Args)[0].skrotPulpit)
					parametry = parametry + wstring(L" /p");
				sei.lpParameters = parametry.c_str();
				sei.hwnd = ((instalacja*)Args)[0].okno;
				sei.nShow = SW_NORMAL;

				if (!ShellExecuteEx(&sei))
				{
					DWORD dwError = GetLastError();
					if (dwError == ERROR_CANCELLED)
					{
						MessageBox(((instalacja*)Args)[0].okno, jezyk::napisy[WymaganeUprawneiniaAdministratora], jezyk::napisy[BladPodczasInstalacji], MB_ICONINFORMATION);
						exit(0);
					}
				}
				else
				{
					EndDialog(((instalacja*)Args)[0].okno, TRUE);  // Quit itself
					exit(0);
				}
			}
		}
		else
		{
			((instalacja*)Args)[0].start(((instalacja*)Args)[0].wfolder);
			//MessageBox(((instalacja*)Args)[0].okno, jezyk::napisy[Zainstalowano], jezyk::napisy[Zainstalowano], MB_ICONINFORMATION);
			//exit(0);
			koniec();
		}
	}
	catch (DWORD dwError)
	{
		((instalacja*)Args)[0].start(((instalacja*)Args)[0].wfolder);
		//MessageBox(((instalacja*)Args)[0].okno, jezyk::napisy[Zainstalowano], jezyk::napisy[Zainstalowano], MB_ICONINFORMATION);
		//exit(0);
		koniec();
	}



}
void r�bFolder(wstring fol)
{
	SECURITY_ATTRIBUTES  sa;
	SECURITY_ATTRIBUTES*  saw = &sa;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;
	TCHAR * szSD = TEXT("D:")       // Discretionary ACL
		TEXT("(A;OICI;GA;;;AU)");
	ConvertStringSecurityDescriptorToSecurityDescriptor(
		szSD,
		SDDL_REVISION_1,
		&(saw->lpSecurityDescriptor),
		NULL);
	for (int i = 3; i < fol.length(); i++)
	{

		if (fol[i] == '\\')
		{
			if (!CreateDirectory(fol.substr(0, i).c_str(), &sa) && _waccess(fol.substr(0, i).c_str(), 0) == ENOENT){
				MessageBox(NULL, (wstring(L"Nie mo�na utworzy� folderu ") + fol.substr(0, i)).c_str(), jezyk::napisy[BladPodczasInstalacji], MB_ICONERROR);
				exit(1);
			}
		}
	}
	if (!CreateDirectory(fol.c_str(), &sa) && _waccess(fol.c_str(), 0) == ENOENT){
		MessageBox(NULL, (wstring(L"Nie mo�na utworzy� folderu ") + fol).c_str(), jezyk::napisy[BladPodczasInstalacji], MB_ICONERROR);
		exit(1);
	}
}
long pozycja;
void ladujNastepnyPlik()
{
	//pozycja = StatyczneInfo::plikBin[0].tellg();
	if (pozycja >= (long) StatyczneInfo::dlugoscPliku){
		StatyczneInfo::otwartyPlikId++;
		StatyczneInfo::plikBin = new fstream[1];
		StatyczneInfo::plikBin[0].open((string("data") + std::to_string(StatyczneInfo::otwartyPlikId) + string(".bin")).c_str(), ios::binary | ios::in);
		StatyczneInfo::otwartyPlik = (StatyczneInfo::plikBin[0].is_open());  //blad otwarcia pliku
		pozycja = 0;

		StatyczneInfo::plikBin[0].seekg(0, ios::end);
		StatyczneInfo::dlugoscPliku = StatyczneInfo::plikBin[0].tellg();
		StatyczneInfo::plikBin[0].seekg(0, ios::beg);
	}
}
int instalacja::postepFaktyczny = 0;
int instalacja::postepAnim = 0;
void instalacja::start(wstring fol)
{
	try{
		postepFaktyczny = 16;

		r�bFolder(fol);
		/*if (!czyJava())
		{
		pobierz("java.bin", fol,this);
		MoveFile(((wstring)folder + L"\\java.bin").c_str(), ((wstring)folder + L"\\javaInstalacja.exe").c_str());
		MessageBox(NULL, L"W systemie brak Javy. Prosz� zainstalowa� Jav�", L"Informacja o Javie", MB_ICONEXCLAMATION);
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		CreateProcess(((wstring)folder + L"\\javaInstalacja.exe").c_str(), L"javaInstalacja.exe", NULL, NULL, false, 0, NULL, folder, &si, &pi);
		}*/
		WCHAR bufor[1024];
		GetModuleFileName(NULL, bufor, 1024);
		CopyFile(bufor, (folderStr + (L"\\uninstall.exe")).c_str(), false);
		CopyFile(L"zlib1.dll", (folderStr + (L"\\zlib1.dll")).c_str(), false);
		postepFaktyczny = 512;
		fstream data1kopia;
		data1kopia.open((folderStr + (L"\\data1.bin")).c_str(), ios::binary | ios::out);
		//zapis danych do pliku
		char* bufdoc = new char[1];

		StatyczneInfo::plikBin[0].seekg(0, ios::beg);
		for (unsigned int i = 0; i < StatyczneInfo::NaglowkiDl; i++)
		{
			StatyczneInfo::plikBin[0].read(bufdoc, 1);
			data1kopia.write(bufdoc,1);
		}
		data1kopia.close();
		//int soc=getHttp("pilotpc.za.pl", 13, "pilotpc-pc-java.jar", 19);
		/*int soc = getHttp("pilotpc.za.pl", 13, "version.ini", 11);
		const int BuffSize = 10000;
		char buff[1 + BuffSize];
		//memset(&buff, 0, BuffSize + 1);
		//char[] = new char[];
		//while (true)
		//{
		int n = recv(soc, buff, BuffSize, 0);*/

		postepFaktyczny = 2048;


		WCHAR* nazwa = new WCHAR[32 * 1024];
		long *dlugoscPlikOrg = new long[2];
		long *dlugoscPlikSkompresowany = new long[2];
		long *dlugoscChwil = new long[2];
		//while (StatyczneInfo::plikBin[0].tellg() < StatyczneInfo::dlugoscPliku)
		while (StatyczneInfo::otwartyPlik)
		{
			pozycja = StatyczneInfo::plikBin[0].tellg();
				ladujNastepnyPlik();
			postepFaktyczny = 2048 + ((StatyczneInfo::plikBin[0].tellg() * 31 * 1024) / StatyczneInfo::dlugoscPliku);

			char *dlugoscNazwa = new char[4];
			for (unsigned int i = 0; i < 4; i++)
			{
				StatyczneInfo::plikBin[0].read((char*)&dlugoscNazwa[i], 1);
			}
			pozycja += 4;
				ladujNastepnyPlik();
			for (unsigned int i = 0; i < ((unsigned short*)dlugoscNazwa)[0]; i++)
			{
				StatyczneInfo::plikBin[0].read((char*)nazwa + i, 1);
			}
			nazwa[((unsigned short*)dlugoscNazwa)[0] / 2] = 0;
			pozycja += ((unsigned short*)dlugoscNazwa)[0];
				ladujNastepnyPlik();


			for (unsigned int i = 0; i < 8; i++)
			{
				StatyczneInfo::plikBin[0].read(((char*)dlugoscPlikOrg) + i, 1);
			}
			pozycja += 8;
			ladujNastepnyPlik();

			fstream plik_po_rozpakowaniu;
			//przygotowanie folderu
			int pos = (wstring(nazwa)).find_last_of(L'\\');
			if (pos > 0)
			{
				r�bFolder((wstring(wfolder) + L"\\" + wstring(nazwa).substr(0, pos).c_str()));
			}

			//tworzenie pliku w ktorym zapiszemy rozpakowane dane
			plik_po_rozpakowaniu.open((wstring(wfolder) + L"\\" + wstring(nazwa)).c_str(), ios::binary | ios::out);
			long rozpTera = 0;
			while (rozpTera<dlugoscPlikOrg[0]){
				for (unsigned int i = 0; i < 8; i++)
				{
					StatyczneInfo::plikBin[0].read(((char*)dlugoscChwil) + i, 1);
				}
				pozycja += 8;
				ladujNastepnyPlik();
				for (unsigned int i = 0; i < 8; i++)
				{
					StatyczneInfo::plikBin[0].read(((char*)dlugoscPlikSkompresowany) + i, 1);
				}
				pozycja += 8;
				ladujNastepnyPlik();

			 long dlugosc_po_rozpakowaniu = -1;
				Byte* bufor_docelowy = new byte[((long*)dlugoscChwil)[0]];
				Byte* buforSkompresowany = new byte[((long*)dlugoscPlikSkompresowany)[0]];
				pozycja = StatyczneInfo::plikBin[0].tellg();
				//czytamy plik
				for (unsigned long i = 0; i < (dlugoscPlikSkompresowany)[0]; i++)
				{
					StatyczneInfo::plikBin[0].read((char*)&buforSkompresowany[i], 1);
					pozycja++;
					if (pozycja >= StatyczneInfo::dlugoscPliku)
					{
						ladujNastepnyPlik();
						if (!StatyczneInfo::otwartyPlik)
							break;
					}
				}

				if (StatyczneInfo::kompresja == Kompresja::Zlib)
				{

					//rozpakowyjemy
					uncompress((Bytef*)bufor_docelowy, (uLong*)dlugoscChwil, (Bytef*)buforSkompresowany, ((long*)dlugoscPlikSkompresowany)[0]);
				}
				else
				{
					bufor_docelowy = buforSkompresowany;
					dlugoscChwil = dlugoscPlikSkompresowany;
				}
				
				//zapis danych do pliku
				for (unsigned int i = 0; i < dlugoscChwil[0]; i++)
				{
					plik_po_rozpakowaniu.write((char*)&bufor_docelowy[i], 1);
				}
			delete[] buforSkompresowany;
			delete[] bufor_docelowy;
			rozpTera += dlugoscChwil[0];
			}
			//zamykamy strumienie plikow
			plik_po_rozpakowaniu.close();

			//czy�cimy pami��
		}


		/*buff[n] = 0;
		int i = 0;
		for (; i < n; i++)
		{
		if (buff[i] == '\n'&&buff[i + 1] == '\n')
		{
		i = i + 2;
		break;
		}
		else if (buff[i] == '\n'&&buff[i + 2] == '\n'){
		i = i + 3;
		break;
		}
		}
		string tresc = buff + i;
		ilePlikow = 0;
		for (int x = 0; x < n - i; x++)
		{
		if (tresc[x] == '\n'&&tresc[x + 1] == 'p'&&tresc[x + 2] == 'l'&&tresc[x + 3] == 'i'&&tresc[x + 4] == 'k'&&tresc[x + 5] == '=')
		{
		x = x + 6;
		ilePlikow++;
		}
		}
		ilePlikowGotowe = 0;
		for (int x = 0; x < n - i; x++)
		{
		if (tresc[x] == '\n'&&tresc[x + 1] == 'p'&&tresc[x + 2] == 'l'&&tresc[x + 3] == 'i'&&tresc[x + 4] == 'k'&&tresc[x + 5] == '=')
		{
		x = x + 6;
		int x2 = x;
		string plik = tresc.substr(x);
		plik = plik.substr(0, plik.find_first_of('\r'));
		pobierz(plik, fol,this);
		ilePlikowGotowe++;
		postepFaktyczny = 2048 + (29 * 1024 * ilePlikowGotowe) / ilePlikow;

		}
		}*/
		postepFaktyczny = 31 * 1024;

		HKEY hkUninstall;
		HKEY hkProgram;
		DWORD dwDisp;
		if (wszyscy)
			RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_ALL_ACCESS | KEY_WOW64_32KEY, &hkUninstall);
		else
			RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_ALL_ACCESS | KEY_WOW64_32KEY, &hkUninstall);
		RegCreateKeyEx(hkUninstall, (wstring(StatyczneInfo::autor) + wstring(StatyczneInfo::nazwa)).c_str(), 0, NULL, REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS | KEY_WOW64_32KEY, NULL, &hkProgram, &dwDisp);
		RegSetValueEx(hkProgram, L"DisplayName", 0, REG_SZ, (byte*)StatyczneInfo::nazwa, 14);
		RegSetValueEx(hkProgram, L"UninstallString", 0, REG_SZ, (byte*)(folderStr + (L"\\uninstall.exe")).c_str(), 28 + 2 * folderStr.length());
		//RegSetValueEx(hkProgram, L"URLInfoAbout", 0, REG_SZ, (byte*)L"https://github.com/FranQy/PilotPC-PC-Java", 82);
		RegSetValueEx(hkProgram, L"Publisher", 0, REG_SZ, (byte*)StatyczneInfo::autor, 46);
		//RegSetValueEx(hkProgram, L"Readme", 0, REG_SZ, (byte*)(folderStr + (L"\\readme.html")).c_str(), 24 + 2 * folderStr.length());
		//int rozmiar = 2252;
		//RegSetValueEx(hkProgram, L"EstimatedSize", 0, REG_DWORD, (byte*)&rozmiar, 4);
		//string wersja = "0.1.25";
		//RegSetValueEx(hkProgram, L"DisplayVersion", 0, REG_SZ, (byte*)wersja.c_str(), 2 * wersja.length());

		/*if (systemStart)
		{
		HKEY hkTest;
		if (wszyscy)
		RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkTest);
		else
		RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkTest);
		wstring polecenie = (L"\"" + folderStr + (L"\\Windows.exe\""));
		RegSetValueEx(hkTest, L"PilotPC", 0, REG_SZ, (byte*)polecenie.c_str(), 2 * polecenie.length());
		}*/
		char userprofile[1024];

		GetEnvironmentVariableA("USERPROFILE", userprofile, 1024);
		char appdata[1024];

		GetEnvironmentVariableA("appdata", appdata, 1024);
			wstring plikexe = wstring(StatyczneInfo::plikWykonywalny);
		if (skrotPulpit)
		{
			wstring naz = wstring(StatyczneInfo::nazwa);
			string Pulpit = userprofile + (string)"\\Desktop\\" + std::string(naz.begin(), naz.end());
			string polecenie = (string)"mklink \"" + Pulpit + (string)"\" \"" + std::string(folderStr.begin(), folderStr.end()) + string("\\")+string(plikexe.begin(), plikexe.end())+string("\"");
			system(polecenie.c_str());
		}
		if (skrotMenuStart)
		{
			string folderMS;
			wstring assdc = wstring(StatyczneInfo::nazwa);
			folderMS = string(userprofile) + string("\\Start Menu\\Programs\\") + std::string(assdc.begin(), assdc.end());
			CreateDirectoryA(folderMS.c_str(), NULL);
			wstring wstrindzek = wstring(StatyczneInfo::nazwa);
			system(((string)"mklink \"" + folderMS + (string)"\\" + std::string(wstrindzek.begin(), wstrindzek.end()) + "\" \"" + std::string(folderStr.begin(), folderStr.end()) + (string)"\\" + string(plikexe.begin(), plikexe.end()) + string("\"")).c_str());
			//CreateLink((folderStr + (L"\\PilotPC-PC-Java.jar")).c_str(), (folderMS + (string)"\\PilotPC").c_str(), L"PilotPC - program do sterowania komputerem z poziomu telefonu", folderStr.c_str());
			//CreateLink((folderStr + (L"\\Uninstall.exe")).c_str(), (folderMS + (string)"\\Odinstaluj").c_str(), L"Usuwa program PilotPC z tego komputera", folderStr.c_str());
			
			folderMS = appdata + (string("\\Microsoft\\Windows\\Start Menu\\Programs\\")) + string(assdc.begin(), assdc.end());
			CreateDirectoryA(folderMS.c_str(), NULL);
			system(((string)"mklink \"" + folderMS + (string)"\\" + std::string(wstrindzek.begin(), wstrindzek.end()) + "\" \"" + std::string(folderStr.begin(), folderStr.end()) + (string)"\\" + string(plikexe.begin(), plikexe.end()) + string("\"")).c_str());
			//CreateLink((folderStr + (L"\\PilotPC-PC-Java.jar")).c_str(), (folderMS + (string)"\\PilotPC").c_str(), L"PilotPC - program do sterowania komputerem z poziomu telefonu", folderStr.c_str());
			//CreateLink((folderStr + (L"\\Uninstall.exe")).c_str(), (folderMS + (string)"\\Odinstaluj").c_str(), L"Usuwa program PilotPC z tego komputera", folderStr.c_str());
		}
		postepFaktyczny = 32 * 1024;
	}
	catch (exception e)
	{
		const char* what = e.what();
		string stWhat = string(what);
		wstring wstWhat = wstring(stWhat.begin(), stWhat.end());
		MessageBox(0, wstWhat.c_str(), jezyk::napisy[BladPodczasInstalacji], MB_ICONERROR);

	}
}

/*HRESULT CreateLink(LPCWSTR lpszPathObj, LPCSTR lpszPathLink, LPCWSTR lpszDesc, LPCWSTR workingDir)
{
HRESULT hres;
IShellLink* psl;
// Get a pointer to the IShellLink interface. It is assumed that CoInitialize
// has already been called.
HRESULT test10 = CoInitialize((LPVOID)&psl);
hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
int test = (int)hres;
if (SUCCEEDED(hres))
{
IPersistFile* ppf;

// Set the path to the shortcut target and add the description.
psl->SetPath(lpszPathObj);
psl->SetDescription(lpszDesc);
psl->SetWorkingDirectory(workingDir);
// Query IShellLink for the IPersistFile interface, used for saving the
// shortcut in persistent storage.

hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

if (SUCCEEDED(hres))
{
WCHAR wsz[MAX_PATH];

// Ensure that the string is Unicode.
MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1, wsz, MAX_PATH);

// Add code here to check return value from MultiByteWideChar
// for success.

// Save the link by calling IPersistFile::Save.
hres = ppf->Save(wsz, TRUE);
ppf->Release();
}
psl->Release();
}
return hres;

}*/
void instalacja::start(HWND hWnd)
{
	okno = hWnd;
	OSVERSIONINFO osv;
	ZeroMemory(&osv, sizeof(OSVERSIONINFO));
	osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osv);
	int test = (int)this;
	_beginthread(watekStart, 0, this);
}

bool instalacja::odinstal = false;
instalacja::~instalacja()
{
}

void instalacja::odinstaluj(HINSTANCE hInstance, HWND okno)
{
	// Check the current process's "run as administrator" status.
	BOOL fIsRunAsAdmin;
	instalacja::odinstal = true;
	try
	{
		fIsRunAsAdmin = IsRunAsAdmin();


		// Elevate the process if it is not run as administrator.
		if (!fIsRunAsAdmin)
		{
			wchar_t szPath[MAX_PATH];
			if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath)))
			{
				// Launch itself as administrator.
				SHELLEXECUTEINFO sei = { sizeof(sei) };
				sei.lpVerb = L"runas";
				sei.lpFile = szPath;
				wstring test = (wstring(jezyk::napisy[Kod]) + wstring(L" /u"));
				LPCWSTR test2 = test.c_str();
				LPCWSTR test3 = (LPCWSTR)test.c_str();
				sei.lpParameters = test3;
				//sei.hwnd = ((instalacja*)Args)[0].okno;
				sei.nShow = SW_NORMAL;

				if (!ShellExecuteEx(&sei))
				{
					DWORD dwError = GetLastError();
					if (dwError == ERROR_CANCELLED)
					{
						MessageBox(okno, jezyk::napisy[WymaganeUprawneiniaAdministratora], jezyk::napisy[BladPodczasInstalacji], MB_ICONINFORMATION);
						exit(0);
					}
				}
				else
				{
					EndDialog(okno, TRUE);  // Quit itself
					exit(0);
				}
				return;
			}
		}
	}
	catch (DWORD dwError)
	{
	}
	HKEY r, uninstall, run;
	wstring klucz = (wstring(StatyczneInfo::autor) + wstring(StatyczneInfo::nazwa));
	long blad = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + klucz).c_str(), 0, KEY_ALL_ACCESS | KEY_WOW64_32KEY, &r);
	if (blad != 0)
		long blad = RegOpenKeyEx(HKEY_CURRENT_USER, (L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + klucz).c_str(), 0, KEY_ALL_ACCESS | KEY_WOW64_32KEY, &r);
	CHAR folderExe[1024];
	DWORD rozmiar; //rozmiar odczytanej warto�ci(w bajtach)
	DWORD typ_danych = REG_SZ; //zmienna na typ danych
	ULONG ret = RegQueryValueExA(r, "UninstallString", 0, &typ_danych, (LPBYTE)folderExe, &rozmiar);
	if (ret != 0)
	{
		MessageBox(0, L"Nie znaleziono �cie�ki do folderu", L"B��d", 0);
	}
	string folder = ((string)folderExe).substr(0, rozmiar - 15);
	postepFaktyczny = 9 * 1024;

	//system("rd /s /q %appdata%\\PilotPC-PC-Java"); 
	postepFaktyczny = 18 * 1024;
	system((string("rd /s /q \"") + folder + "\"").c_str());
	postepFaktyczny = 25 * 1024;

	char userprofile[1024];

	GetEnvironmentVariableA("USERPROFILE", userprofile, 1024);
	char appdata[1024];

	GetEnvironmentVariableA("appdata", appdata, 1024);
	wstring naz = wstring(StatyczneInfo::nazwa);
	string Pulpit = userprofile + (string)"\\Desktop\\" + std::string(naz.begin(), naz.end());
	DeleteFileA(Pulpit.c_str());

	wstring assdc = wstring(StatyczneInfo::nazwa);
	system(((string)"rd /s /q \"" + userprofile + (string)"\\Start Menu\\Programs\\" + std::string(assdc.begin(), assdc.end())+string("\"")).c_str());
	system(((string)"rd /s /q \"" + appdata + (string)"\\Microsoft\\Windows\\Start Menu\\Programs\\" + std::string(assdc.begin(), assdc.end()) + string("\"")).c_str());
	postepFaktyczny = 27 * 1024;

	RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS | KEY_WOW64_32KEY, &run);
	RegDeleteValue(run, klucz.c_str());
	RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_ALL_ACCESS | KEY_WOW64_32KEY, &uninstall);
	RegDeleteKey(uninstall, klucz.c_str());
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS | KEY_WOW64_32KEY, &run);
	RegDeleteValue(run, klucz.c_str());
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_ALL_ACCESS | KEY_WOW64_32KEY, &uninstall);
	RegDeleteKey(uninstall, klucz.c_str());
	postepFaktyczny = 32 * 1024;
	MessageBox(0, jezyk::napisy[Usunieto], L"", MB_ICONINFORMATION);
	exit(0);
}


// 
//   FUNCTION: IsRunAsAdmin()
//
//   PURPOSE: The function checks whether the current process is run as 
//   administrator. In other words, it dictates whether the primary access 
//   token of the process belongs to user account that is a member of the 
//   local Administrators group and it is elevated.
//
//   RETURN VALUE: Returns TRUE if the primary access token of the process 
//   belongs to user account that is a member of the local Administrators 
//   group and it is elevated. Returns FALSE if the token does not.
//
//   EXCEPTION: If this function fails, it throws a C++ DWORD exception which 
//   contains the Win32 error code of the failure.
//
//   EXAMPLE CALL:
//     try 
//     {
//         if (IsRunAsAdmin())
//             wprintf (L"Process is run as administrator\n");
//         else
//             wprintf (L"Process is not run as administrator\n");
//     }
//     catch (DWORD dwError)
//     {
//         wprintf(L"IsRunAsAdmin failed w/err %lu\n", dwError);
//     }
//
BOOL IsRunAsAdmin()
{
	BOOL fIsRunAsAdmin = FALSE;
	DWORD dwError = ERROR_SUCCESS;
	PSID pAdministratorsGroup = NULL;

	// Allocate and initialize a SID of the administrators group.
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	if (!AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&pAdministratorsGroup))
	{
		dwError = GetLastError();
		goto Cleanup;
	}

	// Determine whether the SID of administrators group is enabled in 
	// the primary access token of the process.
	if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
	{
		dwError = GetLastError();
		goto Cleanup;
	}

Cleanup:
	// Centralized cleanup for all allocated resources.
	if (pAdministratorsGroup)
	{
		FreeSid(pAdministratorsGroup);
		pAdministratorsGroup = NULL;
	}

	// Throw the error if something failed in the function.
	if (ERROR_SUCCESS != dwError)
	{
		throw dwError;
	}

	return fIsRunAsAdmin;
}void koniec()
{
	StatyczneInfo::koniec = true;
	
	CreateWindowEx(0, L"BUTTON", L"Zainstalowano, kliknij by zako�czy�", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		0, 0, 450, 650, StatyczneInfo::okno, (HMENU)4000, instalacja::hins, NULL);
}
HINSTANCE instalacja::hins;