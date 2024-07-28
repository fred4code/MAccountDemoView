/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MLabelAndEdit.h"

MLabelAndEdit::MLabelAndEdit(CWnd* pParentWnd, const CString& pName, int pLeft, int pTop, int pLabelWidth, int pEditWidth, int pHeight, const CString& pLabelText, const CString& pEditText)
{
    mv_name = pName;

    // Total height and size of MLabelAndEdit
    int width_total = pLabelWidth + pEditWidth; 
    int height_total = pHeight;

    // Create the MLabelAndEdit window
    CreateEx(0, AfxRegisterWndClass(0), _T("MLabelAndEdit"), WS_CHILD | WS_VISIBLE,
        CRect(pLeft, pTop, pLeft + width_total, pTop + height_total), pParentWnd, 0);

    // Create the MLabel and MEdit of wich mlabelAndEdit is composed
    mv_mLabel = new MLabel(this, "", mv_font_height, 0, 0, pLabelWidth, pHeight, pLabelText);
    mv_mEdit = new MEdit(this, mv_font_height, pLabelWidth, 0, pEditWidth, pHeight, pEditText);
}

MLabelAndEdit::~MLabelAndEdit()
{
    MM_Destroy();
}

void MLabelAndEdit::MM_Destroy()
{
    if (mv_mLabel)
    {
        mv_mLabel->MM_Destroy();
        delete mv_mLabel;
        mv_mLabel = nullptr;
    }

    if (mv_mEdit)
    {
        mv_mEdit->MM_Destroy();
        delete mv_mEdit;
        mv_mEdit = nullptr;
    }

    DestroyWindow();
}

void MLabelAndEdit::MM_MLabel_Padding_Left_Set(int pPaddingLeft)
{
    mv_mLabel->MM_Padding_Left_Set(pPaddingLeft);
}

void MLabelAndEdit::MM_MLabel_Padding_Right_Set(int pPaddingRight)
{
    mv_mLabel->MM_Padding_Right_Set(pPaddingRight);
}

void MLabelAndEdit::MM_MLabel_Padding_BackGround_Color_Set(int pRed, int pGreen, int pBlue)
{
    mv_mLabel->MM_Padding_Background_Color_Set(pRed, pGreen, pBlue);
}

void MLabelAndEdit::MM_MLabel_BackGround_Color_Set(int pRed, int pGreen, int pBlue)
{
    mv_mLabel->MM_Background_Color_Set(pRed, pGreen, pBlue);
}

void MLabelAndEdit::MM_MEdit_Padding_BackGround_Color_Set(int pRed, int pGreen, int pBlue)
{
    mv_mEdit->MM_Padding_Background_Color_Set(pRed, pGreen, pBlue);
}

void MLabelAndEdit::MM_MEdit_BackGround_Color_Set(int pRed, int pGreen, int pBlue)
{
    mv_mEdit->MM_Background_Color_Set(pRed, pGreen, pBlue);
}

void MLabelAndEdit::MM_Resize(int pX, int pY, int pWidthLabel, int pWidthEdit, int pHeight)
{
    int width_total = pWidthLabel + pWidthEdit;

    // calculate the new dimensions for MLabel and MEdit
    pWidthLabel = mv_mLabel->MM_Width_Get();
    pWidthEdit = width_total - pWidthLabel;

    // MLabelAndEdit resizing
    CWnd::MoveWindow(pX, pY, width_total, pHeight, TRUE);
    if (mv_mLabel != nullptr)
    {
        mv_mLabel->MM_Resize(0, 0, pWidthLabel, pHeight);
    }
    if (mv_mEdit != nullptr)
    {
        mv_mEdit->MM_Resize(pWidthLabel, 0, pWidthEdit, pHeight);
    }
}

void MLabelAndEdit::MM_MEdit_Text_Set(const CString& pText)
{
    mv_mEdit->MM_Edit_Text_Set(pText);
}

CString MLabelAndEdit::MM_MEdit_Text_Get()
{
    CString text;
    text = mv_mEdit->MM_MEdit_Text_Get();
    return text;
}