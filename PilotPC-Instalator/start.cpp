﻿#include "stdafx.h"
#include "start.h"
#include "jezyk.h"
#include <Windowsx.h>
#include <Shlobj.h>
#include "zlib.h"
#include <fstream>
#include "StatyczneInfo.h"
using namespace Gdiplus;
HWND przyciskJezyk[3];
HWND g_hPrzycisk, user1, userWiele, systemStart, skrotP, skrotMS;
BOOL systemStartBool = true;
BOOL wszyscy = false;
BOOL skrotPulpit = true;
BOOL skrotMenuStart = true;
HWND folder;
HWND FolderTxt;
HWND StanInstalacji;
int logoCzas;
int myszX, myszY;

bool trwa = false;
instalacja* ins;
// Enable Visual Style
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#pragma endregion

#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib,"ws2_32.lib")
#pragma comment (lib,"comctl32.lib")
#pragma comment (lib,"Msimg32.lib")
#pragma comment (lib,"zdll.lib")

HINSTANCE hinstance;


HBRUSH ciemnyTlo;
HBRUSH ciemnyTloB;
HBRUSH ciemnyTlo2;
HBRUSH ciemnyTlo3;
HBRUSH ciemnyTlo3B;
HBRUSH ciemnyTlo4;
HBRUSH ciemnyTlo4B;
HBRUSH ciemnyTlo5;
HBRUSH jasnyTlo1;
HBRUSH jasnyTlo2, Szymon1, Szymon2;
HBRUSH czarny;
HBRUSH niebieski;


HFONT JaebeCzcionka = CreateFont(60, 0, 0, 0, 0, 0, 0, 0, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, 0, L"Segoe UI");
HFONT PilotPCCzcionka = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, 0, L"Segoe UI");
HFONT PilotPCCzcionka2 = CreateFont(35, 0, 0, 0, 0, 0, 0, 0, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, 0, L"Segoe UI");
HFONT EditCziocka = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, 0, L"Segoe UI");
HFONT hNormalFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, 0, L"Segoe UI");
HFONT XCzcionka = CreateFont(15, 7, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");
void logoAni(HDC);
void odpakuj();
void wyswietl2(HINSTANCE hInstance);
int stringDlugosc(wchar_t* wej)
{
	int ret = 0;
	while (wej[ret] != 0)
		ret++;
	return ret;
}
void convert(std::string &in, std::wstring &out)
{
	out.resize(in.size());
	const char   *in_next = &*in.begin();
	wchar_t      *out_next = &*out.begin();


	typedef std::codecvt<wchar_t, char, std::mbstate_t> converter;
	const converter &my_converter = std::use_facet<converter>(std::locale());


	std::mbstate_t   my_state;


	my_converter.in(my_state,
		in.c_str(), in.c_str() + in.length(), in_next,
		&out[0], (&out[0]) + in.length(), out_next);
}
HBITMAP hbmObraz;
HBITMAP Checkbox1;
int* logoRandom = new int[20000];
HBITMAP Checkbox2;
VOID OnPaint(HDC hdc)
{

	logoAni(hdc);

	RECT prost;
	prost.left = 0;
	prost.top = 500;
	prost.right = 450;
	prost.bottom = 650;
	FillRect(hdc, &prost, ciemnyTlo3);
	prost.left = 0;
	prost.top = 0;
	prost.right = 1;
	prost.bottom = 650;
	FillRect(hdc, &prost, czarny);
	prost.left = 449;
	prost.top = 0;
	prost.right = 450;
	prost.bottom = 650;
	FillRect(hdc, &prost, czarny);
	prost.left = 0;
	prost.top = 0;
	prost.right = 450;
	prost.bottom = 1;
	FillRect(hdc, &prost, czarny);
	prost.left = 0;
	prost.top = 649;
	prost.right = 450;
	prost.bottom = 650;
	FillRect(hdc, &prost, czarny);

	HDC hdcNowy = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNowy, hbmObraz);
	BitBlt(hdc, 1, 79, 21, 41, hdcNowy, 0, 0, SRCCOPY);
	SelectObject(hdcNowy, hbmOld);
	DeleteDC(hdcNowy);


}
boolean* jezykPrzyciskStan = new boolean[3];
boolean* PrzyciskStan = new boolean[10];

DWORD animacjaCzas;
byte nrAni = 0;
HWND hWnd = NULL;
HWND LicencjaZaakceptuj, LicencjaTxt, folderButton;
void wyswietl(HINSTANCE hInstance)
{
	DWORD dlugosc = GetWindowTextLength(folder);
	LPWSTR Bufor = (LPWSTR)GlobalAlloc(GPTR, dlugosc * 2 + 2);
	GetWindowText(folder, Bufor, dlugosc + 2);
	trwa = true;
	//Bufor[dlugosc] = 0;
	//DestroyWindow(LicencjaZaakceptuj);
	//DestroyWindow(LicencjaTxt);
	wyswietl2(hinstance);
	//licencja
	nrAni = 4;
	animacjaCzas = GetTickCount();
	/*LicencjaTxt = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 475, 130, 400, 300, hWnd, NULL, hInstance, NULL);
	SendMessage(LicencjaTxt, WM_SETFONT, (WPARAM)PilotPCCzcionka, 0);
	SetWindowText(LicencjaTxt, StatyczneInfo::licencja);
	LicencjaZaakceptuj = CreateWindowEx(0, L"BUTTON", jezyk::napisy[Zaakceptuj], WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		451, 500, 448, 149, hWnd, (HMENU)2002, hInstance, NULL);
	SendMessage(LicencjaZaakceptuj, WM_SETFONT, (WPARAM)PilotPCCzcionka2, 0);*/
}
HWND JavaTxt, JavaTakB, JavaNieB;
int* animowane = new int[1024, 5];
void przesun(HWND el, DWORD czas, int x, int y, int z, int a)
{
	animacjaCzas = czas;
	for (int i = 0; i < 1024; i++)
	if (animowane[i, 0] == NULL)
	{
		animowane[i, 0] = (int)el;
		animowane[i, 1] = (int)x;
		animowane[i, 2] = (int)y;
		animowane[i, 3] = (int)z;
		animowane[i, 4] = (int)a;
		return;
	}
}
void wyswietl2(HINSTANCE hInstance)
{

	wyswietl3(hInstance);
	return;

}
void wyswietl3(HINSTANCE hInstance)
{
	nrAni = 4;
	animacjaCzas = GetTickCount();
	FolderTxt = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 475, 140, 400, 20, hWnd, NULL, hInstance, NULL);

	//HFONT PilotPCCzcionka = CreateFont(18, 7, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");
	SendMessage(FolderTxt, WM_SETFONT, (WPARAM)hNormalFont, 0);
	SetWindowText(FolderTxt, jezyk::napisy[n::WybierzFolder]);
	SendMessage(FolderTxt, WM_SETFONT, (WPARAM)PilotPCCzcionka, 0);
	g_hPrzycisk = CreateWindowEx(0, L"BUTTON", jezyk::napisy[Instaluj], WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		451, 500, 448, 149, hWnd, (HMENU)2010, hInstance, NULL);
	SendMessage(g_hPrzycisk, WM_SETFONT, (WPARAM)PilotPCCzcionka2, 0);
	//SendMessage(g_hPrzycisk, WM_CTLCOLORSTATIC, g_hBrush, 0);
	folder = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE,
		475, 160, 325, 20, hWnd, NULL, hInstance, NULL);
	SendMessage(folder, WM_SETFONT, (WPARAM)PilotPCCzcionka, 0);
	//wstring sciezkaF = wstring(L"c:\\Program Files\\") + wstring(StatyczneInfo::autor) + wstring(L"\\") + wstring(StatyczneInfo::nazwa);

	//SetWindowText(folder, sciezkaF.c_str());
	SetWindowText(folder, StatyczneInfo::SciezkaDomyslna);


	folderButton = CreateWindowEx(0, L"BUTTON", jezyk::napisy[Wybierz], WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		700, 160, 80, 20, hWnd, (HMENU)2999, hInstance, NULL);
	SendMessage(folderButton, WM_SETFONT, (WPARAM)PilotPCCzcionka, 0);

	user1 = CreateWindowEx(0, L"BUTTON", jezyk::napisy[DlaObecnegoUzytkownika], WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		475, 240, 400, 25, hWnd, (HMENU)3000, hInstance, NULL);
	SendMessage(user1, WM_SETFONT, (WPARAM)hNormalFont, 0);
	SendMessage(user1, BM_SETCHECK, 1, 0);



	userWiele = CreateWindowEx(0, L"BUTTON", jezyk::napisy[DlaWszystkichUzytkownikow], WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		475, 270, 400, 25, hWnd, (HMENU)3001, hInstance, NULL);
	SendMessage(userWiele, WM_SETFONT, (WPARAM)hNormalFont, 0);
	systemStart = CreateWindowEx(0, L"BUTTON", jezyk::napisy[UruchamiajAutomatyczneiPrzyStarcieSystemu], WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		475, 310, 400, 25, hWnd, (HMENU)3002, hInstance, NULL);
	SendMessage(systemStart, WM_SETFONT, (WPARAM)hNormalFont, 0);

	SendMessage(systemStart, BM_SETCHECK, 1, 0);


	skrotP = CreateWindowEx(0, L"BUTTON", jezyk::napisy[SkrotNaPulpicie], WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		475, 340, 400, 25, hWnd, (HMENU)3003, hInstance, NULL);
	SendMessage(skrotP, WM_SETFONT, (WPARAM)hNormalFont, 0);

	SendMessage(skrotP, BM_SETCHECK, 1, 0);

	/*	if (IsWindows8OrGreater())
	skrotMS = CreateWindowEx(0, L"BUTTON", L"Skrót na Ekranie Start", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
	200, 120, 190, 30, hWnd, NULL, hInstance, NULL);
	else*/
	skrotMS = CreateWindowEx(0, L"BUTTON", jezyk::napisy[SkrotWMenuStart], WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		475, 370, 400, 25, hWnd, (HMENU)3004, hInstance, NULL);
	SendMessage(skrotMS, WM_SETFONT, (WPARAM)hNormalFont, 0);

	SendMessage(skrotMS, BM_SETCHECK, 1, 0);

	InitCommonControls();
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	);
LONG a, b;
HWND WyborOdinstaluj, WyborInstaluj, WyborTxt;
void wybor(HINSTANCE hInstance){
	HKEY r;
	wstring klucz = wstring(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\") + wstring(StatyczneInfo::autor) + wstring(StatyczneInfo::nazwa);
	a = RegOpenKeyEx(HKEY_LOCAL_MACHINE, klucz.c_str(), 0, KEY_READ, &r);
	b = RegOpenKeyEx(HKEY_CURRENT_USER, klucz.c_str(), 0, KEY_READ, &r);

	//HFONT hNormalFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	if (a == 0 || b == 0)

		//if(false)
	{
		nrAni = 1;
		animacjaCzas = GetTickCount();
		//HFONT PilotPCCzcionka = CreateFont(18, 7, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");
		WyborTxt = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
			SS_LEFT, 475, 130, 400, 40, hWnd, NULL, hInstance, NULL);
		SendMessage(WyborTxt, WM_SETFONT, (WPARAM)PilotPCCzcionka, 0);
		SetWindowText(WyborTxt, jezyk::napisy[ProgramJestJuzZainstalowany]);
		WyborOdinstaluj = CreateWindowEx(0, L"BUTTON", jezyk::napisy[Odinstaluj], WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
			451, 180, 448, 220, hWnd, (HMENU)2000, hInstance, NULL);
		SendMessage(WyborOdinstaluj, WM_SETFONT, (WPARAM)PilotPCCzcionka, 0);
		WyborInstaluj = CreateWindowEx(0, L"BUTTON", jezyk::napisy[InstalujPonownie], WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
			451, 400, 448, 100, hWnd, (HMENU)2001, hInstance, NULL);
		SendMessage(WyborInstaluj, WM_SETFONT, (WPARAM)PilotPCCzcionka, 0);
	}
	else
		wyswietl(hInstance);
}
HWND przyciskX;
HWND przyciskMin;
HWND CopyTxt;
void rysujStałe(HINSTANCE hInstance)
{
	//HFONT hNormalFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	HFONT JaebeCzcionkaCopy = CreateFont(12, 6, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");

	if (StatyczneInfo::obrazek == NULL){
	HWND JaebeTxt = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 65, 10, 449 - 165, 50, hWnd, NULL, hInstance, NULL);
	SendMessage(JaebeTxt, WM_SETFONT, (WPARAM)JaebeCzcionka, 0);

		SetWindowText(JaebeTxt, StatyczneInfo::autor);
		//CopyTxt = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
		//	SS_LEFT, 30, 630, 300, 50, hWnd, NULL, hInstance, NULL);
		//SendMessage(CopyTxt, WM_SETFONT, (WPARAM)JaebeCzcionkaCopy, 0);
		//SetWindowText(CopyTxt, L"©");
		HWND PilotPCTxt = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
			SS_LEFT, 20, 80, 300, 40, hWnd, NULL, hInstance, NULL);
		SendMessage(PilotPCTxt, WM_SETFONT, (WPARAM)PilotPCCzcionka2, 0);


		SetWindowText(PilotPCTxt, StatyczneInfo::nazwa);
	}
	HDC hdcOkno;
	hdcOkno = GetDC(hWnd);
	RECT prost;
	prost.left = 1;
	prost.top = 500;
	prost.right = 448;
	prost.bottom = 649;


	FillRect(hdcOkno, &prost, ciemnyTlo3);

	przyciskX = CreateWindowEx(0, L"BUTTON", L"X", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		424, 1, 25, 25, hWnd, (HMENU)1999, hInstance, NULL);
	SendMessage(przyciskX, WM_SETFONT, (WPARAM)XCzcionka, 0);
	przyciskMin = CreateWindowEx(0, L"BUTTON", L"_", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		399, 1, 25, 25, hWnd, (HMENU)1998, hInstance, NULL);
	SendMessage(przyciskMin, WM_SETFONT, (WPARAM)XCzcionka, 0);

	if (StatyczneInfo::obrazek != NULL){
		HDC hdcNowy = CreateCompatibleDC(hdcOkno);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNowy, StatyczneInfo::obrazek);

		BitBlt(hdcOkno, 0, 0, StatyczneInfo::obrazekInfo.bmiHeader.biWidth, StatyczneInfo::obrazekInfo.bmiHeader.biHeight, hdcNowy, 0, 0, SRCCOPY);
	}
	ReleaseDC(hWnd, hdcOkno);
}

HFONT jezykCzcionka = CreateFont(20, 8, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");
#define BTNRED  1001
#define BTNBLUE 1002
void wybierzJezyk(HINSTANCE hInstance)
{
	jezyk::nazwyLoad();
	HFONT hNormalFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	przyciskJezyk[0] = CreateWindowEx(0, L"BUTTON", L"Polski", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		1, 150, 448, 113, hWnd, (HMENU)1000, hInstance, NULL);
	SendMessage(przyciskJezyk[0], WM_SETFONT, (WPARAM)jezykCzcionka, 0);
	przyciskJezyk[1] = CreateWindowEx(0, L"BUTTON", L"English", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		1, 263, 448, 113, hWnd, (HMENU)1001, hInstance, NULL);
	SendMessage(przyciskJezyk[1], WM_SETFONT, (WPARAM)jezykCzcionka, 0);
	przyciskJezyk[2] = CreateWindowEx(0, L"BUTTON", L"русский", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		1, 376, 448, 114, hWnd, (HMENU)1002, hInstance, NULL);
	SendMessage(przyciskJezyk[2], WM_SETFONT, (WPARAM)jezykCzcionka, 0);


}
int narysowane = 0;
void drawButtonRed(HDC hDC, UINT itemState, HWND hwnd, HBRUSH zaznaczone, HBRUSH niezaznaczone, LPWSTR txt, int Txtlen, int szerokosc, int wysokosc, HFONT font){


	RECT prost;
	prost.left = 0;
	prost.top = 0;
	prost.right = szerokosc;
	prost.bottom = wysokosc;
	if (itemState & ODS_SELECTED) {


		FillRect(hDC, &prost, zaznaczone);
	}
	else if (itemState & ODS_HOTLIGHT) {


		FillRect(hDC, &prost, zaznaczone);
	}
	else{

		FillRect(hDC, &prost, niezaznaczone);

	}
	if (StatyczneInfo::obrazek != NULL)
	{

		if (hwnd == przyciskMin&&StatyczneInfo::obrazekInfo.bmiHeader.biWidth>399)
		{
			HDC hdcNowy = CreateCompatibleDC(hDC);
			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNowy, StatyczneInfo::obrazek);

			BitBlt(hDC, 0, 0, StatyczneInfo::obrazekInfo.bmiHeader.biWidth, StatyczneInfo::obrazekInfo.bmiHeader.biHeight, hdcNowy, 399, 0, SRCCOPY);

		}
		if (hwnd == przyciskX&&StatyczneInfo::obrazekInfo.bmiHeader.biWidth>424)
		{

			HDC hdcNowy = CreateCompatibleDC(hDC);
			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNowy, StatyczneInfo::obrazek);

			BitBlt(hDC, 2, 2, 12, 12, hdcNowy, 5, 6, SRCCOPY);
		}
	}
	RECT rc;
	GetClientRect(hwnd, &rc);

	SetBkMode(hDC, TRANSPARENT);

	char buf[255];
	if (font != NULL)
		SelectObject(hDC, font);
	//GetWindowText(hwnd, txt, 255);

	//SendMessage(hDC, WM_SETFONT, (WPARAM)jezykCzcionka, 0);

	SetTextColor(hDC, RGB(255, 255, 255));
	DrawText(hDC, txt, Txtlen, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	ReleaseDC(hwnd, hDC);
}
void drawButtonRed(DRAWITEMSTRUCT *dis, HWND hwnd, HBRUSH zaznaczone, HBRUSH niezaznaczone, LPWSTR txt, int Txtlen){
	drawButtonRed(dis->hDC, dis->itemState, hwnd, zaznaczone, niezaznaczone, txt, Txtlen, 450, 650, NULL);
}
void logoAni(HDC hdc){
	if (ins != NULL||instalacja::odinstal)
		instalacja::postepAnim = instalacja::postepAnim + (instalacja::postepFaktyczny - instalacja::postepAnim) / 50;
	if (logoCzas != 0 && narysowane != (*ins).postepAnim * 1200 / (32 * 1024))
	{
		int czasR = (*ins).postepAnim * 1200 / (32 * 1024);
		//int czasR = GetTickCount() - logoCzas;
		//czasR = czasR / 10;
		int czarMn = 1000 - czasR;
		/*if (hbmObraz==NULL)
		hbmObraz = LoadBitmap(hinstance, MAKEINTRESOURCE(4));

		HDC hdcNowy = CreateCompatibleDC(hdc);
		HDC hdcBufor = CreateCompatibleDC(hdc);
		HBITMAP hbmBuf = CreateCompatibleBitmap(hdc, 448, 300);
		HBITMAP hbmOldBuf = (HBITMAP)SelectObject(hdcBufor, hbmBuf);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNowy, hbmObraz);

		RECT prostTlo;
		prostTlo.left = 0;
		prostTlo.top = 0;
		prostTlo.right = 448;
		prostTlo.bottom = 300;
		FillRect(hdcBufor, &prostTlo, ciemnyTlo);
		if (czasR<1000)
		for (int i = 0; i < 150; i++)
		{
		for (int i2 = 0; i2 < 50; i2++)
		{//do napisania pozycji
		BitBlt(hdcBufor, 2 * i + 74 + logoRandom[i * 50 + i2] * czarMn / 1000, 2 * i2 + 100 + logoRandom[i * 50 + i2 + 150 * 50] * czarMn / 1000, 2, 2, hdcNowy, 2 * i, 2 * i2, SRCCOPY);

		}
		}
		else
		{
		logoCzas = 0;
		BitBlt(hdcBufor, 74, 100, 300, 100, hdcNowy, 0, 0, SRCCOPY);
		}

		SelectObject(hdcNowy, hbmOld);
		DeleteDC(hdcNowy);

		BitBlt(hdc, 1, 150, 448, 300, hdcBufor, 0, 0, SRCCOPY);
		DeleteDC(hdcBufor);
		DeleteBitmap(hbmBuf);
		DeleteBitmap(hbmOldBuf);
		DeleteBitmap(hbmOld);*/
		narysowane = czasR;
	}
}
int aaaaa = 0;
VOID CALLBACK TimerProc(
	_In_  HWND hwnd,
	_In_  UINT uMsg,
	_In_  UINT_PTR idEvent,
	_In_  DWORD dwTime
	)
{
	float czas = (float)(GetTickCount() - animacjaCzas) * 2;
	int przes = (int)(0.00045*czas*czas - 0.9*czas);
	/*if (przes >= 0)
		return;*/
	if (czas > 1000)
	{
		przes = -450;
		if (nrAni > 0)
		{

			for (int i2 = 0; i2 < 3; i2++)
			{
				DestroyWindow(przyciskJezyk[i2]);

			}
		}
		if (nrAni>1 && WyborInstaluj != NULL)
		{
			DestroyWindow(WyborInstaluj);
			DestroyWindow(WyborOdinstaluj);
			DestroyWindow(WyborTxt);

			/*RECT prost;
			prost.left = 1;
			prost.top = 130;
			prost.right = 25;
			prost.bottom = 500;
			FillRect(GetDC(hWnd), &prost, ciemnyTlo);*/

		}
		if (nrAni > 2)
		{
			//DestroyWindow(LicencjaTxt);
			//DestroyWindow(LicencjaZaakceptuj);
			/*if (PrzyciskStan[5] == 1)
			{

			drawButtonRed(GetDC(JavaTakB), 0, JavaTakB, ciemnyTlo5, ciemnyTlo4B, jezyk::napisy[JavaTak], stringDlugosc(jezyk::napisy[JavaTak]), 448, 220, PilotPCCzcionka);

			}
			else
			{
			drawButtonRed(GetDC(JavaTakB), 0, JavaTakB, ciemnyTlo5, ciemnyTlo4, jezyk::napisy[JavaTak], stringDlugosc(jezyk::napisy[JavaTak]), 448, 220, PilotPCCzcionka);

			}*/
		}
		if (nrAni > 3)
		{
			//DestroyWindow(JavaTakB);
			//DestroyWindow(JavaNieB);
			//DestroyWindow(JavaTxt);
		}
	}
	if (nrAni > 0 && przyciskJezyk[0] != NULL)
	{

		for (int i2 = 0; i2 < 3; i2++)
		{
			MoveWindow(przyciskJezyk[i2], 1 + przes, 150 + i2 * 113, 448, 113, true);


			if (jezykPrzyciskStan[i2] == 1)
			{

				//drawButtonRed(GetDC(przyciskJezyk[i2]), 0, przyciskJezyk[i2], ciemnyTlo2, ciemnyTloB, jezyk::nazwyJezykow[i2], jezyk::nazwyJezykowLen[i2], 448, 113, jezykCzcionka);

			}
			else
			{
				//jezykPrzyciskStan[i2] = 0;
				//drawButtonRed(GetDC(przyciskJezyk[i2]), 0, przyciskJezyk[i2], ciemnyTlo2, ciemnyTlo, jezyk::nazwyJezykow[i2], jezyk::nazwyJezykowLen[i2], 448, 113, jezykCzcionka);

			}


		}
	}if (nrAni == 1)
	{

		MoveWindow(WyborTxt, 475 + przes, 130, 400, 50, true);
		MoveWindow(WyborOdinstaluj, 451 + przes, 180, 448, 220, true);
		MoveWindow(WyborInstaluj, 451 + przes, 400, 448, 100, true);

		if (PrzyciskStan[0] == 1)
		{

			drawButtonRed(GetDC(WyborOdinstaluj), 0, WyborOdinstaluj, ciemnyTlo5, ciemnyTlo4B, jezyk::napisy[Odinstaluj], stringDlugosc(jezyk::napisy[Odinstaluj]), 448, 220, PilotPCCzcionka);

		}
		else
		{
			drawButtonRed(GetDC(WyborOdinstaluj), 0, WyborOdinstaluj, ciemnyTlo5, ciemnyTlo4, jezyk::napisy[Odinstaluj], stringDlugosc(jezyk::napisy[Odinstaluj]), 448, 220, PilotPCCzcionka);

		}
		if (PrzyciskStan[1] == 1)
		{

			drawButtonRed(GetDC(WyborInstaluj), 0, WyborInstaluj, ciemnyTlo2, ciemnyTloB, jezyk::napisy[InstalujPonownie], stringDlugosc(jezyk::napisy[InstalujPonownie]), 448, 100, PilotPCCzcionka);

		}
		else
		{
			drawButtonRed(GetDC(WyborInstaluj), 0, WyborInstaluj, ciemnyTlo2, ciemnyTlo, jezyk::napisy[InstalujPonownie], stringDlugosc(jezyk::napisy[InstalujPonownie]), 448, 100, PilotPCCzcionka);

		}

	}
	else if (nrAni > 1 && WyborOdinstaluj != NULL)
	{

		MoveWindow(WyborTxt, 25 + przes, 130, 400, 50, true);
		MoveWindow(WyborOdinstaluj, 1 + przes, 180, 448, 220, true);
		MoveWindow(WyborInstaluj, 1 + przes, 400, 448, 100, true);

		if (PrzyciskStan[0] == 1)
		{

			//drawButtonRed(GetDC(WyborOdinstaluj), 0, WyborOdinstaluj, ciemnyTlo5, ciemnyTlo4B, jezyk::napisy[Odinstaluj], stringDlugosc(jezyk::napisy[Odinstaluj]), 448, 220, PilotPCCzcionka);

		}
		else
		{
			//drawButtonRed(GetDC(WyborOdinstaluj), 0, WyborOdinstaluj, ciemnyTlo5, ciemnyTlo4, jezyk::napisy[Odinstaluj], stringDlugosc(jezyk::napisy[Odinstaluj]), 448, 220, PilotPCCzcionka);

		}
		if (PrzyciskStan[1] == 1)
		{

			//drawButtonRed(GetDC(WyborInstaluj), 0, WyborInstaluj, ciemnyTlo2, ciemnyTloB, jezyk::napisy[InstalujPonownie], stringDlugosc(jezyk::napisy[InstalujPonownie]), 448, 100, PilotPCCzcionka);

		}
		else
		{
			//PrzyciskStan[1] = 0;
			//drawButtonRed(GetDC(WyborInstaluj), 0, WyborInstaluj, ciemnyTlo2, ciemnyTlo, jezyk::napisy[InstalujPonownie], stringDlugosc(jezyk::napisy[InstalujPonownie]), 448, 100, PilotPCCzcionka);

		}

	}
	if (nrAni == 2 && LicencjaZaakceptuj != NULL)
	{
		//MoveWindow(LicencjaZaakceptuj, 451 + przes, 500, 448, 149, true);
		//MoveWindow(LicencjaTxt, 475 + przes, 130, 400, 370, true);
		/*if (PrzyciskStan[4] == 1)
		{

			drawButtonRed(GetDC(LicencjaZaakceptuj), 0, LicencjaZaakceptuj, ciemnyTlo2, ciemnyTlo3B, jezyk::napisy[Zaakceptuj], stringDlugosc(jezyk::napisy[Zaakceptuj]), 448, 149, PilotPCCzcionka2);

		}
		else
		{
			drawButtonRed(GetDC(LicencjaZaakceptuj), 0, LicencjaZaakceptuj, ciemnyTlo2, ciemnyTlo3, jezyk::napisy[Zaakceptuj], stringDlugosc(jezyk::napisy[Zaakceptuj]), 448, 149, PilotPCCzcionka2);

		}*/
	}
	if (nrAni > 2 )
	{
		//MoveWindow(LicencjaZaakceptuj, 1 + przes, 500, 448, 149, true);
		//MoveWindow(LicencjaTxt, 25 + przes, 130, 400, 300, true);
		if (PrzyciskStan[4] == 1)
		{

			//drawButtonRed(GetDC(LicencjaZaakceptuj), 0, LicencjaZaakceptuj, ciemnyTlo2, ciemnyTlo3B, jezyk::napisy[Zaakceptuj], stringDlugosc(jezyk::napisy[Zaakceptuj]), 250, 100, PilotPCCzcionka2);

		}
		else
		{
			//drawButtonRed(GetDC(LicencjaZaakceptuj), 0, LicencjaZaakceptuj, ciemnyTlo2, ciemnyTlo3, jezyk::napisy[Zaakceptuj], stringDlugosc(jezyk::napisy[Zaakceptuj]), 250, 100, PilotPCCzcionka2);

		}
	}
	if (nrAni == 3 && JavaNieB != NULL)
	{
		MoveWindow(JavaNieB, 451 + przes, 400, 448, 100, true);
		MoveWindow(JavaTakB, 451 + przes, 180, 448, 220, true);
		MoveWindow(JavaTxt, 475 + przes, 130, 400, 100, true);

		if (PrzyciskStan[5] == 1)
		{

			drawButtonRed(GetDC(JavaTakB), 0, JavaTakB, ciemnyTlo5, ciemnyTlo4B, jezyk::napisy[JavaTak], stringDlugosc(jezyk::napisy[JavaTak]), 448, 220, PilotPCCzcionka);

		}
		else
		{
			drawButtonRed(GetDC(JavaTakB), 0, JavaTakB, ciemnyTlo5, ciemnyTlo4, jezyk::napisy[JavaTak], stringDlugosc(jezyk::napisy[JavaTak]), 448, 220, PilotPCCzcionka);

		}
		if (PrzyciskStan[6] == 1)
		{

			drawButtonRed(GetDC(JavaNieB), 0, JavaNieB, ciemnyTlo2, ciemnyTloB, jezyk::napisy[JavaNie], stringDlugosc(jezyk::napisy[JavaNie]), 448, 100, PilotPCCzcionka);

		}
		else
		{
			drawButtonRed(GetDC(JavaNieB), 0, JavaNieB, ciemnyTlo2, ciemnyTlo, jezyk::napisy[JavaNie], stringDlugosc(jezyk::napisy[JavaNie]), 448, 100, PilotPCCzcionka);

		}
	}
	if (nrAni > 3 )
	{
		//MoveWindow(JavaNieB, 1 + przes, 400, 448, 100, true);
		//MoveWindow(JavaTakB, 1 + przes, 180, 448, 220, true);
		//MoveWindow(JavaTxt, 25 + przes, 130, 400, 100, true);

		/*if (PrzyciskStan[5] == 1)
		{

		drawButtonRed(GetDC(JavaTakB), 0, JavaTakB, ciemnyTlo5, ciemnyTlo4B, jezyk::napisy[JavaTak], stringDlugosc(jezyk::napisy[JavaTak]), 448, 220, PilotPCCzcionka);

		}
		else
		{
		drawButtonRed(GetDC(JavaTakB), 0, JavaTakB, ciemnyTlo5, ciemnyTlo4, jezyk::napisy[JavaTak], stringDlugosc(jezyk::napisy[JavaTak]), 448, 220, PilotPCCzcionka);

		}
		if (PrzyciskStan[6] == 1)
		{

		drawButtonRed(GetDC(JavaNieB), 0, JavaNieB, ciemnyTlo2, ciemnyTloB, jezyk::napisy[JavaNie], stringDlugosc(jezyk::napisy[JavaNie]), 448, 100, PilotPCCzcionka);

		}
		else
		{
		drawButtonRed(GetDC(JavaNieB), 0, JavaNieB, ciemnyTlo2, ciemnyTlo, jezyk::napisy[JavaNie], stringDlugosc(jezyk::napisy[JavaNie]), 448, 100, PilotPCCzcionka);

		}*/
	}
	if (nrAni == 4 && folderButton != NULL)
	{
		MoveWindow(FolderTxt, 475 + przes, 140, 400, 20, true);
		MoveWindow(g_hPrzycisk, 451 + przes, 500, 448, 149, true);
		MoveWindow(folder, 475 + przes, 160, 325, 20, true);
		MoveWindow(folderButton, 800 + przes, 160, 80, 20, true);
		MoveWindow(user1, 475 + przes, 240, 400, 25, true);
		MoveWindow(userWiele, 475 + przes, 270, 400, 25, true);
		MoveWindow(systemStart, 475 + przes, 310, 400, 25, true);
		MoveWindow(skrotP, 475 + przes, 340, 400, 25, true);
		MoveWindow(skrotMS, 475 + przes, 370, 400, 25, true);

		/*drawRadio(GetDC, dis->itemState, user1, ciemnyTlo, jezyk::napisy[DlaObecnegoUzytkownika], stringDlugosc(jezyk::napisy[DlaObecnegoUzytkownika]), !wszyscy);

		drawRadio(dis->hDC, dis->itemState, userWiele, ciemnyTlo, jezyk::napisy[DlaWszystkichUzytkownikow], stringDlugosc(jezyk::napisy[DlaWszystkichUzytkownikow]), wszyscy);

		drawRadio(dis->hDC, dis->itemState, systemStart, ciemnyTlo, jezyk::napisy[UruchamiajAutomatyczneiPrzyStarcieSystemu], stringDlugosc(jezyk::napisy[UruchamiajAutomatyczneiPrzyStarcieSystemu]), systemStartBool);

		drawRadio(dis->hDC, dis->itemState, skrotP, ciemnyTlo, jezyk::napisy[SkrotNaPulpicie], stringDlugosc(jezyk::napisy[SkrotNaPulpicie]), skrotPulpit);

		drawRadio(dis->hDC, dis->itemState, skrotMS, ciemnyTlo, jezyk::napisy[SkrotWMenuStart], stringDlugosc(jezyk::napisy[SkrotWMenuStart]), skrotMenuStart);*/

		/*
		RECT prost;
		prost.left = 0;
		prost.top = 0;
		prost.right = 450;
		prost.bottom = 650;
		FillRect(GetDC(hWnd), &prost, ciemnyTlo);*/
	}


	/*for (int i = 0; i < 10; i++)
	{
	if (animowane[i,0] != NULL)
	{
	MoveWindow((HWND)animowane[i, 0], animowane[i, 1] + przes, animowane[i, 2], animowane[i, 3], animowane[i, 4], false);
	}
	}
	if (przes<-450)
	{

	for (int i = 0; i < 1024; i++)
	{
	animowane[i, 0] = animowane[i, 1] = animowane[i, 2] = animowane[i, 3] = animowane[i, 4] = 0;
	}
	animacjaCzas = GetTickCount();
	}*/
	if (czas > 1000)
	{
		/*if (nrAni == 3)
		{

			RECT prost;
			prost.left = 0;
			prost.top = 500;
			prost.right = 450;
			prost.bottom = 650;
			FillRect(GetDC(hWnd), &prost, ciemnyTlo3);
		}
		nrAni = 0;*/
	}

	logoAni(GetDC(hWnd));
	/*if ((*ins).postepAnim > 0)
	{
	RECT prostTlo2;
	prostTlo2.left = 25;
	prostTlo2.top = 450;
	prostTlo2.right = 25 + (*ins).postepAnim*400/(32*1024);
	prostTlo2.bottom = 470;
	FillRect(GetDC(hWnd), &prostTlo2, jasnyTlo1);
	prostTlo2.left = 25 + (*ins).postepAnim * 400 / (32 * 1024);
	prostTlo2.top = 450;
	prostTlo2.right = 425;
	prostTlo2.bottom = 470;
	FillRect(GetDC(hWnd), &prostTlo2, ciemnyTlo2);
	}*/
	if ((*ins).postepFaktyczny > 0)
	{
		RECT prostTlo2;
		prostTlo2.left = 25;
		prostTlo2.top = 450;
		prostTlo2.right = 25 + (*ins).postepAnim * 400 / (32 * 1024);
		prostTlo2.bottom = 470;
		FillRect(GetDC(hWnd), &prostTlo2, Szymon1);
		prostTlo2.left = 25 + (*ins).postepAnim * 400 / (32 * 1024);
		prostTlo2.top = 450;
		prostTlo2.right = 425;
		prostTlo2.bottom = 470;
		FillRect(GetDC(hWnd), &prostTlo2, Szymon2);
	}
	//if (hProgressBar != NULL)
	//	SendMessage(hProgressBar, PBM_SETPOS, (WPARAM)(*ins).postepFaktyczny, 0);
}
void przerysuj(HWND msghwnd)
{

	for (int i = 0; i < 3; i++)
	{
		if (msghwnd == przyciskJezyk[i] && jezykPrzyciskStan[i] == 0)
		{
			jezykPrzyciskStan[i] = 1;

			drawButtonRed(GetDC(przyciskJezyk[i]), 0, przyciskJezyk[i], ciemnyTlo2, ciemnyTloB, jezyk::nazwyJezykow[i], jezyk::nazwyJezykowLen[i], 448, 113, jezykCzcionka);

		}
		else if (msghwnd != przyciskJezyk[i] && jezykPrzyciskStan[i] != 0)
		{
			jezykPrzyciskStan[i] = 0;
			drawButtonRed(GetDC(przyciskJezyk[i]), 0, przyciskJezyk[i], ciemnyTlo2, ciemnyTlo, jezyk::nazwyJezykow[i], jezyk::nazwyJezykowLen[i], 448, 113, jezykCzcionka);

		}
	}
	if (msghwnd == WyborOdinstaluj && PrzyciskStan[0] == 0)
	{
		PrzyciskStan[0] = 1;

		drawButtonRed(GetDC(WyborOdinstaluj), 0, WyborOdinstaluj, ciemnyTlo5, ciemnyTlo4B, jezyk::napisy[Odinstaluj], stringDlugosc(jezyk::napisy[Odinstaluj]), 448, 220, PilotPCCzcionka);

	}
	else if (msghwnd != WyborOdinstaluj && PrzyciskStan[0] != 0)
	{
		PrzyciskStan[0] = 0;
		drawButtonRed(GetDC(WyborOdinstaluj), 0, WyborOdinstaluj, ciemnyTlo5, ciemnyTlo4, jezyk::napisy[Odinstaluj], stringDlugosc(jezyk::napisy[Odinstaluj]), 448, 220, PilotPCCzcionka);

	}
	if (msghwnd == WyborInstaluj && PrzyciskStan[1] == 0)
	{
		PrzyciskStan[1] = 1;

		drawButtonRed(GetDC(WyborInstaluj), 0, WyborInstaluj, ciemnyTlo2, ciemnyTloB, jezyk::napisy[InstalujPonownie], stringDlugosc(jezyk::napisy[InstalujPonownie]), 448, 100, PilotPCCzcionka);

	}
	else if (msghwnd != WyborInstaluj && PrzyciskStan[1] != 0)
	{
		PrzyciskStan[1] = 0;
		drawButtonRed(GetDC(WyborInstaluj), 0, WyborInstaluj, ciemnyTlo2, ciemnyTlo, jezyk::napisy[InstalujPonownie], stringDlugosc(jezyk::napisy[InstalujPonownie]), 448, 100, PilotPCCzcionka);

	}
	/*if (msghwnd == przyciskX && PrzyciskStan[2] == 0)
	{
	PrzyciskStan[2] = 1;

	drawButtonRed(GetDC(przyciskX), 0, przyciskX, ciemnyTlo2, ciemnyTloB, L"X", 1, 25, 25, XCzcionka);

	}
	else if (msghwnd != przyciskX && PrzyciskStan[2] != 0)
	{
	PrzyciskStan[2] = 0;
	drawButtonRed(GetDC(przyciskX), 0, przyciskX, ciemnyTlo2, ciemnyTlo, L"X", 1, 25, 25, XCzcionka);

	}
	if (msghwnd == przyciskMin && PrzyciskStan[3] == 0)
	{
	PrzyciskStan[3] = 1;

	drawButtonRed(GetDC(przyciskMin), 0, przyciskMin, ciemnyTlo2, ciemnyTloB, L"_", 1, 25, 25, XCzcionka);

	}
	else if (msghwnd != przyciskMin && PrzyciskStan[3] != 0)
	{
	PrzyciskStan[3] = 0;
	drawButtonRed(GetDC(przyciskMin), 0, przyciskMin, ciemnyTlo2, ciemnyTlo, L"_", 1, 25, 25, XCzcionka);

	}*/
	if (msghwnd == LicencjaZaakceptuj && PrzyciskStan[4] == 0)
	{
		PrzyciskStan[4] = 1;

		drawButtonRed(GetDC(LicencjaZaakceptuj), 0, LicencjaZaakceptuj, ciemnyTlo2, ciemnyTlo3B, jezyk::napisy[Zaakceptuj], stringDlugosc(jezyk::napisy[Zaakceptuj]), 448, 149, PilotPCCzcionka2);

	}
	else if (msghwnd != LicencjaZaakceptuj && PrzyciskStan[4] != 0)
	{
		PrzyciskStan[4] = 0;
		drawButtonRed(GetDC(LicencjaZaakceptuj), 0, LicencjaZaakceptuj, ciemnyTlo2, ciemnyTlo3, jezyk::napisy[Zaakceptuj], stringDlugosc(jezyk::napisy[Zaakceptuj]), 448, 149, PilotPCCzcionka2);

	}


	if (msghwnd == JavaTakB && PrzyciskStan[5] == 0)
	{
		PrzyciskStan[5] = 1;

		drawButtonRed(GetDC(JavaTakB), 0, JavaTakB, ciemnyTlo5, ciemnyTlo4B, jezyk::napisy[JavaTak], stringDlugosc(jezyk::napisy[JavaTak]), 448, 220, PilotPCCzcionka);

	}
	else if (msghwnd != JavaTakB && PrzyciskStan[5] != 0)
	{
		PrzyciskStan[5] = 0;
		drawButtonRed(GetDC(JavaTakB), 0, JavaTakB, ciemnyTlo5, ciemnyTlo4, jezyk::napisy[JavaTak], stringDlugosc(jezyk::napisy[JavaTak]), 448, 220, PilotPCCzcionka);

	}
	if (msghwnd == JavaNieB && PrzyciskStan[6] == 0)
	{
		PrzyciskStan[6] = 1;

		drawButtonRed(GetDC(JavaNieB), 0, JavaNieB, ciemnyTlo2, ciemnyTloB, jezyk::napisy[JavaNie], stringDlugosc(jezyk::napisy[JavaNie]), 448, 100, PilotPCCzcionka);

	}
	else if (msghwnd != JavaNieB && PrzyciskStan[6] != 0)
	{
		PrzyciskStan[6] = 0;
		drawButtonRed(GetDC(JavaNieB), 0, JavaNieB, ciemnyTlo2, ciemnyTlo, jezyk::napisy[JavaNie], stringDlugosc(jezyk::napisy[JavaNie]), 448, 100, PilotPCCzcionka);

	}

	if (msghwnd == g_hPrzycisk && PrzyciskStan[7] == 0)
	{
		PrzyciskStan[7] = 1;

		drawButtonRed(GetDC(g_hPrzycisk), 0, g_hPrzycisk, ciemnyTlo2, ciemnyTlo3B, jezyk::napisy[Instaluj], stringDlugosc(jezyk::napisy[Instaluj]), 448, 149, PilotPCCzcionka2);

	}
	else if (msghwnd != g_hPrzycisk && PrzyciskStan[7] != 0)
	{
		PrzyciskStan[7] = 0;
		drawButtonRed(GetDC(g_hPrzycisk), 0, g_hPrzycisk, ciemnyTlo2, ciemnyTlo3, jezyk::napisy[Instaluj], stringDlugosc(jezyk::napisy[Instaluj]), 448, 149, PilotPCCzcionka2);

	}
}
void odpakuj()
{

	StatyczneInfo::plikBin[0].open("data1.bin", ios::binary | ios::in);
	if (!StatyczneInfo::plikBin[0].is_open())  //blad otwarcia pliku
		exit(-1);   //koniec programu

	//sprawdzenie dlugosci pliku
	StatyczneInfo::plikBin[0].seekg(0, ios::end);
	StatyczneInfo::dlugoscPliku = StatyczneInfo::plikBin[0].tellg();
	StatyczneInfo::plikBin[0].seekg(0, ios::beg);


	//tworzenie bufora do ktorego wczytamy plik
	char *dlugoscNagłówka = new char[4];

	//odczytujemy plik bajt po bajcie
	for (unsigned int i = 0; i < 4; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)&dlugoscNagłówka[i], 1);
	}


	char *dlugoscNazwa = new char[4];
	for (unsigned int i = 0; i < 4; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)&dlugoscNazwa[i], 1);
	}
	StatyczneInfo::nazwa = new WCHAR[((unsigned short*)dlugoscNazwa)[0] + 1];
	for (unsigned int i = 0; i < ((unsigned short*)dlugoscNazwa)[0]; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)StatyczneInfo::nazwa + i, 1);
	}
	StatyczneInfo::nazwa[((unsigned short*)dlugoscNazwa)[0] / 2] = 0;

	char *dlugoscWersja = new char[4];
	for (unsigned int i = 0; i < 4; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)&dlugoscWersja[i], 1);
	}
	StatyczneInfo::wersja = new WCHAR[((unsigned short*)dlugoscWersja)[0] + 1];
	for (unsigned int i = 0; i < ((unsigned short*)dlugoscWersja)[0]; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)StatyczneInfo::wersja + i, 1);
	}

	StatyczneInfo::wersja[((unsigned short*)dlugoscWersja)[0] / 2] = 0;
	char *dlugoscAutor = new char[4];
	for (unsigned int i = 0; i < 4; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)&dlugoscAutor[i], 1);
	}
	StatyczneInfo::autor = new WCHAR[((unsigned short*)dlugoscAutor)[0] + 1];
	for (unsigned int i = 0; i < ((unsigned short*)dlugoscAutor)[0]; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)StatyczneInfo::autor + i, 1);
	}

	StatyczneInfo::autor[((unsigned short*)dlugoscAutor)[0] / 2] = 0;
	char *dlugoscLicencja = new char[4];
	for (unsigned int i = 0; i < 4; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)&dlugoscLicencja[i], 1);
	}
	StatyczneInfo::licencja = new WCHAR[((unsigned short*)dlugoscLicencja)[0] + 1];
	for (unsigned int i = 0; i < ((unsigned short*)dlugoscLicencja)[0]; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)StatyczneInfo::licencja + i, 1);
	}

	StatyczneInfo::licencja[((unsigned short*)dlugoscLicencja)[0] / 2] = 0;


	char *dlugoscPlikWyk = new char[4];
	for (unsigned int i = 0; i < 4; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)&dlugoscPlikWyk[i], 1);
	}
	StatyczneInfo::plikWykonywalny = new WCHAR[((unsigned short*)dlugoscPlikWyk)[0] + 1];
	for (unsigned int i = 0; i < ((unsigned short*)dlugoscPlikWyk)[0]; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)StatyczneInfo::plikWykonywalny + i, 1);
	}

	StatyczneInfo::plikWykonywalny[((unsigned short*)dlugoscPlikWyk)[0] / 2] = 0;

	char *dlugoscScD = new char[4];
	for (unsigned int i = 0; i < 4; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)&dlugoscScD[i], 1);
	}
	StatyczneInfo::SciezkaDomyslna = new WCHAR[((unsigned short*)dlugoscScD)[0] + 1];
	for (unsigned int i = 0; i < ((unsigned short*)dlugoscScD)[0]; i++)
	{
		StatyczneInfo::plikBin[0].read((char*)StatyczneInfo::SciezkaDomyslna + i, 1);
	}

	StatyczneInfo::SciezkaDomyslna[((unsigned short*)dlugoscScD)[0] / 2] = 0;

	unsigned long *dlugoscObrOrg = new unsigned long[8];
	for (unsigned int i = 0; i < 8; i++)
	{
		StatyczneInfo::plikBin[0].read(((char*)dlugoscObrOrg)+i, 1);
	}
	unsigned long *dlugoscObr = new unsigned long[8];
	for (unsigned int i = 0; i < 8; i++)
	{
		StatyczneInfo::plikBin[0].read(((char*)dlugoscObr) + i, 1);
	}
	if (((unsigned long*)dlugoscObr)[0] != 0)
	{
		unsigned long dlugosc_po_rozpakowaniu = -1;
		Byte* bufor_docelowy = new byte[(dlugoscObrOrg)[0]];
		Byte* buforSkompresowany = new byte[(dlugoscObr)[0]];

		//czytamy plik
		for (unsigned long i = 0; i < ((unsigned long*)dlugoscObr)[0]; i++)
		{
			StatyczneInfo::plikBin[0].read((char*)&buforSkompresowany[i], 1);

		}

		//rozpakowyjemy
		uncompress((Bytef*)bufor_docelowy, (uLong*)dlugoscObrOrg, (Bytef*)buforSkompresowany, ((long*)dlugoscObr)[0]);



		tagBITMAPFILEHEADER bfh = *(tagBITMAPFILEHEADER*)(bufor_docelowy);
		tagBITMAPINFOHEADER bih = *(tagBITMAPINFOHEADER*)(bufor_docelowy + sizeof(tagBITMAPFILEHEADER));
		RGBQUAD             rgb = *(RGBQUAD*)(bufor_docelowy + sizeof(tagBITMAPFILEHEADER)+sizeof(tagBITMAPINFOHEADER));

		StatyczneInfo::obrazekInfo.bmiColors[0] = rgb;
		StatyczneInfo::obrazekInfo.bmiHeader = bih;

		char* pPixels = (char*)(bufor_docelowy + bfh.bfOffBits);

		char* ppvBits;

		StatyczneInfo::obrazek = CreateDIBSection(NULL, &StatyczneInfo::obrazekInfo, DIB_RGB_COLORS, (void**)&ppvBits, NULL, 0);
		SetDIBits(NULL, StatyczneInfo::obrazek, 0, bih.biHeight, pPixels, &StatyczneInfo::obrazekInfo, DIB_RGB_COLORS);

		//GetObject(StatyczneInfo::obrazek, sizeof(BITMAP), &cBitmap);
	}


	//tworzenie bufora do ktorego zapiszemy dane rozpakowane przez biblioteke zlib
	//wielkosc bufora dla bezpieczenistwa powinna byc
	//odpowiednio duza aby rozpakowane dany zmiescily sie
	//mozna bylo oczywiscie zapisac rozmiar danych przed spakowaniem do pliku
	//maksymalnie dane mogą mieć wielkość 5000 bajtow
	//jezeli mamy wiekszy plik to odpowiedni musimy zwiekszyc ta wartosc
	//char * bufor_docelowy = new char[5000];

	//unsigned long dlugosc_po_rozpakowaniu;

	//rozpakowyjemy
	//uncompress((Bytef*)bufor_docelowy, (uLong*)&dlugosc_po_rozpakowaniu, (Bytef*)bufor, dlugosc_pliku);

	//tworzenie pliku w ktorym zapiszemy rozpakowane dane
	/*plik_po_rozpakowaniu.open("rozpakowany.txt", ios::binary | ios::out);
	//zapis danych do pliku
	for (unsigned int i = 0; i<dlugosc_po_rozpakowaniu; i++)
	{
	plik_po_rozpakowaniu.write((char*)&bufor_docelowy[i], 1);
	}
	//zamykamy strumienie plikow
	plik.close();
	plik_po_rozpakowaniu.close();*/

	StatyczneInfo::NaglowkiDl = StatyczneInfo::plikBin[0].tellg();

}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR test, INT iCmdShow)
{
	odpakuj();
	Checkbox1 = LoadBitmap(hinstance, MAKEINTRESOURCE(2));
	Checkbox2 = LoadBitmap(hinstance, MAKEINTRESOURCE(3));
	hbmObraz = LoadBitmap(hinstance, MAKEINTRESOURCE(1));
	for (int i = 0; i < 50 * 150; i++)
	{
		logoRandom[i] = (rand() % 2) * 900 - 450;
	}
	for (int i = 50 * 150; i < 100 * 150; i++)
	{
		logoRandom[i] = rand() % 180 - 90;
	}
	logoCzas = 0;
	for (int i = 0; i < 10; i++)
		PrzyciskStan[i] = 0;
	for (int i = 0; i < 1024; i++)
	{
		animowane[i, 0] = animowane[i, 1] = animowane[i, 2] = animowane[i, 3] = animowane[i, 4] = 0;
	}
	hbmObraz = LoadBitmap(hinstance, MAKEINTRESOURCE(1));

	ciemnyTlo = CreateSolidBrush(RGB(47, 47, 49));
	ciemnyTloB = CreateSolidBrush(RGB(55, 55, 58));
	ciemnyTlo2 = CreateSolidBrush(RGB(62, 62, 66));
	ciemnyTlo3 = CreateSolidBrush(RGB(37, 37, 39));
	ciemnyTlo3B = CreateSolidBrush(RGB(55, 55, 58));
	ciemnyTlo4 = CreateSolidBrush(RGB(65, 65, 70));
	ciemnyTlo4B = CreateSolidBrush(RGB(70, 70, 76));
	ciemnyTlo5 = CreateSolidBrush(RGB(75, 75, 82));
	jasnyTlo1 = CreateSolidBrush(RGB(225, 220, 210));
	jasnyTlo2 = CreateSolidBrush(RGB(255, 255, 255));
	Szymon1 = CreateSolidBrush(RGB(0, 153, 253));
	Szymon2 = CreateSolidBrush(RGB(30, 75, 104));
	czarny = CreateSolidBrush(RGB(0, 0, 0));
	niebieski = CreateSolidBrush(RGB(20, 40, 240));
	hinstance = hInstance;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)ciemnyTlo;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("PilotPC - Instalator"),  // window caption
		WS_POPUP | WS_MINIMIZE,      // window style
		GetSystemMetrics(SM_CXSCREEN) / 2 - 225,            // initial x position
		GetSystemMetrics(SM_CYSCREEN) / 2 - 325,            // initial y position
		450,            // initial x size
		650,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters
	//SendMessage(hWnd, WM_CTLCOLORSTATIC, g_hBrush, 0);
	ShowWindow(hWnd, iCmdShow);

	UpdateWindow(hWnd);

	SetTimer(hWnd, 1, 10, TimerProc);
	HFONT hNormalFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	rysujStałe(hInstance);

	string parametry = string(test);
	if (parametry.length() > 0 && !IsRunAsAdmin())
	{
		MessageBox(hWnd, jezyk::napisy[WymaganeUprawneiniaAdministratora], jezyk::napisy[BladPodczasInstalacji], MB_ICONERROR);
		exit(-1);
	}
	if (parametry.length() > 1 && parametry.substr(0, 2) == string("PL"))
	{
		jezyk::laduj(jezyk::jezyki::Polski);

	}
	else if (parametry.length() > 1 && parametry.substr(0, 2) == string("EN"))
	{
		jezyk::laduj(jezyk::jezyki::Angielski);

	}
	else if (parametry.length() > 1 && parametry.substr(0, 2) == string("RU"))
	{
		jezyk::laduj(jezyk::jezyki::Rosyjski);

	}
	if (parametry.length() > 1 && (parametry.substr(0, 2) == string("PL") || parametry.substr(0, 2) == string("RU") || parametry.substr(0, 2) == string("EN")))
	{
		if (parametry.length() > 4 && (parametry.substr(3, 2) == string("/u")))
		{
			DWORD dlugosc = GetWindowTextLength(folder);
			LPWSTR Bufor = (LPWSTR)GlobalAlloc(GPTR, dlugosc * 2 + 2);
			GetWindowText(folder, Bufor, dlugosc + 2);
			trwa = true;

			instalacja::odinstaluj(hinstance, hWnd);
		}
		else if (parametry.length() > 4 && parametry[3] == '"')
		{
			string folder1;
			wstring folder2;
			LPCWSTR folder3 = L"c:\\program files\\PilotPC";
			systemStartBool = wszyscy = skrotMenuStart = skrotPulpit = false;
			int i = 4;
			for (; i < parametry.length(); i++)
			{
				if (parametry[i] == '"')
				{
					folder1 = parametry.substr(4, i - 4);
					convert(folder1, folder2);
					folder3 = folder2.c_str();
					break;
				}

			}
			for (; i < parametry.length(); i++)
			{
				if (parametry[i] == '/')
				{
					if (parametry[i + 1] == 's')
					{
						systemStartBool = true;
						i = i + 2;
					}
					else if (parametry[i + 1] == 'm')
					{
						skrotMenuStart = true;
						i = i + 2;
					}
					else if (parametry[i + 1] == 'p')
					{
						skrotPulpit = true;
						i = i + 2;
					}
					else if (parametry[i + 1] == 'w')
					{
						wszyscy = true;
						i = i + 2;
					}
				}

			}
			trwa = true;

			StanInstalacji = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
				SS_LEFT, 25, 470, 400, 20, hWnd, NULL, hInstance, NULL);
			SendMessage(StanInstalacji, WM_SETFONT, (WPARAM)PilotPCCzcionka, 0);

			logoCzas = GetTickCount();
			instalacja::hins = hInstance;
			ins = new instalacja(systemStartBool, wszyscy, folder3, skrotPulpit, skrotMenuStart, folder2, StanInstalacji);
			(*ins).start(hWnd);
		}
		else
			wybor(hinstance);

	}
	else
		wybierzJezyk(hInstance);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_MOUSEMOVE)
		{
			int xPos = GET_X_LPARAM(msg.lParam);
			int yPos = GET_Y_LPARAM(msg.lParam);

			przerysuj(msg.hwnd);
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);



	return msg.wParam;
}  // WinMain


void drawRadio(HDC hDC, int itemState, HWND hwnd, HBRUSH tlo, LPWSTR txt, int Txtlen, boolean zaznaczone){

	if (Checkbox1 == NULL)
		Checkbox1 = LoadBitmap(hinstance, MAKEINTRESOURCE(2));
	if (Checkbox2 == NULL)
		Checkbox2 = LoadBitmap(hinstance, MAKEINTRESOURCE(3));
	RECT prost;
	prost.left = 0;
	prost.top = 0;
	prost.right = 32;
	prost.bottom = 32;

	RECT prostTlo;
	prostTlo.left = 0;
	prostTlo.top = 0;
	prostTlo.right = 400;
	prostTlo.bottom = 25;
	FillRect(hDC, &prostTlo, tlo);
	/*HBRUSH PedzelZiel, Pudelko;
	HPEN OlowekCzerw, Piornik;
	if (itemState & ODS_SELECTED) {


	PedzelZiel = CreateSolidBrush(0x444444);
	OlowekCzerw = CreatePen(PS_DOT, 1, 0xFFFFFF);
	}
	else if (itemState & ODS_HOTLIGHT) {


	PedzelZiel = CreateSolidBrush(0x444444);
	OlowekCzerw = CreatePen(PS_DOT, 1, 0xFFFFFF);
	}
	else{

	PedzelZiel = CreateSolidBrush(0x000000);
	OlowekCzerw = CreatePen(PS_DOT, 1, 0xEEEEEE);

	}
	Pudelko = (HBRUSH)SelectObject(hDC, PedzelZiel);
	Piornik = (HPEN)SelectObject(hDC, OlowekCzerw);
	Ellipse(hDC, 0, 0, 24, 24);
	SelectObject(hDC, Pudelko);
	SelectObject(hDC, Piornik);
	if (zaznaczone)
	{
	Ellipse(hDC, 8, 8, 16, 16);

	}
	DeleteObject(OlowekCzerw);
	DeleteObject(PedzelZiel);*/
	RECT rc;
	GetClientRect(hwnd, &rc);

	SetBkMode(hDC, TRANSPARENT);


	HDC hdcNowy = CreateCompatibleDC(hDC);
	HBITMAP hbmOld;
	if (zaznaczone)
		hbmOld = (HBITMAP)SelectObject(hdcNowy, Checkbox1);
	else
		hbmOld = (HBITMAP)SelectObject(hdcNowy, Checkbox2);
	BitBlt(hDC, 4, 5, 16, 16, hdcNowy, 0, 0, SRCCOPY);
	SelectObject(hdcNowy, hbmOld);
	DeleteDC(hdcNowy);

	char buf[255];
	GetWindowText(hwnd, txt, 255);
	rc.left += 28;
	SetTextColor(hDC, RGB(255, 255, 255));
	SelectObject(hDC, hNormalFont);
	DrawText(hDC, txt, Txtlen, &rc, DT_VCENTER | DT_SINGLELINE);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;

	int xPos, yPos;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		OnPaint(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_CTLCOLOREDIT:
		hdc = (HDC)wParam;
		SetBkMode(hdc, (int)ciemnyTlo2);
		SetTextColor(hdc, RGB(255, 255, 255));
		return(LRESULT)ciemnyTlo3;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break; case WM_CTLCOLORSTATIC:
		{
			hdc = (HDC)wParam;

			//for (int i = 0; i < 3;i++)
			//if (hCtl == przyciskJezyk[i])
			if ((HWND)lParam == CopyTxt)
			{
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 255, 255));
				return(LRESULT)ciemnyTlo3;
			}
			else
			{
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 255, 255));
				return(LRESULT)ciemnyTlo;
			}
		}
			break;

		case WM_CTLCOLORDLG:

			hdc = (HDC)wParam;

			//for (int i = 0; i < 3;i++)
			//if (hCtl == przyciskJezyk[i])
			if ((HWND)lParam == CopyTxt)
			{
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 255, 255));
				return(LRESULT)ciemnyTlo3;
			}
			else
			{
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 255, 255));
				return(LRESULT)ciemnyTlo;
			}

			break;
		case WM_DRAWITEM:
		{
							DRAWITEMSTRUCT *dis = (DRAWITEMSTRUCT*)lParam;
							if (dis->CtlID > 999 && dis->CtlID < 1003)
								drawButtonRed(dis, przyciskJezyk[dis->CtlID - 1000], ciemnyTlo2, ciemnyTlo, jezyk::nazwyJezykow[dis->CtlID - 1000], jezyk::nazwyJezykowLen[dis->CtlID - 1000]);
							else if (dis->CtlID == 2000)
								drawButtonRed(dis, WyborOdinstaluj, ciemnyTlo5, ciemnyTlo4, jezyk::napisy[Odinstaluj], stringDlugosc(jezyk::napisy[Odinstaluj]));
							else if (dis->CtlID == 2001)
								drawButtonRed(dis, WyborInstaluj, ciemnyTlo2, ciemnyTlo, jezyk::napisy[InstalujPonownie], stringDlugosc(jezyk::napisy[InstalujPonownie]));
							else if (dis->CtlID == 1998)
								drawButtonRed(dis, przyciskMin, ciemnyTlo2, ciemnyTlo, L"_", 1);
							else if (dis->CtlID == 1999)
								drawButtonRed(dis, przyciskX, ciemnyTlo2, ciemnyTlo, L"X", 1);
							else if (dis->CtlID == 2002)
								drawButtonRed(dis, LicencjaZaakceptuj, ciemnyTlo2, ciemnyTlo3, jezyk::napisy[Zaakceptuj], stringDlugosc(jezyk::napisy[Zaakceptuj]));
							else if (dis->CtlID == 2003)
								drawButtonRed(dis, JavaNieB, ciemnyTlo2, ciemnyTlo, jezyk::napisy[JavaNie], stringDlugosc(jezyk::napisy[JavaNie]));
							else if (dis->CtlID == 2004)
								drawButtonRed(dis, JavaTakB, ciemnyTlo4, ciemnyTlo5, jezyk::napisy[JavaTak], stringDlugosc(jezyk::napisy[JavaTak]));
							else if (dis->CtlID == 2010)
								drawButtonRed(dis, g_hPrzycisk, ciemnyTlo2, ciemnyTlo3, jezyk::napisy[Instaluj], stringDlugosc(jezyk::napisy[Instaluj]));
							else if (dis->CtlID == 2999)
								drawButtonRed(dis, folderButton, ciemnyTlo2, ciemnyTlo3, jezyk::napisy[Wybierz], stringDlugosc(jezyk::napisy[Wybierz]));
							else if (dis->CtlID == 3000)
								drawRadio(dis->hDC, dis->itemState, user1, ciemnyTlo, jezyk::napisy[DlaObecnegoUzytkownika], stringDlugosc(jezyk::napisy[DlaObecnegoUzytkownika]), !wszyscy);
							else if (dis->CtlID == 3001)
								drawRadio(dis->hDC, dis->itemState, userWiele, ciemnyTlo, jezyk::napisy[DlaWszystkichUzytkownikow], stringDlugosc(jezyk::napisy[DlaWszystkichUzytkownikow]), wszyscy);
							else if (dis->CtlID == 3002)
								drawRadio(dis->hDC, dis->itemState, systemStart, ciemnyTlo, jezyk::napisy[UruchamiajAutomatyczneiPrzyStarcieSystemu], stringDlugosc(jezyk::napisy[UruchamiajAutomatyczneiPrzyStarcieSystemu]), systemStartBool);
							else if (dis->CtlID == 3003)
								drawRadio(dis->hDC, dis->itemState, skrotP, ciemnyTlo, jezyk::napisy[SkrotNaPulpicie], stringDlugosc(jezyk::napisy[SkrotNaPulpicie]), skrotPulpit);
							else if (dis->CtlID == 3004)
								drawRadio(dis->hDC, dis->itemState, skrotMS, ciemnyTlo, jezyk::napisy[SkrotWMenuStart], stringDlugosc(jezyk::napisy[SkrotWMenuStart]), skrotMenuStart);

							/*switch (dis->CtlID){
							case (int)1000: drawButtonRed(dis, przyciskJezyk[0]); break;
							case (int)1001: drawButtonBlue(dis, przyciskJezyk[1]); break;
							}*/
							return TRUE;
		}

		case WM_COMMAND:

			/*switch (LOWORD(wParam)){
			case BTNRED: MessageBox(hWnd, L"Red Button Pressed", L"Red", MB_OK); break;
			case BTNBLUE: MessageBox(hWnd, L"Blue Button Pressed", L"Blue", MB_OK); break;
			}*/

			if ((HWND)lParam == g_hPrzycisk)
			{
				DWORD dlugosc = GetWindowTextLength(folder);
				LPWSTR Bufor = (LPWSTR)GlobalAlloc(GPTR, dlugosc * 2 + 2);
				GetWindowText(folder, Bufor, dlugosc + 2);
				trwa = true;
				//Bufor[dlugosc] = 0;
				DestroyWindow(user1);
				DestroyWindow(userWiele);
				DestroyWindow(systemStart);
				DestroyWindow(skrotMS);
				DestroyWindow(skrotP);
				DestroyWindow(folder);
				DestroyWindow(folderButton);
				DestroyWindow(FolderTxt);
				DestroyWindow(g_hPrzycisk);

				wstring wfolder;
				logoCzas = GetTickCount();
				ins = new instalacja(systemStartBool, wszyscy, Bufor, skrotPulpit, skrotMenuStart, wstring(Bufor), StanInstalacji);
				(*ins).start(hWnd);
			}for (int i = 0; i < 3; i++)
			{
				if ((HWND)lParam == przyciskJezyk[i])
				{
					/*for (int i2 = 0; i2 < 3; i2++)
					{
					DestroyWindow(przyciskJezyk[i2]);
					}*/
					jezyk::laduj((jezyk::jezyki)i);
					wybor(hinstance);
					//nrAni = 1;
					//animacjaCzas = GetTickCount();
					return NULL;
				}
			}
			if ((HWND)lParam == WyborInstaluj)
			{
				//Bufor[dlugosc] = 0;
				/*DestroyWindow(WyborInstaluj);
				DestroyWindow(WyborOdinstaluj);
				DestroyWindow(WyborTxt);*/

				wyswietl(hinstance);
				nrAni = 4;
				animacjaCzas = GetTickCount();
			}if ((HWND)lParam == WyborOdinstaluj)
			{
				DWORD dlugosc = GetWindowTextLength(folder);
				LPWSTR Bufor = (LPWSTR)GlobalAlloc(GPTR, dlugosc * 2 + 2);
				GetWindowText(folder, Bufor, dlugosc + 2);
				trwa = true;
				//Bufor[dlugosc] = 0;
				DestroyWindow(WyborInstaluj);
				DestroyWindow(WyborOdinstaluj);
				DestroyWindow(WyborTxt);

				instalacja::odinstaluj(hinstance, hWnd);
			}
			else if ((HWND)lParam == user1)
			{
				SendMessage(user1, BM_SETCHECK, 1, 0);
				SendMessage(userWiele, BM_SETCHECK, 0, 0);
				wszyscy = false;
				if (userWiele != NULL)
					drawRadio(GetDC(userWiele), 0, userWiele, ciemnyTlo, jezyk::napisy[DlaWszystkichUzytkownikow], stringDlugosc(jezyk::napisy[DlaWszystkichUzytkownikow]), wszyscy);
				if (user1 != NULL)
					drawRadio(GetDC(user1), 0, user1, ciemnyTlo, jezyk::napisy[DlaObecnegoUzytkownika], stringDlugosc(jezyk::napisy[DlaObecnegoUzytkownika]), !wszyscy);
			}
			else if ((HWND)lParam == userWiele)
			{
				SendMessage(user1, BM_SETCHECK, 0, 0);
				SendMessage(userWiele, BM_SETCHECK, 1, 0);
				wszyscy = true;
				if (userWiele != NULL)
					drawRadio(GetDC(userWiele), 0, userWiele, ciemnyTlo, jezyk::napisy[DlaWszystkichUzytkownikow], stringDlugosc(jezyk::napisy[DlaWszystkichUzytkownikow]), wszyscy);
				if (user1 != NULL)
					drawRadio(GetDC(user1), 0, user1, ciemnyTlo, jezyk::napisy[DlaObecnegoUzytkownika], stringDlugosc(jezyk::napisy[DlaObecnegoUzytkownika]), !wszyscy);
			}
			else if ((HWND)lParam == systemStart)
			{
				if (systemStartBool)
				{
					SendMessage(systemStart, BM_SETCHECK, 0, 0);
					systemStartBool = false;
				}
				else
				{
					SendMessage(systemStart, BM_SETCHECK, 1, 0);
					systemStartBool = true;
				}
			}
			else if ((HWND)lParam == skrotP)
			{
				if (skrotPulpit)
				{
					SendMessage(skrotP, BM_SETCHECK, 0, 0);
					skrotPulpit = false;
				}
				else
				{
					SendMessage(skrotP, BM_SETCHECK, 1, 0);
					skrotPulpit = true;
				}
			}
			else if ((HWND)lParam == skrotMS)
			{
				if (skrotMenuStart)
				{
					SendMessage(skrotMS, BM_SETCHECK, 0, 0);
					skrotMenuStart = false;
				}
				else
				{
					SendMessage(skrotMS, BM_SETCHECK, 1, 0);
					skrotMenuStart = true;
				}
			}
			else if ((HWND)lParam == przyciskX)
			{
				exit(0);
			}
			else if ((HWND)lParam == przyciskMin)
			{
				ShowWindow(hWnd, SW_MINIMIZE);
			}
			else if ((HWND)lParam == LicencjaZaakceptuj)
			{
				DWORD dlugosc = GetWindowTextLength(folder);
				LPWSTR Bufor = (LPWSTR)GlobalAlloc(GPTR, dlugosc * 2 + 2);
				GetWindowText(folder, Bufor, dlugosc + 2);
				trwa = true;
				//Bufor[dlugosc] = 0;
				//DestroyWindow(LicencjaZaakceptuj);
				//DestroyWindow(LicencjaTxt);
				wyswietl2(hinstance);
			}
			else if ((HWND)lParam == JavaNieB)
			{
				exit(0);
			}
			else if ((HWND)lParam == JavaTakB)
			{
				//DestroyWindow(JavaTakB);
				//DestroyWindow(JavaNieB);
				//DestroyWindow(JavaTxt);
				wyswietl3(hinstance);
			}
			else if ((HWND)lParam == folderButton)
			{
				TCHAR szDir[MAX_PATH];
				BROWSEINFO bInfo;
				bInfo.hwndOwner = hWnd;
				bInfo.pidlRoot = NULL;
				bInfo.pszDisplayName = szDir; // Address of a buffer to receive the display name of the folder selected by the user
				bInfo.lpszTitle = jezyk::napisy[WybierzFolder]; // Title of the dialog
				bInfo.ulFlags = 0;
				bInfo.lpfn = NULL;
				bInfo.lParam = 0;
				bInfo.iImage = -1;

				LPITEMIDLIST lpItem = SHBrowseForFolder(&bInfo);
				if (lpItem != NULL)
				{
					SHGetPathFromIDList(lpItem, szDir);

					SetWindowText(folder, szDir);
				}
			}

			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc