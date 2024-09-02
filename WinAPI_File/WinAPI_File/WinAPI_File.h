#pragma once
#include <stdio.h>
#include "framework.h"
#include "resource.h"

constexpr int MAX_STR_SIZE{ 100 };
constexpr int SHOW_STR_SIZE{ 100 };

void OutFromFile(TCHAR fileName[], const HWND& hWnd)
{
	FILE* fPtr;
	HDC hdc;
	int line{ 0 };
	TCHAR buffer[500];
	hdc = GetDC(hWnd);

#ifdef _UNICODE
	_tfopen_s(&fPtr, fileName, _T("r, ccs = UNICODE"));
#else
	_tfopen_s(&fPtr, fileName, _T("r"));
#endif // 
	while (_fgetts(buffer, 100, fPtr) != NULL)
	{
		if (buffer[_tcslen(buffer) - 1] == _T('\n'))
			buffer[_tcslen(buffer) - 1] = NULL;

		TextOut(hdc, 0, line * 20, buffer, _tcslen(buffer));
		++line;
	}

	fclose(fPtr);
	ReleaseDC(hWnd, hdc);
}

void SaveFile(TCHAR chatStr[MAX_STR_SIZE][100], int strSize)
{
	FILE* fptr;

	TCHAR fileName[] = _T("chatlog.txt");

#ifdef _UNICODE
	_tfopen_s(&fptr, fileName, _T("w"));
#else
	_tfopen_s(&fptr, fileName, _T("w");
#endif

	// 3°³
	// a b c
	// 0 1 2 3

	for (int i = 0; i < strSize; ++i)
	{
		if (chatStr[i][_tcslen(chatStr[i])] == NULL)
			chatStr[i][_tcslen(chatStr[i])] = _T('\n');

		_fputts(chatStr[i], fptr);
	}

	if (_tcslen(chatStr[strSize]) != 0)
	{
		if (chatStr[strSize][_tcslen(chatStr[strSize])] == NULL)
			chatStr[strSize][_tcslen(chatStr[strSize])] = _T('\n');

		_fputts(chatStr[strSize], fptr);
	}

	fclose(fptr);
}