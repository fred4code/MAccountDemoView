/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MEdit.h"

MEdit::MEdit(CWnd* pParentWnd, int pFontHeight, int pLeft, int pTop, int pWidth, int pHeight, const CString& pText)
{

    // Default padding color is set to red for debugging purposes. In this way it is easier to see the padding
    mv_padding_cBrush.CreateSolidBrush(RGB(255, 0, 0));

    // Default background color for a CEdit object
    mv_background_cBrush.CreateSolidBrush(RGB(255, 255, 255));

    CDC* cDC = pParentWnd->GetDC();
    if (cDC)
    {
        mv_cFont.CreateFont(
            pFontHeight,
            0,
            0,
            0,
            FW_NORMAL,
            FALSE,
            FALSE,
            0,
            ANSI_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS,
            _T("Arial"));

        CFont* cFont_old = cDC->SelectObject(&mv_cFont);
        TEXTMETRIC tm;
        cDC->GetTextMetrics(&tm);
        int textHeight = tm.tmHeight + tm.tmExternalLeading;
        int innerHeight = textHeight;

        cDC->SelectObject(cFont_old);
        pParentWnd->ReleaseDC(cDC);

        Create(NULL, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER, CRect(pLeft, pTop, pLeft + pWidth, pTop + pHeight), pParentWnd);
        
        int innerWidth = pWidth;
        int innerX = 0;
        int innerY = (pHeight - innerHeight) / 2;

        mv_cEdit = new CEdit();
        mv_cEdit->Create(WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL , CRect(innerX, innerY, innerX + innerWidth, innerY + innerHeight), this, 1);
        mv_cEdit->SetFont(&mv_cFont);
        mv_cEdit->SetWindowText(pText);
    }
}

void MEdit::MM_Destroy()
{
    if (mv_cEdit)
    {
        mv_cEdit->DestroyWindow();
        delete mv_cEdit;
        mv_cEdit = nullptr;
    }

    DestroyWindow();
}

MEdit::~MEdit()
{
    MM_Destroy();
}

void MEdit::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
    ModifyStyle(0, SS_NOTIFY);
}


int MEdit::MM_Width_Get()
{
    CRect rect;
    GetWindowRect(&rect);
    return rect.Width();
}

void MEdit::MM_Resize(int pLeft, int pTop, int pWidth, int pHeight)
{
    // Resize MEdit
    SetWindowPos(NULL, pLeft, pTop, pWidth, pHeight, SWP_NOZORDER);

    // Resize mv_cEdit
    CRect cRect;
    GetClientRect(&cRect);

    TEXTMETRIC textmetric;
    CDC* cdc = GetDC();
    if (cdc)
    {
        CFont* pOldFont = cdc->SelectObject(&mv_cFont);
        cdc->GetTextMetrics(&textmetric);
        int textHeight = textmetric.tmHeight + textmetric.tmExternalLeading;
        cdc->SelectObject(pOldFont);
        ReleaseDC(cdc);

        int innerX = 0;
        int innerY = (cRect.Height() - textHeight) / 2;
        mv_cEdit->SetWindowPos(NULL, innerX, innerY, cRect.Width(), textHeight, SWP_NOZORDER);
    }
}

void MEdit::MM_Padding_Background_Color_Set(int pRed, int pGreen, int pBlue)
{
    mv_padding_cBrush.DeleteObject();
    mv_padding_cBrush.CreateSolidBrush(RGB(pRed, pGreen, pBlue));
    Invalidate();
}

void MEdit::MM_Background_Color_Set(int pRed, int pGreen, int pBlue)
{
    mv_background_cBrush.DeleteObject();
    mv_background_cBrush.CreateSolidBrush(RGB(pRed, pGreen, pBlue));
    Invalidate();
}

void MEdit::MM_Edit_Text_Set(const CString& pText)
{
    mv_cEdit->SetWindowText(pText);
}

HBRUSH MEdit::CtlColor(CDC* pCDC, UINT pNCtlColor)
{
    if (pNCtlColor == CTLCOLOR_STATIC)
    {
        LOGBRUSH lb;
        mv_padding_cBrush.GetLogBrush(&lb);
        pCDC->SetBkColor(lb.lbColor);
        return (HBRUSH)mv_padding_cBrush.GetSafeHandle();
    }
    return NULL;
}

HBRUSH MEdit::OnCtlColor(CDC* pCDC, CWnd* pCWnd, UINT pNCtlColor)
{
    if (pCWnd->GetSafeHwnd() == mv_cEdit->GetSafeHwnd())
    {
        LOGBRUSH lb;
        mv_background_cBrush.GetLogBrush(&lb);
        pCDC->SetBkColor(lb.lbColor);
        return (HBRUSH)mv_background_cBrush.GetSafeHandle();
    }
    return CStatic::OnCtlColor(pCDC, pCWnd, pNCtlColor);
}

CString MEdit::MM_MEdit_Text_Get()
{
    CString text;
    mv_cEdit->GetWindowText(text);
    return text;
}

BEGIN_MESSAGE_MAP(MEdit, CStatic)
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()