/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MAccount.h"

#include "../MDatabaseFake/MDatabaseFake.h"
#include "../MComponent/MComponent.h"
#include "../MLabel/MLabel.h"
#include "../MEdit/MEdit.h"
#include "../MHeader/MHeader.h"
#include "../MLabelAndEdit/MLabelAndEdit.h"

class MApp : public CWinApp
{
public:
    virtual BOOL InitInstance()
    {
        MAccount* mAccount = new MAccount();
        m_pMainWnd = mAccount;
        mAccount->ShowWindow(SW_NORMAL);
        mAccount->UpdateWindow();
        return TRUE;
    }
};

MApp mApp;