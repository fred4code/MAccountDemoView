/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MComponent.h"

class MComponentTest : public MComponent
{
public:
    MComponentTest() {}
    virtual ~MComponentTest() {}

    void MM_Destroy() override { delete this; }
};

class MApp : public CWinApp
{
public:
    virtual BOOL InitInstance()
    {
        MComponent* mComponent = new MComponentTest();
        mComponent->MM_Destroy();
        return TRUE;
    }
};

MApp mApp;