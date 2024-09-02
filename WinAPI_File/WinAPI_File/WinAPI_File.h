#pragma once
#include <stdio.h>
#include "framework.h"
#include "resource.h"

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