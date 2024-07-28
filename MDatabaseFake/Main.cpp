/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MDatabaseFake.h"

int main() {

    // Allocazione sul heap
    MDatabaseFake* mDatabaseFake = new MDatabaseFake();
    mDatabaseFake->MM_Data_Test_Get();

    // Deallocazione della memoria
    delete mDatabaseFake;

    return 0;
}