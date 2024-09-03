#pragma once

#include "framework.h"
#include "resource.h"

#define TIMER_ANI 3

HBITMAP hBackImage;
BITMAP bitBack;

HBITMAP hTransparentImage;
BITMAP bitTransparent;

HBITMAP hAniImage;
BITMAP bitAni;

constexpr int SPRITE_X = 57;
constexpr int SPRITE_Y = 52;
constexpr int SPRITE_COUNT = 16;
constexpr int SPRITE_DIR = 2;

int Run_Frame_Max = 0;
int Run_Frame_Min = 0;
int currFrame = Run_Frame_Min;

void CreateBitMap()
{
	hBackImage = (HBITMAP)LoadImage(NULL, TEXT("Image/winter2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hBackImage == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("이미지 로드 에러"), _T("에러"), MB_OK);
	}
	else
	{
		GetObject(hBackImage, sizeof(BITMAP), &bitBack);
	}



	hTransparentImage = (HBITMAP)LoadImage(NULL, TEXT("Image/sigong.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hTransparentImage == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("이미지 로드 에러"), _T("에러"), MB_OK);
	}
	else
	{
		GetObject(hTransparentImage, sizeof(BITMAP), &bitTransparent);
	}


	hAniImage = (HBITMAP)LoadImage(NULL, TEXT("Image/zero_run.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hAniImage == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("zero_run 이미지 로드 에러"), _T("에러"), MB_OK);
	}
	else
	{
		GetObject(hAniImage, sizeof(BITMAP), &bitAni);
	}

	Run_Frame_Max = bitAni.bmWidth / SPRITE_X - 1;
	Run_Frame_Min = 2;
	currFrame = Run_Frame_Min;
}

void DrawBitMap(const HWND& hWnd, const HDC& hdc)
{
	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx, by;

	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackImage);

		// bitBack 변수
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);

		StretchBlt(hdc, bx, 0, bx / 4, by / 4, hMemDC, 0, 0, bx, by, SRCCOPY);

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}

	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hTransparentImage);

		// bitBack 변수
		bx = bitTransparent.bmWidth;
		by = bitTransparent.bmHeight;

		TransparentBlt(hdc, 200, 200, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}

	{
		hMemDC = CreateCompatibleDC(hdc);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hAniImage);

		// bitBack 변수
		bx = bitAni.bmWidth / SPRITE_COUNT;
		by = bitAni.bmHeight / SPRITE_DIR;

		int xStart { currFrame * bx };
		int yStart{ 0 };

		TransparentBlt(hdc, 400, 400, bx, by, hMemDC, xStart, yStart, bx, by, RGB(255, 0, 255));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}

void DeleteBitmap()
{
	DeleteObject(hBackImage);
	DeleteObject(hTransparentImage);
	DeleteObject(hAniImage);
}

void UpdateFrame(HWND hWnd)
{
	currFrame++;
	if (currFrame > Run_Frame_Max)
		currFrame = Run_Frame_Min;
}

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	UpdateFrame(hWnd);

	InvalidateRect(hWnd, nullptr, false);
}