/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#ifndef MEDIT_H
#define MEDIT_H

#include "../MComponent/MComponent.h"

class MEdit : public CStatic, public MComponent
{
public:
    MEdit(CWnd* pParentWnd, int pFontHeight, int pLeft, int pTop, int pWidth, int pHeight, const CString& pText);
    ~MEdit();
    void MM_Destroy() override;

    int MM_Width_Get();
    void MM_Resize(int pLeft, int pTop, int pWidth, int pHeight);
    void MM_Padding_Background_Color_Set(int pRed, int pGreen, int pBlue);
    void MM_Background_Color_Set(int pRed, int pGreen, int pBlue);
    void MM_Edit_Text_Set(const CString& pText);
    CString MM_MEdit_Text_Get();

protected:
    virtual void PreSubclassWindow();

    // Message Handlers

    afx_msg HBRUSH CtlColor(CDC* pCDC, UINT pNCtlColor);
    afx_msg HBRUSH OnCtlColor(CDC* pCDC, CWnd* pCWnd, UINT pNCtlColor);

    DECLARE_MESSAGE_MAP()

private:
    CBrush mv_padding_cBrush;
    CBrush mv_background_cBrush;
    CEdit* mv_cEdit;
    CFont mv_cFont;

};

#endif