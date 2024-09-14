#include "stdafx.h"
#include "CBannerCtrl.h"

CBannerCtrl::CBannerCtrl(void)
{
	m_nCurSelected = 0;
	m_bAdd = true;
}

CBannerCtrl::~CBannerCtrl(void)
{
}

void CBannerCtrl::OnMouseHover(WPARAM wParam, SOUI::CPoint ptPos)
{
	SetMsgHandled(FALSE);
	KillTimer(1);
}

void CBannerCtrl::OnMouseLeave()
{
	SetMsgHandled(FALSE);
 	SetTimer(1, 2000);
}

void CBannerCtrl::OnMouseMove(UINT nFlags, SOUI::CPoint pt)
{
	SetMsgHandled(FALSE);
	HCURSOR hCursor = ::LoadCursor(NULL, IDC_HAND);
	::SetCursor(hCursor);
}

void CBannerCtrl::OnLButtonDown(UINT nFlags, SOUI::CPoint pt)
{
	SetMsgHandled(FALSE);
	SetCapture();

	bool bClickDot = false;
	for (int i = 0; i < m_vecDots.size(); i++)
	{
		if (PtInRect(m_vecDots[i], pt))
		{
			bClickDot = true;
			m_nCurSelected = i;
			Invalidate();
			break;
		}
	}

	if (!bClickDot)
	{
		//将当前页面的点击事件通知上层
		//TODO:
	}
}

void CBannerCtrl::OnPaint(IRenderTarget* pRT)
{
	CRect rcClient = GetClientRect();
	CalcDot();

	switch (m_nCurSelected)
	{
	case 0:
		pRT->DrawBitmap(rcClient, m_pBitmap, 0, 0);
		break;
	case 1:
		pRT->DrawBitmap(rcClient, m_pBitmap, 300, 0);
		break;
	case 2:
		pRT->DrawBitmap(rcClient, m_pBitmap, 600, 0);
		break;
	default:
		break;
	}

	//绘制几个点
	for (int i = 0; i < m_vecDots.size(); i++)
	{
		CRect rcDot(m_vecDots[i]);
		if (m_nCurSelected == i)
		{
			COLORREF clrBkgnd = RGBA(255, 255, 255, 255);
			CAutoRefPtr<IBrush> brush, oldbrush;
			pRT->CreateSolidColorBrush(clrBkgnd, &brush);
			pRT->SelectObject(brush, (IRenderObj**)&oldbrush);
			pRT->FillEllipse(&rcDot);
			pRT->SelectObject(oldbrush, NULL);
		}
		else
		{
			CAutoRefPtr<IPen> pen, oldpen;
			COLORREF clrBorder = RGBA(255, 255, 255, 180);
			pRT->CreatePen(PS_SOLID | PS_ENDCAP_SQUARE, clrBorder, 2, &pen);
			pRT->SelectObject(pen, (IRenderObj**)&oldpen);
			pRT->DrawEllipse(rcDot);
			pRT->SelectObject(oldpen, NULL);
		}
	}
}

void CBannerCtrl::OnTimer(UINT_PTR idEvent)
{
	SetMsgHandled(FALSE);
	switch (idEvent)
	{
	case 1:
	{
		if (m_bAdd)
		{
			m_nCurSelected++;
			if (m_nCurSelected >= 2)
			{
				m_bAdd = false;
				m_nCurSelected = 2;
			}
		}
		else
		{
			m_nCurSelected--;
			if (m_nCurSelected <= 0)
			{
				m_bAdd = true;
				m_nCurSelected = 0;
			}
		}
	}
	break;
	default:
		break;
	}

	Invalidate();
}

void CBannerCtrl::SetBannerImage(SStringW& sstrPath)
{
	m_pBitmap = SResLoadFromFile::LoadImage(sstrPath);
}

void CBannerCtrl::StartTimer()
{
	SetTimer(1, 2000);
}

void CBannerCtrl::CalcDot()
{
	//计算操作点
	m_vecDots.clear();
	CRect rcClient = GetClientRect();
	for (int i = 0; i < 3; i++)
	{
		CRect rcDot;
		rcDot.left = rcClient.left + i * 20 + 20;
		rcDot.top = rcClient.bottom - 20;
		rcDot.right = rcDot.left + 8;
		rcDot.bottom = rcDot.top + 8;

		m_vecDots.push_back(rcDot);
	}
}