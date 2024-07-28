/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#ifndef MLABEL_H //If MLABEL_H is not defined...
#define MLABEL_H //...define it. This prevents the header file from being included multiple times in a single compilation unit, which can cause errors due to redefinition of classes and functions.

#include "../MComponent/MComponent.h"

// Custom message (wPrm) used to send events to the parent window
#define WM_MMessage (WM_USER + 1) 
// Custom message (lParam) used to send events to the parent window
struct MMessage {
    CString mv_mComponent_name;
};

class MLabel : public CStatic, public MComponent
{
public:
    MLabel(CWnd* pParentWnd, const CString& pName, int pFontHeight, int pLeft, int pTop, int pWidth, int pHeight, const CString& pText);
    virtual ~MLabel();
    // Override garantees that we are overriding the MM_Destroy in the base abstract class MLabel derives from
    void MM_Destroy() override;

    int MM_Width_Get();
    void MM_Resize(int pLeft, int pTop, int pWidth, int pHeight);
    void MM_Padding_Left_Set(int pPaddingLeft);
    void MM_Padding_Right_Set(int pPaddingRight);
    void MM_Padding_Background_Color_Set(int pRed, int pGreen, int pBlue);
    void MM_Background_Color_Set(int pRed, int pGreen, int pBlue);
    void MM_Text_Align_Set(UINT pTextAlign);
    void MM_Text_Set(const CString& pText);


protected:
    virtual void PreSubclassWindow();

    // Message Handlers
    // Message handler called for the control when it needs a background color
    afx_msg HBRUSH CtlColor(CDC* pCDC, UINT pNCtlColor);
    // Message handler called for every child control that needs background color
    afx_msg HBRUSH OnCtlColor(CDC* pCDC, CWnd* pCWnd, UINT pNCtlColor);
    // Message handler called on the mouse up click on the MLabel
    afx_msg void OnLButtonUp(UINT pNFlags, CPoint pCPoint);

    DECLARE_MESSAGE_MAP()

private:
    
    // name of the MLabel (optional)
    CString mv_name = "";
    // brush to set the color of the padding area
    CBrush mv_padding_cBrush;
    // brush to set the color of the background
    CBrush mv_background_cBrush;
    // font of the mv_cStatic_inner text
    CFont mv_cFont;
    // cstatic control that contains the text
    CStatic* mv_cStatic_inner;

    // Padding
    int mv_padding_left;
    int mv_padding_right;

};

#endif 