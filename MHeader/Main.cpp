/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MHeader.h"

class MFrame : public CFrameWnd
{
public:
    MHeader* mv_mHeader;

    MFrame()
    {
        Create(NULL, _T("MHeader"));
        mv_mHeader = new MHeader(this, 10, 50, "MHeader");
    }

    ~MFrame()
    {
        if (mv_mHeader)
        {
            mv_mHeader->MM_Destroy();
            delete mv_mHeader;
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