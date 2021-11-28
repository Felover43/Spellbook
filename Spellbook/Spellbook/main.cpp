
#include <windows.h>
#include <WinUser.h>
#include <stdio.h>
#include "clicker.h"
#include "copycat.h"
#include <string>
#include "helpers.h"
#include "record.h"
#include <iostream>
#include <string.h>

#define Tools 109
using namespace std;
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK DialogProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK copyProcedure(HWND, UINT, WPARAM, LPARAM);
void addcontrol(HWND);
int registerDialogClass(HINSTANCE);
int registercopyClass(HINSTANCE);
void createcopy(HWND);
void createdialog(HWND);
void addD1Control(HWND);
void addD2Control(HWND);
HWND mainW;
HWND Hsleep;
// changed WinMain to wWinMain
int WINAPI WinMain(_In_ HINSTANCE hinst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR args, _In_ int ncmdshow)

{
	
	
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_HOTLIGHT;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hinst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;
	mainW = CreateWindowExW(WS_EX_TOOLWINDOW ,L"myWindowClass", L"Dark Window", WS_POPUP | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX| WS_VISIBLE, 100, 100, 400, 200, NULL, NULL, NULL, NULL);
		
	if (!registerDialogClass(hinst))
		return -1;
	if (!registercopyClass(hinst))
		return -1;
	HACCEL hAccelTable = LoadAccelerators(hinst, MAKEINTRESOURCE(Tools));
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
	return 0;
}
//******************** MAIN WINDOW PROCEDURE**************/
//********************************************************/
//********************************************************/
//********************************************************/
//********************************************************/
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	

	switch (msg)
	{
	case WM_CREATE:
		{
			addcontrol(hWnd);
			break;
		}

	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case  1:
		{
			createdialog(hWnd);
			break;
		}
		case 2:
		{
			createcopy(hWnd);
			break;
		}
		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);

	}
	return 0;
}
/* BUTTONS FOR MAIN WINDOW*********
************************************
**********************************
***********************************/
void addcontrol(HWND h)
{
	
	CreateWindow("BUTTON", "Mage Hand", WS_VISIBLE | WS_CHILD | WS_BORDER, 35, 90, 150, 50, h, (HMENU)1, NULL, NULL);	
	CreateWindow("BUTTON", "CopyCat", WS_VISIBLE | WS_CHILD | WS_BORDER, 35, 20, 150, 50, h, (HMENU)2, NULL, NULL);
	CreateWindow("BUTTON", "Invisibility:WIP", WS_VISIBLE | WS_CHILD | WS_BORDER, 195, 90, 150, 50, h, NULL, NULL, NULL);
	CreateWindow("BUTTON", "Identifier:WIP", WS_VISIBLE | WS_CHILD | WS_BORDER, 195, 20, 150, 50, h, NULL, NULL, NULL);

}
//*************************** CLICKER:PROCEDURE**********************************
//
//
//*********************************************************************************
LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(230, 230, 230));
	char sleep[3];
	static bool randi = true;
	COLORREF iTextColor = RGB(139, 0, 139);
	double isleep = 3;
	while (true)
	{
		if (msg == WM_CLOSE)
		{
			EnableWindow(mainW, true);
			DestroyWindow(hWnd);
			DeleteObject(hBrush);

			break;
		}
		if (msg == WM_CREATE)
		{
			addD1Control(hWnd);
			break;
		}
		if (msg == WM_CTLCOLORSTATIC)
		{

			HDC hdcStatic = (HDC)wp;
			SetTextColor(hdcStatic, RGB(139, 0, 139));
			SetBkColor(hdcStatic, RGB(0, 0, 0));
			return (INT_PTR)hBrush;
		}

		if (GetAsyncKeyState(VK_F1))
		{
			GetWindowText(Hsleep, sleep, 3);

			if (is_digits(sleep))
			{
				isleep = std::stoi(sleep);
				if (isleep > 0)
				{
					EnableWindow(hWnd, false);
					startclicker(isleep, randi);
					EnableWindow(hWnd, true);
				}
			}
			else
				Beep(440, 500);
			break;

		}

		if (msg == WM_COMMAND)
		{
			switch (LOWORD(wp))
			{
			case  2:
			{
				
				randi = true;
				break;
			}
			case 3:
			{
				randi = false;
				break;
			}
			break;
			}
		}
	
	return DefWindowProc(hWnd, msg, wp, lp);
	}
	
	
		

	
	return DefWindowProc(hWnd, msg, wp, lp);
}

//*************************** COPYCAT:PROCEDURE**********************************
//
//
//*******************************************************************************
LRESULT CALLBACK copyProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(230, 230, 230));
	COLORREF iTextColor = RGB(139, 0, 139);
	static HWND Hsave;
	static record rec;
	string save="";
	string check = "";
	while (true)
	{
		if (msg == WM_CLOSE)
		{
			EnableWindow(mainW, true);
			DestroyWindow(hWnd);
			DeleteObject(hBrush);
			rec.~record();
			break;
		}
		if (msg == WM_CREATE)
		{

			addD2Control(hWnd);
			Hsave = CreateWindow(TEXT("Edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 100, 50, 180, 20, hWnd, NULL, NULL, NULL);	//savefile name
			break;
		}
		if (msg == WM_CTLCOLORSTATIC)
		{

			HDC hdcStatic = (HDC)wp;
			SetTextColor(hdcStatic, RGB(139, 0, 139));
			SetBkColor(hdcStatic, RGB(0, 0, 0));
			return (INT_PTR)hBrush;
		}

		if (GetAsyncKeyState(VK_F1))
		{
			if (rec.getvector().empty())	// vector is always empty check why
			{
				while (GetAsyncKeyState(VK_F1)) {}
				EnableWindow(hWnd, false);
				copycatrecord(rec);
				EnableWindow(hWnd, true);
			}
			else
			{
				EnableWindow(hWnd, false);
				copycatexecute(rec);
				EnableWindow(hWnd, true);
			}

		}



		if (msg == WM_COMMAND)
		{
			switch (LOWORD(wp))
			{
			case  4:
			{
				if (!rec.getvector().empty())
				{
					GetWindowText(Hsave, LPSTR(save.c_str()),GetWindowTextLength(Hsave)+1);
					if (!strcmp(save.c_str(),""))
						save = "savefile";
					SaveTheCat(rec,save);
				}
				else
					Beep(440, 500);
				break;
			}
			case 5:
			{
				GetWindowText(Hsave, LPSTR(save.c_str()), GetWindowTextLength(Hsave) + 1);
				if (!strcmp(save.c_str(), ""))
					save = "savefile";
				UploadTheCat(rec,save);
				break;
			}
			case 6:
			{
				rec.cleancat();
				break;
			}
			break;
			}
		}

		return DefWindowProc(hWnd, msg, wp, lp);
	}





	return DefWindowProc(hWnd, msg, wp, lp);
}
int registerDialogClass(HINSTANCE hinst)
{
	WNDCLASSW dialog = { 0 };
	dialog.hbrBackground = (HBRUSH)COLOR_HOTLIGHT;
	dialog.hCursor = LoadCursor(NULL, IDC_ARROW);
	dialog.hInstance = hinst;
	dialog.lpszClassName = L"myDialogClass";
	dialog.lpfnWndProc = DialogProcedure;

	if (!RegisterClassW(&dialog))
		return -1;
	return 1;
}
int registercopyClass(HINSTANCE hinst)
{
	WNDCLASSW copy = { 0 };
	copy.hbrBackground = (HBRUSH)COLOR_HOTLIGHT;
	copy.hCursor = LoadCursor(NULL, IDC_ARROW);
	copy.hInstance = hinst;
	copy.lpszClassName = L"mycopyClass";
	copy.lpfnWndProc = copyProcedure;

	if (!RegisterClassW(&copy))
		return -1;

	return 1;

}

void createdialog(HWND h)
{
	CreateWindowW(L"myDialogClass", L"DC", WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE, 400, 200, 400, 200, NULL, NULL, NULL, NULL);
	EnableWindow(h, false);
}
void createcopy(HWND h)
{
	CreateWindowW(L"mycopyClass", L"DC", WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE, 400, 200, 400, 200, NULL, NULL, NULL, NULL);
	EnableWindow(h, false);
}
void addD1Control(HWND h)
{
	
	CreateWindow("BUTTON", "Random - on", WS_VISIBLE | WS_CHILD | WS_BORDER, 135, 120, 100, 20, h, (HMENU)2, NULL, NULL);
	CreateWindow("BUTTON", "Random - off", WS_VISIBLE | WS_CHILD | WS_BORDER, 135, 100, 100, 20, h, (HMENU)3, NULL, NULL);
	CreateWindowW(L"Static", L"Intervals(in secs):", WS_CHILD | WS_VISIBLE, 104, 72, 130, 15, h, NULL, NULL, NULL);
	Hsleep = CreateWindow(TEXT("Edit"), TEXT("0"), WS_CHILD | WS_VISIBLE | WS_BORDER, 220, 70, 40, 20, h, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"F1 to start", WS_CHILD | WS_VISIBLE, 100, 0, 65, 15, h, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"F2 to stop", WS_CHILD | WS_VISIBLE, 220, 0, 64, 15, h, NULL, NULL, NULL);
	
	

}
void addD2Control(HWND h)
{
	CreateWindowW(L"Static", L"F1 to Record and Start", WS_CHILD | WS_VISIBLE, 125, 0, 144, 15, h, NULL, NULL, NULL);
	CreateWindowW(L"Static", L"F2 to stop", WS_CHILD | WS_VISIBLE, 160, 25, 64, 15, h, NULL, NULL, NULL);
	CreateWindow("BUTTON", "Save Recording", WS_VISIBLE | WS_CHILD | WS_BORDER, 35, 80, 150, 40, h, (HMENU)4, NULL, NULL);
	CreateWindow("BUTTON", "Upload Recording", WS_VISIBLE | WS_CHILD | WS_BORDER, 195, 80, 150, 40, h, (HMENU)5, NULL, NULL);
	CreateWindow("BUTTON", "Clean Cat", WS_VISIBLE | WS_CHILD | WS_BORDER, 135, 130, 100, 20, h, (HMENU)6, NULL, NULL);
}


