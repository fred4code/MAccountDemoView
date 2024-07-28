/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MEdit.h"

class MFrame : public CFrameWnd
{
public:
    MEdit* m_mEdit;

    MFrame()
    {
        Create(NULL, _T("MEdit"));
        m_mEdit = new MEdit(this, 20, 0, 0, 300, 200, "MEdit");
    }

    ~MFrame()
    {
        if (m_mEdit)
        {
            delete m_mEdit;
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