#include "Square.h"
#include "framework.h"
#include <string>

namespace MomDra
{
	Square::Square(int x, int y, int width, int height) noexcept : node{ x, y }, width{ width }, height{ height }
	{

	}

	void Square::Draw(const HDC& hdc) const noexcept
	{
		int left{ width * node.x };
		int top{ height * node.y };
		
		HBRUSH brush;
		COLORREF color = RGB(255, 0, 0);
		switch (state)
		{
		case MomDra::Square::State::START:
			color = RGB(255, 0, 0);
			break;
		case MomDra::Square::State::END:
			color = RGB(0, 255, 0);
			break;
		case MomDra::Square::State::WALL:
			color = RGB(128, 128, 128);
			break;
		default:
			color = RGB(255, 255, 255);
			break;
		}

		brush = CreateSolidBrush(color);

		HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(hdc, brush));
		Rectangle(hdc, left, top, left + width, top + height);
		SelectObject(hdc, oldBrush);
		
		// 아래 밑에 F(x)
		// 왼쪽 위에 G(x)
		// 오른쪽 위에 H(x)

		SetBkColor(hdc, color);

		std::wstring tmpStr{ std::to_wstring(node.g) };

		TextOut(hdc, left + stringPadding, top + stringPadding, tmpStr.data(), tmpStr.size());
		tmpStr = std::to_wstring(node.h);
		TextOut(hdc, left + width - stringPadding * 2, top + stringPadding, tmpStr.data(), tmpStr.size());
		tmpStr = std::to_wstring(node.F());
		TextOut(hdc, left + width / 2, top + height - stringPadding * 4, tmpStr.data(), tmpStr.size());
		DeleteObject(brush);
	}

	void Square::SetG(int g) noexcept
	{
		node.g = g;
	}

	void Square::SetH(int h) noexcept
	{
		node.h = h;
	}

	void Square::SetState(State state) noexcept
	{
		this->state = state;
	}

	Square::State Square::GetState() const noexcept
	{
		return state;
	}
}

