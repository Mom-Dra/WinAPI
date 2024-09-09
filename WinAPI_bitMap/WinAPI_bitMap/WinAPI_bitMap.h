#pragma once

#include "framework.h"
#include "resource.h"

#define TIMER_ANI 3
#define TIMER_KEYSTATE 4


HWND g_hWnd{ NULL };
HINSTANCE g_bInst;


HBITMAP hBackImage;
BITMAP bitBack;

HBITMAP hTransparentImage;
BITMAP bitTransparent;

HBITMAP hAniImage;
BITMAP bitAni;

constexpr int SPRITE_X{ 57 };
constexpr int SPRITE_Y{ 52 };
constexpr int SPRITE_COUNT{ 16 };
constexpr int SPRITE_DIR{ 2 };

constexpr int CIRCLE_RADIUS{ 50 };

int Run_Frame_Max = 0;
int Run_Frame_Min = 0;
int currFrame = Run_Frame_Min;

POINT ptAni{ 400, 400 };

HBITMAP hDoubleBufferImage;
RECT rectView;

// 키가 뭐가 눌렸는지 확인 용도
TCHAR sKeyState[128];

ULONG_PTR g_GdiPlusToken;

void Gdi_Init()
{
	GdiplusStartupInput gpsi;

	GdiplusStartup(&g_GdiPlusToken, &gpsi, NULL);
}

void Gdi_Draw(HDC hdc)
{
	Graphics graphics(hdc);

	SolidBrush brush(Color(255, 255, 0, 0));
	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);

	Point pointF(10.0f, 20.0f);
	graphics.DrawString(L"Hello GDI+!", -1, &font, pointF, &brush);

	Pen pen(Color(128, 0, 255, 255));
	graphics.DrawLine(&pen, 0, 0, 200, 100);

	Image img{ (WCHAR*)L"image/sigong.png" };

	int w = img.GetWidth();
	int h = img.GetHeight();
	graphics.DrawImage(&img, 100, 100, w, h);

	Image img2((WCHAR*)L"image/zero_run.png");
	w = img2.GetWidth() / SPRITE_COUNT;
	h = img2.GetHeight() / SPRITE_DIR;
	
	int xStart{ currFrame * w };
	int yStart{ 0 };

	ImageAttributes imgAttr0;
	imgAttr0.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(&img2, Rect(200, 100, w, h), xStart, yStart, w, h, UnitPixel, &imgAttr0);

	brush.SetColor(Color(128, 255, 0, 0));
	graphics.FillRectangle(&brush, 100, 100, 200, 300);

	Image* pImg = nullptr;
	pImg = Image::FromFile((WCHAR*)L"image/sigong.png");
	int xPos{ 300 };
	int yPos{ 200 };

	if (pImg)
	{
		w = pImg->GetWidth();
		h = pImg->GetHeight();

		Gdiplus::Matrix mat;
		static int rot{ 0 };

		mat.RotateAt(rot % 360,
			Gdiplus::PointF(xPos + (float)(w / 2), yPos + (float)(h / 2)));

		graphics.SetTransform(&mat);
		graphics.DrawImage(pImg, xPos, yPos, w, h);
		rot += 10;

		mat.Reset();
		graphics.SetTransform(&mat);
	}

	ImageAttributes imgAttr;
	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	yPos = 200;

	graphics.DrawImage(&img2, Rect(200, 100, w, h),
		0, 0, w, h, UnitPixel, &imgAttr);

	if (pImg)
	{
		REAL transparcy = 0.5f;

		ColorMatrix colorMatrix =
		{
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, transparcy, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		};
		
		imgAttr.SetColorMatrix(&colorMatrix);
		xPos = 400;

		graphics.DrawImage(pImg, Rect(xPos, yPos, w, h), 0, 0, w, h, UnitPixel, &imgAttr);

		xPos = 600;
		pImg->RotateFlip(RotateNoneFlipX);
	}

	if (pImg) delete pImg;
}

void Gdi_End()
{
	GdiplusShutdown(g_GdiPlusToken);
}

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

		TransparentBlt(hdc, ptAni.x, ptAni.y, bx, by, hMemDC, xStart, yStart, bx, by, RGB(255, 0, 255));

		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}

void DrawBitMapDoubleBuffering(const HWND& hWnd, const HDC& hdc)
{
	HDC hDoubleBufferDC;
	HBITMAP hOldDoubleBufferBitMap;
	int dx, dy;

	hDoubleBufferDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);

	hOldDoubleBufferBitMap = (HBITMAP)SelectObject(hDoubleBufferDC, hDoubleBufferImage);

	DrawBitMap(hWnd, hDoubleBufferDC);

	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hDoubleBufferDC, 0, 0, SRCCOPY);
	SelectObject(hDoubleBufferDC, hOldDoubleBufferBitMap);
	DeleteDC(hDoubleBufferDC);

	Gdi_Draw(hdc);
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
	InvalidateRect(hWnd, nullptr, FALSE);
}

VOID CALLBACK KeyStateProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (GetKeyState('W') & 0x8000)
	{
		wsprintf(sKeyState, TEXT("%s"), _T("W-key pressed"));
	}
	else if (GetKeyState('A') & 0x8000)
	{
		wsprintf(sKeyState, TEXT("%s"), _T("A-key pressed"));
	}
	else if (GetKeyState('S') & 0x8000)
	{
		wsprintf(sKeyState, TEXT("%s"), _T("S-key pressed"));
	}
	else if(GetKeyState('D') & 0x8000)
	{
		wsprintf(sKeyState, TEXT("%s"), _T("D-key pressed"));
	}
}

BOOL CALLBACK Dialog1_Proc(HWND hDlg, UINT uMsg, WPARAM wParam, DWORD dwTime)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		return TRUE;
		break;
	
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, 0);
			break;

		case IDCANCEL:

			break;

		default:
			break;
		}

		break;

	default:
		break;
	}
}

void Update()
{
	DWORD newTime{ GetTickCount() };
	static DWORD oldTime{ newTime };

	if (newTime - oldTime < 100)
		return;

	// 보간?
	oldTime = newTime - (newTime - oldTime) % 100;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		ptAni.x -= 10;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		ptAni.x += 10;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		ptAni.y -= 10;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		ptAni.y += 10;
	}
}