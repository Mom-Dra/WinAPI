#include "Rectangle.h"
#include "framework.h"

namespace MomDra
{
	Square::Square(int x, int y, int width, int height) noexcept : node{ x, y }, width{ width }, height{ height }
	{

	}

	void Square::Draw(const HDC& hdc) const noexcept
	{
		int left{ width * node.x };
		int top{ height * node.y };

		Rectangle(hdc, left, top, left + width, top + height);
		
		// �Ʒ� �ؿ� F(x)
		// ���� ���� G(x)
		// ������ ���� H(x)

		TextOut(hdc, left + stringPadding, top + stringPadding, _T("ai"), true);
		TextOut(hdc, left + width - stringPadding * 2, top + stringPadding, _T("k"), true);
		TextOut(hdc, left + width / 2, top + height - stringPadding * 4, _T("A"), true);
	}
}

