/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#ifndef MCOMPONENT_H
#define MCOMPONENT_H 

#include <afxwin.h>

// Abstract basse class to derive all the other MComponent from
class MComponent
{
public:
    virtual ~MComponent() {}
    // Pure virtual method
    virtual void MM_Destroy() = 0;
};

#endif