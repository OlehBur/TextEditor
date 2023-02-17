#include "Header.h"


TextField currentTextField(0);

void AddMenuWnd(HWND hWnd) {
	HMENU mainMenu = CreateMenu(),
		font = CreateMenu(), fontSize = CreateMenu(),
		bold = CreateMenu(), ital = CreateMenu(), underL = CreateMenu(), crossL = CreateMenu();

	AppendMenu(mainMenu, MF_POPUP, (UINT)font, L"Шрифт");
	//AppendMenu(calcMenu, MFT_STRING, OPEN_CALC, L"Відкрити");
	//AppendMenu(calcMenu, MFT_STRING, CLOSE_CALC, L"Закрити");
	AppendMenu(mainMenu, MF_POPUP, (UINT)fontSize, L"Розмір шрифту");
	//AppendMenu(progMenu, MFT_STRING, OPEN_MYPROG, L"Відкрити");
	//AppendMenu(progMenu, MFT_STRING, CLOSE_MYPROG, L"Закрити");

	SetMenu(hWnd, mainMenu);
}

//wstring* ConvertStrToWstr(string str) {
//	return &wstring(str.begin(), str.end())/*.c_str()*/;
//};
//
//wstring* ConvertIntToWstr(int num) {
//	string s; 
//	s += num;
//	return ConvertStrToWstr(s);
//};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	//RECT screenArea;
	HWND hWnd;
	MSG msg;

	WNDCLASS textEditor;
	textEditor.hInstance = hInstance;
	textEditor.lpszClassName = wndClassName;
	textEditor.lpfnWndProc = WndProc;
	textEditor.style = CS_BYTEALIGNWINDOW,
		textEditor.hIcon = LoadIcon(NULL, IDI_SHIELD);
	textEditor.hCursor = LoadCursor(NULL, IDC_HAND);
	textEditor.lpszMenuName = NULL;
	textEditor.cbClsExtra = 0;
	textEditor.cbWndExtra = 0;
	textEditor.hbrBackground = (HBRUSH)COLOR_WINDOW;


	if (!RegisterClass(&textEditor)) return 0;

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &screenArea, 0);
	parentHwnd = hWnd = CreateWindow(wndClassName,
		wndName,
		WS_OVERLAPPEDWINDOW,//WS_POPUP|WS_MAXIMIZE,
		GetSystemMetrics(SM_CXSCREEN) / 2 - GetSystemMetrics(SM_CXSCREEN) / 3,
		GetSystemMetrics(SM_CYSCREEN) / 2 - GetSystemMetrics(SM_CYSCREEN) / 3,
		GetSystemMetrics(SM_CXSCREEN) / 1.5,
		GetSystemMetrics(SM_CYSCREEN) / 1.5,//screenArea.bottom,
		HWND_DESKTOP,
		NULL,//StdDialog(IDD_TEXTSETTINGDLG),
		hInstance,
		NULL);

	if (!hWnd)
		return MessageBox(hWnd, L"Не створено дескриптор вікна.", L"Увага!", MB_OK | MB_ICONWARNING);

	ShowWindow(hWnd, nCmdShow);

	hInst = hInstance;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	RECT rt;
	PAINTSTRUCT ps;
	HFONT newFont, oldFont;
	static int mouseClickX, mouseClickY, wndWidth, wndHeight, f = 0,
		arrOrientations[4] = { TEXTFIELD_ORIENTATION_LR, TEXTFIELD_ORIENTATION_RL,TEXTFIELD_ORIENTATION_UD,TEXTFIELD_ORIENTATION_DU };
	/*static const char alphavit[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '!',  '-', '.',  ',', '(', ')', '\n' };*/
	static std::string currentStr;
	static bool isMouseLPress = false;

		//static HWND hWndDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_TEXTSETTINGDLG), hWnd, DialogFunc, 0);

	switch (message) {
	case WM_CREATE:
		//CreateWindowW(L"Button", L"Бутонка", WS_VISIBLE | WS_CHILD /*| BS_RIGHT*/, 100, 150, 300, 100, hWnd, NULL, NULL, NULL);
		
		//SetWindowPos(dlgHwnd, dlgHwnd, 0,0, 778, 112, SWP_SHOWWINDOW);
		//AddMenuWnd(hWnd);
		break;
	case WM_SIZE:
		//ClientToScreen(hWnd, &firstWndPoint);
		/*wndRect.left = firstWndPoint.x;
		wndRect.top = firstWndPoint.y;
		wndRect.right=wndWidth = LOWORD(lParam);
		wndRect.bottom=wndHeight = HIWORD(lParam);*/
		InvalidateRect(hWnd, &wndRect, true);
		GetClientRect(hWnd, &wndRect);
		wndRect.top += settingDlgHeight;
		if (!dialogIsOpened) {
			dlgHwnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TEXTSETTINGDLG), hWnd, DialogFunc);
			ShowWindow(dlgHwnd, SW_SHOW);
		}
		//SetWindowPos(dlgHwnd, HWND_TOPMOST, wndWidth- settingDlgWidth, wndHeight- settingDlgHeight, settingDlgWidth, settingDlgHeight/*dlgRect.right, dlgRect.left*/, SWP_SHOWWINDOW);
		break;
	case WM_LBUTTONDOWN:
		SetFocus(hWnd);
		mouseClickX = LOWORD(lParam);
		mouseClickY = HIWORD(lParam);
		if (mouseClickY > wndRect.top) {
			currentTextField.SetPos(mouseClickX, mouseClickY);
			//buffTF.CreateTextField(mouseClickX, mouseClickY);
			//for (int s = 0; s < 5 + rand() % 5; s++)
			//		(rand() % 4 == 3) ? currentStr += " " : currentStr += alphavit[rand() % sizeof(alphavit)];
			InvalidateRect(hWnd, &wndRect, true);
			//isMouseLPress = true;
		}
		break;
	case WM_RBUTTONDOWN:
		mouseClickX = LOWORD(lParam);
		mouseClickY = HIWORD(lParam);
		//ShowWindow(hWndDlg, SW_SHOW);
	/*SetWindowPos(hWndDlg, hWndDlg, mouseClickX, mouseClickY, mouseClickX + 200, mouseClickY + 200, SWP_ASYNCWINDOWPOS);*/

		//MoveWindow(hWndDlg, mouseClickX, mouseClickY, 600, 500, false);
	//buffTF.SetTextOrientation(arrOrientations[rand() % 4]);
		InvalidateRect(hWnd, &wndRect, true);
		break;
	case WM_LBUTTONUP:
		//isMouseLPress = false;
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
			/*case VK_UP:
				break;
			case VK_DOWN:
				break;*/
		case VK_HOME:
			break;
		case VK_END:
			break;
		case VK_INSERT:
			break;
		case VK_DELETE:
			break;
		}
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case '\b':          // backspace
			currentTextField.SubSym();
			break;
		case '\t':         // tab
			currentTextField.AddSym(' ');
			currentTextField.AddSym(' ');
			currentTextField.AddSym(' ');
			break;

		case '\n':          // ctrl enter
			//buffTF.AddSym('\n');
			break;

		case '\r':          //  ENTER
			currentTextField.AddSym('\n');
			//ubfocus of text field
			break;

		default:            // other
			currentTextField.AddSym(wParam);
			break;
		}
		//buffTF.SetTexColor(100, 230, 32);
		//buffTF.SetTextBackgroundColor(0, 0, 200);

		InvalidateRect(hWnd, &wndRect, true);
		break;
	case WM_MOUSEMOVE:// WM_LBUTTONDOWN:


		//if (isMouseLPress) {

		//}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(10, 10, 10)));
		SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
		Rectangle(hdc, wndRect.left, wndRect.top, wndRect.right, wndRect.bottom);

		//if (buffTF.isInit)
		currentTextField.DrawTextField(hdc, ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		dialogIsOpened = false;
		EndDialog(hWnd, LOWORD(wParam));
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
};

INT_PTR CALLBACK DialogFunc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	static HDC hdcDlg;
	static HWND fontsCBhWnd, sizesCBhWnd;
	static const int fontsCount = 57, const fontSizesCount = 44;
	static int currentFontIndex = 0, currentSizeIndex = 0,// rotateSym=0,
		textBold = 0, textColor = 0, backgrColor = 0/*, aligmentType= TEXTFIELD_ALIGMENT_LEFT*//*short checkAligm*/;
	static const TCHAR* fontNamesList[fontsCount],// = { L"Arial", L"Arial Black", L"Bahnchrift", L"Calibri",  L"Cambria",  L"Candara",  L"Comic Sans MS",  L"Consolas",  L"Corbel",  L"Courier New",  L"Ebrima",  L"Franklin Gothic Medium",  L"Gabriola",  L"Gadugi",  L"Georgia",  L"HoloLens MDL2 Assets",  L"Impact",  L"Ink Free", L"Japanese Text", L"Leelawadee UI", L"Lucida Console", L"Lucida Sans Unicode", L"Malgum Gothic", L"Marlett", L"Microsoft Himalaya", L"Microsoft JhengHei", L"Microsoft New Tai Lue", L"Microsoft PhagsPa", L"Microsoft Sans Serif", L"Microsoft Tai Le",  L"Microsoft YaHei",  L"Microsoft Yi Baiti",  L"MingLiu-ExtB",  L"Mongolian Baiti",  L"MS Gothic",  L"MV Boli",  L"Myanmar Text", L"Nirmala UI", L"Palatino LinoType", L"Segoe MDL2 Assets", L"Segoe Print",  L"Segoe Script",  L"Segoe UI",  L"Segoe UI Historic",  L"Segoe UI Emoji",  L"Segoe UI Symbol",  L"SimSun", L"Sitka", L"Sylfaen", L"Symbol", L"Tahoma", L"Times New Roman", L"Trebuchet MS", L"Verdana",  L"Webdings", L"Wingdings", L"Yu Gothic" },
		* fontSizesList[30];
	//dlgHwnd=hDlg;
	//MoveWindow(hDlg, )
	//static FILE* file{};
	for (int f = 0; f < fontsCount; f++)
		fontNamesList[f] = defaulFonts[f];
	for (int s = 0; s < fontSizesCount - 1; s++)
		fontSizesList[s] = (wchar_t*)(new std::wstring(std::to_wstring(8 + s * 2)))->c_str();

	MoveWindow(hDlg, /*firstWndPoint.x, firstWndPoint.y*/wndRect.left, wndRect.top - settingDlgHeight, settingDlgWidth*1.5, settingDlgHeight, false);
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_LBUTTONDOWN:
		/*AllocConsole();
		freopen_s(&file, "CONOUT$", "w", stdout);
		printf("%d %d", LOWORD(lParam), HIWORD(lParam));*/
		break;
	case WM_INITDIALOG:
		dialogIsOpened = true;

		//SendDlgItemMessage(hDlg, IDC_LRBUTTON, BS_DISA, wParam, lParam);
		//fonts list
		for (short int i = 0; i < fontsCount - 1; i++)
			SendDlgItemMessage(hDlg, IDC_FONT, CB_ADDSTRING, 0, (LPARAM)fontNamesList[i]);
		SendDlgItemMessage(hDlg, IDC_FONT, CB_SETCURSEL, currentFontIndex, 0);
		//sizes list 
		for (short int j = 0; j < fontSizesCount - 1; j++)
			SendDlgItemMessage(hDlg, IDC_TEXTSIZE, CB_ADDSTRING, 0, (LPARAM)fontSizesList[j]);
		SendDlgItemMessage(hDlg, IDC_TEXTSIZE, CB_SETCURSEL, 6/*currentSizeIndex*/, 0);

		//bold slider
		SendDlgItemMessage(hDlg, IDC_BOLDFONTSLIDER, TBM_SETRANGE, true, MAKELPARAM(0, 2));// 7/*10*/));
		SendDlgItemMessage(hDlg, IDC_BOLDFONTSLIDER, TBM_SETPOS, true, 0);
		//textColor slider
		SendDlgItemMessage(hDlg, IDC_TEXTCOLORSLIDER, TBM_SETRANGE, true, MAKELPARAM(0, 100));
		SendDlgItemMessage(hDlg, IDC_TEXTCOLORSLIDER, TBM_SETPOS, true, 100);
		//backgrColor slider
		SendDlgItemMessage(hDlg, IDC_BACKGRCOLORSLIDER, TBM_SETRANGE, true, MAKELPARAM(0, 100));
		SendDlgItemMessage(hDlg, IDC_BACKGRCOLORSLIDER, TBM_SETPOS, true, 100);

		//aligm
		//CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO3, IDC_RADIO2); set Center rad
		SendDlgItemMessage(hDlg, IDC_RADIO2, BM_SETCHECK, BST_CHECKED, 1);

		//rotate of write (buttons)
		EnableWindow(GetDlgItem(hDlg, IDC_LRBUTTON), currentTextField.IsReverseSym());
		EnableWindow(GetDlgItem(hDlg, IDC_RLBUTTON), !currentTextField.IsReverseSym());
		EnableWindow(GetDlgItem(hDlg, IDC_UDBUTTON), currentTextField.IsReverseStr());
		EnableWindow(GetDlgItem(hDlg, IDC_DUBUTTON), !currentTextField.IsReverseStr());

		//symbols rotate
		//SetDlgItemText(hDlg, IDC_ANGLETEXT, ConvertIntToWstr(rotateSym).c_str());
		//SendDlgItemMessage(hDlg, IDC_ROTATEANGLESLIDER, TBM_SETRANGE, true, MAKELPARAM(0, 360));
		//SendDlgItemMessage(hDlg, IDC_ROTATEANGLESLIDER, TBM_SETPOS, true, 0);

		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_FONT:
			currentFontIndex= SendMessage(GetDlgItem(hDlg, IDC_FONT), CB_GETCURSEL, 0, 0);
			currentTextField.SetBaseFont(currentFontIndex/*(LPCWSTR)fontNamesList[currentFontIndex]*/);
			break;
		case IDC_TEXTSIZE:
			currentSizeIndex = SendMessage(GetDlgItem(hDlg, IDC_TEXTSIZE), CB_GETCURSEL, 0, 0);
			currentTextField.SetSizeText(8 + currentSizeIndex * 2);
			break;
		case IDC_RADIO1: 
			currentTextField.SetAligm(TEXTFIELD_ALIGMENT_LEFT);
			break;
		case IDC_RADIO2: 
			currentTextField.SetAligm(TEXTFIELD_ALIGMENT_CENTER);
			break;
		case IDC_RADIO3: 
			currentTextField.SetAligm(TEXTFIELD_ALIGMENT_RIGHT);
			break;
		case IDC_ITAL: 
			currentTextField.SetItal(!currentTextField.IsItal());
			SendMessage(GetDlgItem(hDlg, IDC_ITAL), BM_SETSTYLE, (currentTextField.IsItal())?BS_DEFPUSHBUTTON:BS_FLAT, lParam);
			break;
		case IDC_UNDERL: 
			currentTextField.SetUnderL(!currentTextField.IsUnderL());
			SendMessage(GetDlgItem(hDlg, IDC_UNDERL), BM_SETSTYLE, (currentTextField.IsUnderL()) ? BS_DEFPUSHBUTTON : BS_FLAT, lParam);
			break;
		case IDC_CROSSL: 
			currentTextField.SetCrossL(!currentTextField.IsCrossL());
			SendMessage(GetDlgItem(hDlg, IDC_CROSSL), BM_SETSTYLE, (currentTextField.IsCrossL()) ? BS_DEFPUSHBUTTON : BS_FLAT, lParam);
			break;
		case IDC_LRBUTTON: 
			/*(buffTF.GetReverseSym()) ?
				SendMessage(GetDlgItem(hDlg, IDC_LRBUTTON), BM_SETSTYLE, BS_DEFPUSHBUTTON, lParam) :
				SendMessage(GetDlgItem(hDlg, IDC_LRBUTTON), BM_SETSTYLE, BS_FLAT, lParam);*/
			currentTextField.SetTextOrientation(TEXTFIELD_ORIENTATION_LR);
			break;
		case IDC_RLBUTTON: 
			/*(!buffTF.GetReverseSym()) ?
				SendMessage(GetDlgItem(hDlg, IDC_RLBUTTON), BM_SETSTYLE, BS_DEFPUSHBUTTON, lParam) :
				SendMessage(GetDlgItem(hDlg, IDC_RLBUTTON), BM_SETSTYLE, BS_FLAT, lParam);*/
			currentTextField.SetTextOrientation(TEXTFIELD_ORIENTATION_RL);
			break;
		case IDC_UDBUTTON: 
			/*(buffTF.GetReverseStr()) ?
				SendMessage(GetDlgItem(hDlg, IDC_UDBUTTON), BM_SETSTYLE, BS_DEFPUSHBUTTON, lParam) :
				SendMessage(GetDlgItem(hDlg, IDC_UDBUTTON), BM_SETSTYLE, BS_FLAT, lParam);*/
			currentTextField.SetTextOrientation(TEXTFIELD_ORIENTATION_UD);
			//InvalidateRect(hDlg, NULL, true);
			break;
		case IDC_DUBUTTON: 
			/*(!buffTF.GetReverseStr()) ?
				SendMessage(GetDlgItem(hDlg, IDC_DUBUTTON), BM_SETSTYLE, BS_DEFPUSHBUTTON, lParam) :
				SendMessage(GetDlgItem(hDlg, IDC_DUBUTTON), BM_SETSTYLE, BS_FLAT, lParam);*/
			currentTextField.SetTextOrientation(TEXTFIELD_ORIENTATION_DU);
			/*break;
				default:*/		

		}

		//rotate buttons
		EnableWindow(GetDlgItem(hDlg, IDC_LRBUTTON), currentTextField.IsReverseSym());
		EnableWindow(GetDlgItem(hDlg, IDC_RLBUTTON), !currentTextField.IsReverseSym());
		EnableWindow(GetDlgItem(hDlg, IDC_UDBUTTON), currentTextField.IsReverseStr());
		EnableWindow(GetDlgItem(hDlg, IDC_DUBUTTON), !currentTextField.IsReverseStr());

		//font tupes buttons
		//EnableWindow(GetDlgItem(hDlg, IDC_ITAL), !currentTextField.IsItal());
		//EnableWindow(GetDlgItem(hDlg, IDC_UNDERL), !currentTextField.IsUnderL());
		//EnableWindow(GetDlgItem(hDlg, IDC_CROSSL), !currentTextField.IsCrossL());
		InvalidateRect(parentHwnd, &wndRect, true);
		break;
	case WM_HSCROLL:
		textBold = SendDlgItemMessage(hDlg, IDC_BOLDFONTSLIDER, TBM_GETPOS, 0, 0);
		textColor = SendDlgItemMessage(hDlg, IDC_TEXTCOLORSLIDER, TBM_GETPOS, 0, 0);
		backgrColor = SendDlgItemMessage(hDlg, IDC_BACKGRCOLORSLIDER, TBM_GETPOS, 0, 0);
		//rotateSym = SendDlgItemMessage(hDlg, IDC_ROTATEANGLESLIDER, TBM_GETPOS, 0, 0);

		currentTextField.SetWeight(textBold/* * 100*/);
		currentTextField.SetTextColor_Generator(textColor);
		currentTextField.SetTextBackgroundColor_Generator(backgrColor);
		//currentTextField.SetSymbolsRotate(rotateSym);

		//SetDlgItemText(hDlg, IDC_ANGLETEXT, ConvertIntToWstr(rotateSym/*currentTextField.GetSymOrientationInDegrees()*/).c_str());

		InvalidateRect(parentHwnd, &wndRect, true);
		break;
	case WM_CHAR:
		WndProc(parentHwnd, message, wParam, lParam);
		break;
	case WM_SIZE:
		/*dlgRect.left = 0;
		dlgRect.top = 0;
		dlgRect.right = LOWORD(lParam);
		dlgRect.bottom = HIWORD(lParam);*/
		break;
	}
	return(INT_PTR)FALSE;
}