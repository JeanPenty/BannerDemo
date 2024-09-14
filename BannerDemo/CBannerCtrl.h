#pragma once

#include <vector>
class CBannerCtrl : public SWindow
{
	DEF_SOBJECT(SWindow, L"banner_ctrl")
public:
	CBannerCtrl(void);
	~CBannerCtrl(void);

	void OnMouseHover(WPARAM wParam, SOUI::CPoint ptPos);
	void OnMouseLeave();
	void OnLButtonDown(UINT nFlags, SOUI::CPoint pt);
	void OnMouseMove(UINT nFlags, SOUI::CPoint pt);
	void OnPaint(IRenderTarget* pRT);
	void OnTimer(UINT_PTR idEvent);

protected:
	SOUI_MSG_MAP_BEGIN()
		MSG_WM_PAINT_EX(OnPaint)

		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSELEAVE(OnMouseLeave)

		MSG_WM_TIMER(OnTimer)
		SOUI_MSG_MAP_END()

private:
	SAutoRefPtr<IBitmap> m_pBitmap;

	int		m_nCurSelected;
	bool	m_bAdd;

	std::vector<CRect> m_vecDots;
public:
	void SetBannerImage(SStringW& sstrPath);
	void StartTimer();

	void CalcDot();
};

