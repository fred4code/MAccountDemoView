/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#ifndef MHEADER_H
#define MHEADER_H

#include "../MComponent/MComponent.h"
#include "../MLabel/MLabel.h"

class MHeader : public CWnd, public MComponent
{
public:
    MHeader(CWnd* pCWndParent, int pTop, int pHeight, const CString& pText);
    ~MHeader();
    void MM_Destroy() override;

    void MM_Resize(int pX, int y, int pWidth, int pHeight);

private:
    MLabel* vm_mLabel;
    int vm_font_height = 50;

};

#endif