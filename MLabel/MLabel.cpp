/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MLabel.h"

MLabel::MLabel(CWnd* pParentWnd, const CString& pName, int pFontHeight, int pLeft, int pTop, int pWidth, int pHeight, const CString& pText)
{
    // set the optional name for the MLabel (if setted it can be used in the OnLButtonUp to identify the MLabel in the parent)
    mv_name = pName;

    // Padding
    mv_padding_left = 0;
    mv_padding_right = 0;

    // Default padding color is set to red for debugging purposes. In this way, it is easier to see the padding
    mv_padding_cBrush.CreateSolidBrush(RGB(255, 0, 0));

    // Default background color for a CStatic object
    mv_background_cBrush.CreateSolidBrush(RGB(240, 240, 240));

    CDC* cDC = pParentWnd->GetDC();
    if (cDC)
    {
        mv_cFont.CreateFont(
            pFontHeight,
            0,
            0,
            0,
            FW_BOLD,
            FALSE,
            FALSE,
            0,
            ANSI_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS,
            _T("Arial"));

        CFont* pOldFont = cDC->SelectObject(&mv_cFont);
        TEXTMETRIC tm;
        cDC->GetTextMetrics(&tm);
        int textHeight = tm.tmHeight + tm.tmExternalLeading;
        int innerHeight = textHeight;

        cDC->SelectObject(pOldFont);
        pParentWnd->ReleaseDC(cDC);

        Create(NULL, WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER, CRect(pLeft, pTop, pLeft + pWidth, pTop + pHeight), pParentWnd);

        int innerWidth = pWidth - mv_padding_left - mv_padding_right;
        int innerX = mv_padding_left;
        int innerY = (pHeight - innerHeight) / 2;

        mv_cStatic_inner = new CStatic();
        mv_cStatic_inner->Create(pText, WS_CHILD | WS_VISIBLE | SS_RIGHT, CRect(innerX, innerY, innerX + innerWidth, innerY + innerHeight), this);
        mv_cStatic_inner->SetFont(&mv_cFont);

    }
}

void MLabel::MM_Destroy()
{
    // Destroy the inner static control
    if (mv_cStatic_inner)
    {
        mv_cStatic_inner->DestroyWindow();
        delete mv_cStatic_inner;
        mv_cStatic_inner = nullptr;
    }

    // Destroy the MLabel window
    DestroyWindow();
}

MLabel::~MLabel()
{
    MM_Destroy();
}

int MLabel::MM_Width_Get()
{
    CRect cRect;
    GetWindowRect(&cRect);
    return cRect.Width();
}

void MLabel::MM_Resize(int pLeft, int pTop, int pWidth, int pHeight)
{
    // Resize MLabel
    SetWindowPos(NULL, pLeft, pTop, pWidth, pHeight, SWP_NOZORDER);

    // Resize inner static control
    CRect cRect;
    GetClientRect(&cRect);

    TEXTMETRIC tm;
    CDC* cDC = GetDC();
    if (cDC)
    {
        CFont* pOldFont = cDC->SelectObject(&mv_cFont);
        cDC->GetTextMetrics(&tm);
        int textHeight = tm.tmHeight + tm.tmExternalLeading;
        cDC->SelectObject(pOldFont);
        ReleaseDC(cDC);

        int x = mv_padding_left;
        int y = (cRect.Height() - textHeight) / 2;
        int width = cRect.Width() - mv_padding_left - mv_padding_right;
        mv_cStatic_inner->SetWindowPos(NULL, x, y, width, textHeight, SWP_NOZORDER);
    }
}

void MLabel::MM_Padding_Left_Set(int pPaddingLeft)
{
    mv_padding_left = pPaddingLeft;
    // Update the position of the inner static control
    CRect cRect;
    GetClientRect(&cRect);
    MM_Resize(cRect.left, cRect.top, cRect.Width(), cRect.Height());
}

void MLabel::MM_Padding_Right_Set(int pPaddingRight)
{
    mv_padding_right = pPaddingRight;
    CRect cRect;
    GetClientRect(&cRect);
    MM_Resize(cRect.left, cRect.top, cRect.Width(), cRect.Height());
}

void MLabel::MM_Text_Align_Set(UINT pTextAlign)
{
    // Remove current style
    mv_cStatic_inner->ModifyStyle(SS_LEFT | SS_CENTER | SS_RIGHT, 0);

    // Add the new style
    mv_cStatic_inner->ModifyStyle(0, pTextAlign);

    // Repaint the MLabel
    mv_cStatic_inner->Invalidate();
}

void MLabel::PreSubclassWindow()
{
    // Perform subclassing operations
    CStatic::PreSubclassWindow();
    // Add SS_NOTIFY style to receive notifications such as mouse clicks
    ModifyStyle(0, SS_NOTIFY);
}


void MLabel::MM_Padding_Background_Color_Set(int pRed, int pGreen, int pBlue)
{
    // Delete the old brush to free the memory
    mv_padding_cBrush.DeleteObject();
    // Create a new brush with the specified color
    mv_padding_cBrush.CreateSolidBrush(RGB(pRed, pGreen, pBlue));
    // Force the control to redraw to apply the new color
    Invalidate();
}

void MLabel::MM_Background_Color_Set(int pRed, int pGreen, int pBlue)
{
    mv_background_cBrush.DeleteObject();
    mv_background_cBrush.CreateSolidBrush(RGB(pRed, pGreen, pBlue));
    Invalidate();
}

void MLabel::MM_Text_Set(const CString& pText)
{
    mv_cStatic_inner->SetWindowText(pText);
}

// Message Handlers
HBRUSH MLabel::CtlColor(CDC* pCDC, UINT pNCtlColor)
{

    LOGBRUSH lb;
    // Get the brush details
    mv_padding_cBrush.GetLogBrush(&lb);
    // Set the background color from the brush
    pCDC->SetBkColor(lb.lbColor);
    return (HBRUSH)mv_padding_cBrush.GetSafeHandle();

    return NULL;
}

HBRUSH MLabel::OnCtlColor(CDC* pCDC, CWnd* pCWnd, UINT pNCtlColor)
{
    // The message handler is processed only if it is for mv_cStatic_inner
    if (pCWnd->GetSafeHwnd() == mv_cStatic_inner->GetSafeHwnd())
    {
        LOGBRUSH lb;
        mv_background_cBrush.GetLogBrush(&lb);
        pCDC->SetBkColor(lb.lbColor);
        return (HBRUSH)mv_background_cBrush.GetSafeHandle();
    }
    return CStatic::OnCtlColor(pCDC, pCWnd, pNCtlColor);
}

void MLabel::OnLButtonUp(UINT pNFlags, CPoint pCPoint)
{
    MMessage* mMessage = new MMessage{ mv_name };

    GetParent()->SendMessage(WM_MMessage, 0, reinterpret_cast<LPARAM>(mMessage));

    CStatic::OnLButtonUp(pNFlags, pCPoint);
}

BEGIN_MESSAGE_MAP(MLabel, CStatic)
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_CTLCOLOR()
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()
