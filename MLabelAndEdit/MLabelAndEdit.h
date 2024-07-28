/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#ifndef MLABELANDEDIT_H
#define MLABELANDEDIT_H

#include "../MComponent/MComponent.h"
#include "../MLabel/MLabel.h"
#include "../MEdit/MEdit.h"

class MLabelAndEdit : public CWnd, public MComponent
{
public:
    CString mv_name;

    MLabelAndEdit(CWnd* pParentWnd, const CString& pName, int pLeft, int pTop, int pLabelWidth, int pEditWidth, int pHeight, const CString& pLabelText, const CString& pEditText);
    ~MLabelAndEdit();
    void MM_Destroy() override;

    // Methods for MLabel
    void MM_MLabel_Padding_Left_Set(int pPaddingLeft);
    void MM_MLabel_Padding_Right_Set(int pPaddingRight);
    void MM_MLabel_Padding_BackGround_Color_Set(int pRed, int pGreen, int pBlue);
    void MM_MLabel_BackGround_Color_Set(int pRed, int pGreen, int pBlue);

    // Methods for MEdit
    void MM_MEdit_Padding_BackGround_Color_Set(int pRed, int pGreen, int pBlue);
    void MM_MEdit_BackGround_Color_Set(int pRed, int pGreen, int pBlue);
    void MM_MEdit_Text_Set(const CString& pText);
    CString MM_MEdit_Text_Get();

    //Methods for MLabelAndEdit
    void MM_Resize(int pX, int pY, int pWidthLabel, int pWidthEdit, int pHeight);
    
private:
    MLabel* mv_mLabel;
    MEdit* mv_mEdit;
    int mv_font_height = 30;

};

#endif