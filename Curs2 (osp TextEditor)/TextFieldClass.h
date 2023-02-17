#pragma once

#include <windows.h>
#include <string>
#include <vector>

using namespace std;

#define TEXTFIELD_ORIENTATION_NORMAL 0
#define TEXTFIELD_ORIENTATION_LR 0
#define TEXTFIELD_ORIENTATION_RL 1
#define TEXTFIELD_ORIENTATION_UD 2
#define TEXTFIELD_ORIENTATION_DU 3

#define TEXTFIELD_ALIGMENT_LEFT 0
#define TEXTFIELD_ALIGMENT_CENTER 1
#define TEXTFIELD_ALIGMENT_RIGHT 2

const LPCWSTR defaulFonts[] = { L"Arial", L"Arial Black", L"Bahnchrift", L"Calibri",  L"Cambria",  L"Candara",  L"Comic Sans MS",  L"Consolas",  L"Corbel",  L"Courier New",  L"Ebrima",  L"Franklin Gothic Medium",  L"Gabriola",  L"Gadugi",  L"Georgia",  L"HoloLens MDL2 Assets",  L"Impact",  L"Ink Free", L"Japanese Text", L"Leelawadee UI", L"Lucida Console", L"Lucida Sans Unicode", L"Malgum Gothic", L"Marlett", L"Microsoft Himalaya", L"Microsoft JhengHei", L"Microsoft New Tai Lue", L"Microsoft PhagsPa", L"Microsoft Sans Serif", L"Microsoft Tai Le",  L"Microsoft YaHei",  L"Microsoft Yi Baiti",  L"MingLiu-ExtB",  L"Mongolian Baiti",  L"MS Gothic",  L"MV Boli",  L"Myanmar Text", L"Nirmala UI", L"Palatino LinoType", L"Segoe MDL2 Assets", L"Segoe Print",  L"Segoe Script",  L"Segoe UI",  L"Segoe UI Historic",  L"Segoe UI Emoji",  L"Segoe UI Symbol",  L"SimSun", L"Sitka", L"Sylfaen", L"Symbol", L"Tahoma", L"Times New Roman", L"Trebuchet MS", L"Verdana",  L"Webdings", L"Wingdings", L"Yu Gothic" };

class TextField {
	int format = 0;
	int maxLengthOfStrings = 3;
	int indexMaxLengthStr = 1;
	int buffLength = 3;
	int strings = 1;
	int bottomEnter = 0;
	int stringIndex = 0;
	int boldTypes[3] = { 400, 700, 600 };

	int backgroundColor[3]{ 255,255,255 }; 
	int penColor[3] = { 0,0,0 }; 
	int textColor[3] = { 0,0,0 };

	int sizeTextH = 20; 
	int sizeTextW = sizeTextH / 2.5;
	int weightText = 300;

	int orientationText = 0; 
	int orientationSymbols = 0/*[4] = { 0, 2700, 900, 1800  }*/; 
	int alignment = 1;//0,1,2
		
	bool isReverseSym = false, 
		isReverseStr = false,//isMirrorActiveted=false;
		ital = false,
		underline = false,
		strike = false;

	LPCWSTR baseFont;
	//string baseFontStr;
	HWND hWnd;
	TEXTMETRIC textMetrics;
	RECT textField{ 0,0,0,0 },
		rotateTextField{ 0,0,0,0 },
		textFrame{ 0,0,0,0 };
	POINT centrText;

	HPEN framePen;
	//HBRUSH frameBrush = CreateSolidBrush(RGB(255, 255, 255)), textBrush = (HBRUSH)RGB(255, 255, 255);
	HFONT font;
	LONG defWndStyle, mirrorWndStyle;
	//std::string text;
	//vector <char> text;
	string allTextStr;
	vector <string> allText;
	//char textCursor[2] = { '|',' ' };
	//bool textCursorIndex = 0;

	int inline GetMaxCntSymStr();
	/*int inline GetSymbolsBetweenEnters();*/
	void DrawFrame(HDC&, PAINTSTRUCT&);
	void ReverseSymbols();
	void ReverseStrings();
	void UpdateStrAllText();
	void RegetTextMetrixParametres(HDC);

public:
	TextField(int, int);//void CreateTextField(int, int);
	TextField(int);

	bool IsItal();
	bool IsUnderL();
	bool IsCrossL();
	bool IsReverseStr();
	bool IsReverseSym();
	RECT* GetTextAreaRect();
	int GetSymOrientationInDegrees();

	void SetItal(bool);
	void SetUnderL(bool);
	void SetCrossL(bool);
	void SetPos(int, int);
	void SetTextColor_Generator(int);
	void SetTextBackgroundColor_Generator(int);
	void SetAligm(int );
	void SetTextOrientation(int);
	void SetSymbolsRotate(int);
	void SetWeight(short int);
	void SetSizeText(short int);
	void SetBaseFont(int/*LPCWSTR*/);

	void UpdateFont(HDC hdc);
	void UpdateRects();
	void AddSym(char);
	void SubSym();
	void DrawTextField(HDC&, PAINTSTRUCT&);

	~TextField();
};

//extern TextField buffTF;