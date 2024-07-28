/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MLabelAndEdit.h"

class MFrame : public CFrameWnd
{
public:
    MLabelAndEdit* mv_mLabelAndEdit;

    MFrame()
    {
        Create(NULL, _T("MLabelAndEdit"));
        mv_mLabelAndEdit = new MLabelAndEdit(this, "", 0, 0, 200, 300, 50, "MLabel", "MEdit");
    }

    ~MFrame()
    {
        if (mv_mLabelAndEdit)
        {
            mv_mLabelAndEdit->MM_Destroy();
        }
    }
};

class MApp : public CWinApp
{
public:
    virtual BOOL InitInstance()
    {
        MFrame* mFrame = new MFrame();
        m_pMainWnd = mFrame;
        mFrame->ShowWindow(SW_NORMAL);
        mFrame->UpdateWindow();
        return TRUE;
    }
};

MApp mApp;