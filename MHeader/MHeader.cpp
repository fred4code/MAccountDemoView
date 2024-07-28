/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MHeader.h"

MHeader::MHeader(CWnd* pCWndParent, int pTop, int pHeight, const CString& pText)
{
    // Get the parent window width
    CRect cRect_parent;
    pCWndParent->GetClientRect(&cRect_parent);
    int width_parent = cRect_parent.Width();

    // Create the MHeader window
    CreateEx(0, AfxRegisterWndClass(0), _T("MHeader"), WS_CHILD | WS_VISIBLE,
        CRect(0, pTop, width_parent, pTop + pHeight), pCWndParent, 0);

    // Create an MLabel inside the MHeader window
    vm_mLabel = new MLabel(this, "", vm_font_height, 10, 10, width_parent, pHeight, pText);
    // Set some properties
    vm_mLabel->MM_Padding_Background_Color_Set(220, 220, 220);
    vm_mLabel->MM_Background_Color_Set(220, 220, 220);
    vm_mLabel->MM_Padding_Right_Set(10);

}

void MHeader::MM_Destroy()
{
    if (vm_mLabel)
    {
        vm_mLabel->MM_Destroy();
        delete vm_mLabel;
        vm_mLabel = nullptr;
    }
}

MHeader::~MHeader()
{
    MM_Destroy();
}

void MHeader::MM_Resize(int pX, int pY, int pWidth, int pHeight)
{
    CWnd::MoveWindow(pX, pY, pWidth, pHeight, TRUE);

    vm_mLabel->MM_Resize(0, 0, pWidth, pHeight);
}