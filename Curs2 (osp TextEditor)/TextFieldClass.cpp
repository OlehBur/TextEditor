#include "TextFieldClass.h"

int TextField::GetMaxCntSymStr() {
		int maxCount = 0;
		for (int currStr = 0; currStr < allText.size(); currStr++)
			if (maxCount < allText.at(currStr).size())
				maxCount = allText.at(currStr).size();
		return maxCount;
}

	/*int inline TextField::GetSymbolsBetweenEnters() {
		int countRep = 0;
		for (int s = text.size(); text.at(s) != '\n' && s > 0; s--)
			countRep++;
		return countRep;
	}*/
void TextField::DrawFrame(HDC & hdc, PAINTSTRUCT & ps) {
	framePen = CreatePen(PS_SOLID, 1, RGB(penColor[0], penColor[1], penColor[2]));
	SelectObject(hdc, framePen); 
	SelectObject(hdc, CreateSolidBrush(RGB(backgroundColor[0], backgroundColor[1], backgroundColor[2]))/*frameBrush*/);

	Rectangle(hdc, textFrame.left, textFrame.top, textFrame.right, textFrame.bottom);
	//SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(131, 52, 9)));
	//Rectangle(hdc, textField.left, textField.top, textField.right, textField.bottom);
};
void TextField::ReverseSymbols() {
	string buffStr;
	for (int s = 0; s < allText.size(); s++)
		if (allText.at(s).size())
			if (allText.at(s).back() == '\n') {
				allText.at(s).pop_back();
				reverse(allText.at(s).begin(), allText.at(s).end());
				allText.at(s).push_back('\n');
			}
			else if (allText.at(s).front() == '\n') {
				allText.at(s).erase(0, 1);
				reverse(allText.at(s).begin(), allText.at(s).end());
				allText.at(s).insert(allText.at(s).begin(), '\n');
			}
			else
				reverse(allText.at(s).begin(), allText.at(s).end());
	isReverseSym = !isReverseSym;
}; 
void TextField::ReverseStrings() {
	if (allText.size()) {
		//if (!isReverseStr) {
		//	if (!isReverseSym) {
		//		if (allText.at(strings - 1)[0] == '\n')
		//			allText.at(strings - 1).erase(0, 1);
		//		if(allText.at(strings-1).back()!='\n')
		//			allText.at(strings - 1) += '\n';
		//	}
		//	else {
		//		/*if (allText.at(0).back() == '\n')
		//			allText.at(0).pop_back();*/
		//		if(allText.at(0)[0]=='\n')
		//			allText.at(0).erase(0, 1);
		//		if (allText.at(0).back() != '\n')
		//			allText.at(0) += '\n';
		//		//allText.at(0) = '\n' + allText.at(strings - 1);
		//	}
		//}
		//else {
		//	if (!isReverseSym) {
		//		/*allText.at(0).pop_back();*/
		//		if (allText.at(strings - 1).back() == '\n')
		//			allText.at(strings - 1).pop_back();
		//		if (allText.at(strings - 1)[0] != '\n')
		//			allText.at(strings - 1) = '\n' + allText.at(strings - 1);
		//	}
		//	else {
		//		if (allText.at(0).back() == '\n')
		//			allText.at(0).pop_back();
		//		if (allText.at(0)[0] != '\n')
		//			allText.at(0) = '\n'+ allText.at(0);
		//		//allText.at(strings - 1).erase(0,1);
		//	}
		//}

		/* \n deleter */
		for (int s = 0; s < allText.size(); s++) {
			if (allText.at(s).size()) {
				if (allText.at(s).front()  == '\n')
					allText.at(s).erase(0,1);
				if (allText.at(s).back() == '\n')
					allText.at(s).pop_back();
			}
		}
		/* reverser */
		for (int beg = 0, bac = allText.size() - 1; beg < bac; beg++, bac--)
			swap(allText.at(beg), allText.at(bac));
		isReverseStr = !isReverseStr;

		/* \n add */
		if (!isReverseStr && !isReverseSym) {
			for (int s = 0; s < allText.size() - 1; s++)
				allText.at(s).push_back('\n');
			//allText.at(s).insert(allText.at(s).begin(), '\n');
		}
		else if (isReverseStr && !isReverseSym) {
			for (int s = 1; s < allText.size(); s++)
				allText.at(s).insert(allText.at(s).begin(), '\n');
		}
		else if (!isReverseStr && isReverseSym) {
			for (int s = 0; s < allText.size() - 1; s++)
				allText.at(s).push_back('\n');
		}
		else if (isReverseStr && isReverseSym) {
			for (int s = 1; s < allText.size(); s++)
				allText.at(s).insert(allText.at(s).begin(), '\n');
			int b = 0;
		}
	}
}
void TextField::UpdateStrAllText() {
	allTextStr = "";
	for (int str = 0; str < allText.size(); str++)
		allTextStr += allText.at(str);
}
void TextField::RegetTextMetrixParametres(HDC hdc) {
	GetTextMetricsW(hdc, &textMetrics);
	//exteranalLead = textMetrics.tmExternalLeading;
	sizeTextH = textMetrics.tmHeight;
	sizeTextW = sizeTextH / 2.5;
	bottomEnter = /*textMetrics.tmAscent+ textMetrics.tmDescent*/(/*textMetrics.tmExternalLeading +*/ sizeTextH) * (strings - 1);
}
bool TextField::IsItal() {
	return ital;
};
bool TextField::IsUnderL() {
	return underline;
};
bool TextField::IsCrossL() {
	return strike;
};
bool TextField::IsReverseStr() {
	return isReverseStr;
}
bool TextField::IsReverseSym() {
	return isReverseSym;
}
RECT* TextField::GetTextAreaRect() {
	return &textFrame;
}
int TextField::GetSymOrientationInDegrees() {
	return orientationSymbols;
};

void TextField::UpdateFont(HDC hdc) {
	font = /*(ital) ?
		CreateFontA(sizeTextH - .5, sizeTextW, orientationText, orientationSymbols, weightText, ital, underline, strike,
			DEFAULT_CHARSET | EASTEUROPE_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCSTR)baseFont) :*/
		CreateFont(sizeTextH, sizeTextW, orientationText, orientationSymbols, weightText, ital, underline, strike,
			/*DEFAULT_CHARSET | EASTEUROPE_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE*/
			DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, /*TEXT("Arial")*/baseFont/*(LPCSTR)baseFont*/);
	SelectObject(hdc, font);
}
void TextField::UpdateRects() {
	strings = allText.size();
	maxLengthOfStrings = GetMaxCntSymStr();

	textField = RECT({
		centrText.x - (maxLengthOfStrings + 1) / 2 * sizeTextW - sizeTextW,
		centrText.y - sizeTextH / 2,
		centrText.x + (maxLengthOfStrings + 1) / 2 * sizeTextW + sizeTextW,
		centrText.y + sizeTextH / 2 + bottomEnter
		});

	textFrame = RECT({
		textField.left - sizeTextW ,
		textField.top - sizeTextW,
		textField.right + sizeTextW,
		textField.bottom + sizeTextW
		});
}
TextField::TextField/*CreateTextField*/(int xCentr, int yCentr) {
	/*if (!isInit)*/
	allText.push_back("");
	//isInit = true;
	centrText = { xCentr, yCentr };

	//UpdateRects();
}
TextField::TextField/*CreateTextField*/(int emptyCord) {
	/*if (!isInit)*/
	allText.push_back("");
	//isInit = true;
	//centrText = { xCentr, yCentr };

	UpdateRects();
}

void TextField::AddSym(char sym) {
	if (!isReverseSym) {
		if (sym == '\n') {
			if (!isReverseStr) {
				allText.at(strings - 1) += sym;
				allText.push_back("");//new str
				//strings++;
			}
			else {
				allText.at(0).insert(allText.at(0).begin(), sym); //= sym + allText.at(0);
				allText.insert(allText.begin(), "");//new str
				//strings++;
			}
			UpdateRects();
			return;
		}

		if (!isReverseStr)
			allText.at(strings - 1) += sym;
		else allText.at(0) += sym;// = sym + allText.at(0);
		//UpdateRects();
	}
	else {
		if (sym == '\n') {
			if (!isReverseStr) {
				//allText.insert(allText.begin(), "\n");
				allText.at(strings - 1) += sym;
				allText.push_back("");
				//strings++;
			}
			else {
				allText.at(0).insert(allText.at(0).begin(), sym);//=sym+str //+= sym;
				allText.insert(allText.begin(), "");
			}
			UpdateRects();
			return;
		}
		if (!isReverseStr)
			allText.at(strings - 1).insert(allText.at(strings - 1).begin(), sym);// = sym + allText.at(strings - 1);
		else allText.at(0).insert(allText.at(0).begin(), sym);// = sym + allText.at(0);
		UpdateRects();
	}
}
void TextField::SubSym() {
	if (allText.size()) {
		if (!isReverseSym) {

			if (!isReverseStr) {
				if (allText.at(strings - 1).size())
					allText.at(strings - 1).pop_back();
				else
					//strings--;
					if (strings > 1) {
						allText.pop_back();
						allText.at(strings - 2).pop_back();//delete '\n'
					}
			}
			else {
				if (allText.at(0).size())
					allText.at(0).pop_back();
				else
					if (strings > 1) {
						allText.erase(allText.begin());
						allText.at(0).erase(0,1);//delete f '\n'
					}
			}
			/*if (allText.at(strings - 1).back() == '\n') {
				strings--;
				allText.at(strings - 1).pop_back();

				UpdateRects();
				return;
			}*/

			//"text"
			//if (allText.at(strings - 1).size())
			//	allText.at(strings - 1).pop_back();
			//else allText.pop_back();//""
			//UpdateRects();
		}
		else {
			if (!isReverseStr) {
				if (allText.at(strings - 1).size()) {
					allText.at(strings - 1).erase(0, 1);//pop_front();
					//strings--;
					//UpdateRects();
				}
				else if (strings > 1) {
					allText.pop_back();
					allText.at(strings - 2).pop_back();//del \n
				}
			}
			else {
				if (allText.at(0).size()) {
					allText.at(0).erase(0, 1);
				}
				else if (strings > 1) {
					allText.erase(allText.begin());
					allText.at(0).erase(0,1);//del \n in pre str
				}
			}
			//UpdateRects();
			//else {
			//	if (allText.at(0).size()) {
			//		allText.at(0).erase(0, 1);//pop_front();
			//		//strings--;
			//		//UpdateRects();
			//	}
			//	else if (strings > 1) {
			//		allText.erase(allText.begin());
			//		allText.at(0).erase(0, 1);
			//	}
			//}
			
		}
	UpdateRects();
	}
}

void TextField::SetItal(bool val) {
	ital = val;
};
void TextField::SetUnderL(bool val) {
	underline = val;
};
void TextField::SetCrossL(bool val) {
	strike = val;
};

void TextField::SetPos(int x, int y) {
	centrText = { x, y };
}
	///*(red, green, blue): 0-255*/
/*in: double 1 to 0*/
void TextField::SetTextColor_Generator(int coefficient/*int r, int g, int b*/) {
	coefficient = int(coefficient * 2.56 * 6);
	int pos = coefficient / 256,
		x = coefficient % 256, 
		r = 0, g = 0, b = 0;

	switch (pos)
	{
	case 0: 
		r = 255; g = 0; b = 0; g += x;
		break;
	case 1:
		r = 255; g = 255; b = 0; r -= x;
		break;
	case 2: 
		r = 0; g = 255; b = 0; b += x;
		break;
	case 3:
		r = 0; g = 255; b = 255; g -= x;
		break;
	case 4:
		r = 0; g = 0; b = 255; r += x;
		break;
	case 5:
		r = 255; g = 0; b = 255; b -= x;
	}

	textColor[0] = r;
	textColor[1] = g;
	textColor[2] = b;
}
	///*(red, green, blue): 0-255*/
void TextField::SetTextBackgroundColor_Generator(int coefficient/*int r, int g, int b*/) {
	coefficient = int(coefficient * 2.56 * 6);
	int pos = coefficient / 256,
		x = coefficient % 256,
		r = 0, g = 0, b = 0;

	switch (pos)
	{
	case 0:
		r = 255; g = 0; b = 0; g += x;
		break;
	case 1:
		r = 255; g = 255; b = 0; r -= x;
		break;
	case 2:
		r = 0; g = 255; b = 0; b += x;
		break;
	case 3:
		r = 0; g = 255; b = 255; g -= x;
		break;
	case 4:
		r = 0; g = 0; b = 255; r += x;
		break;
	case 5:
		r = 255; g = 0; b = 255; b -= x;
		break;
	case 6:
		r = 255; g = 255; b = 255;
	}
	backgroundColor[0] = r;
	backgroundColor[1] = g;
	backgroundColor[2] = b;

	//textBrush = CreateSolidBrush(RGB(backgroundColor[0], backgroundColor[1], backgroundColor[2]));
}
	/*0-Left, 1-Centr, 2-Right*/
void TextField::SetAligm(int mode) {
	alignment = mode;
}
	/*use a "TFO_" constants*/
void TextField::SetTextOrientation(int orientaion) {
	switch (orientaion) {
	case TEXTFIELD_ORIENTATION_NORMAL || TEXTFIELD_ORIENTATION_LR://ud lr
		//orientationSymbols = 0;
		//orientationText = 0;
		//isRotate = false;
		if (isReverseSym)
			ReverseSymbols();

		//isMirrorActiveted = false;
		break;
	case TEXTFIELD_ORIENTATION_RL:// ud rl
		//orientationSymbols = 1800;
		//orientationText = -1800;
		//isRotate = true;
		if (!isReverseSym)
			ReverseSymbols();


		/*if (!isMirrorActiveted)
			SetWindowLong(hWnd, GWL_EXSTYLE, mirrorWndStyle);*/
			//for (int s = 0; s < text.size(); s++)
			//	text[s] = //UNICODE(text[s] + 202E);
			//isMirrorActiveted = true;
		break;
	case TEXTFIELD_ORIENTATION_UD://lr du
		//orientationSymbols = 0;// 1800;
		if (isReverseStr)
			ReverseStrings();
		/*if (isReverse)
		ReversString();*/
		//orientationText = 2700;
		break;
	case TEXTFIELD_ORIENTATION_DU://du rl
		//orientationSymbols = 1800;
		if (!isReverseStr)
			ReverseStrings();
		/*	if (!isReverse)
				ReversString();*/
				//orientationText = 900;
		break;
	}
	//orientationSymblos = orientaion;
	//orientationText = orientaion;
}
void TextField::SetSymbolsRotate(int degree) {
	orientationSymbols = degree*100;
};
void TextField::SetWeight(short int boldInex) {
	weightText = boldTypes[boldInex];
}
void TextField::SetSizeText(short int size) {
	sizeTextH = size;
	sizeTextW = sizeTextH / 2.5;
}
void TextField::SetBaseFont(/*LPCWSTR*/int fontIndex/*string str*/) {
	baseFont = defaulFonts[fontIndex];
}
void TextField::DrawTextField(HDC& hdc, PAINTSTRUCT& ps/*, std::string str,*//* RECT& rect, int format*/) {
	SetGraphicsMode(hdc, GM_ADVANCED);// advance mode for visal rotated symbols
	UpdateFont(hdc);
	RegetTextMetrixParametres(hdc);
	UpdateStrAllText();
	UpdateRects();

	DrawFrame(hdc, ps);
	SetBkColor(hdc, RGB(backgroundColor[0], backgroundColor[1], backgroundColor[2])/*(COLORREF)textBrush*/);
	SetTextColor(hdc, RGB(textColor[0], textColor[1], textColor[2]));
	
	/*(isRotate) ? TextOut(hdc, textField.left, textField.top+ bottomEnter+ size, std::wstring(text.begin(), text.end()).c_str(), text.size())
		:TextOut(hdc, textField.left, textField.top, std::wstring(text.begin(), text.end()).c_str(), text.size());*/
		//TextOut(hdc, textField.left, textField.top, std::wstring(text.begin(), text.end()).c_str(), text.size());
		/*(isRotate) ?
			DrawTextW(hdc, std::wstring(text.begin(), text.end()).c_str(), text.size(), &rotateTextField, alignment):*/
			//DrawTextW(hdc, std::wstring(text.begin(), text.end()).c_str(), text.size(), &textField, alignment);
	DrawTextW(hdc, std::wstring(allTextStr.begin(), allTextStr.end()).c_str(), allTextStr.size(), &textField, alignment);
}

TextField::~TextField() {
	allText.clear();
}