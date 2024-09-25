#pragma once

#include "resource.h"

void FileRead(HWND hwnd, const wchar_t* fileName)
{
	HANDLE hFile;
	LPTSTR buffer;
	DWORD size, CharNum;
	int fileSize;

	hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
		return;

	fileSize = GetFileSize(hFile, &size);
	buffer = new TCHAR[(int)fileSize / sizeof(TCHAR) + 1];
	memset(buffer, 0, fileSize);
	ReadFile(hFile, buffer, fileSize, &CharNum, NULL);
	buffer[(int)fileSize / sizeof(TCHAR)] = NULL;
	SetWindowText(hwnd, buffer);
	delete[] buffer;
	CloseHandle(hFile);
}

void FileSave(HWND hwnd, const wchar_t* fileName)
{
	HANDLE hFile;
	LPTSTR buffer;
	int size;

#ifdef _UNICODE
	WORD uni = 0xFEFF;
	DWORD nSize;
#endif // _UNICODE
	hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

#ifdef _UNICODE
	WriteFile(hFile, &uni, 2, &nSize, NULL);
#endif // _UNICODE
	size = GetWindowTextLength(hwnd);
	buffer = new TCHAR[size + 1];
	memset(buffer, 0, (size + 1) * sizeof(TCHAR));
	size = GetWindowText(hwnd, (LPTSTR)buffer, size + 1);
	buffer[size] = NULL;
	WriteFile(hFile, buffer, size * sizeof(TCHAR), (LPDWORD)&size, NULL);
	delete[] buffer;
	CloseHandle(hFile);
}