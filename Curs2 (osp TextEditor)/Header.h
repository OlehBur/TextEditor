#pragma once

#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include "TextFieldClass.h"
#include <CommCtrl.h>//for trackbar
#pragma comment(lib,"comctl32.lib")



HINSTANCE hInst;
TCHAR wndClassName[] = _T("TextEditor");
TCHAR wndName[] = _T("Text Editor");
RECT wndRect, dlgRect;
HWND dlgHwnd, parentHwnd;
//POINT firstWndPoint;
//TextField buffTF;

const int settingDlgWidth = 778, const settingDlgHeight = 112;
bool dialogIsOpened = false;

void AddMenuWnd(HWND hWnd);
//wstring *ConvertStrToWstr(string);
//wstring *ConvertIntToWstr(int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY WinMain(HINSTANCE, HINSTANCE, PSTR, int);
INT_PTR CALLBACK DialogFunc(HWND, UINT, WPARAM, LPARAM);
