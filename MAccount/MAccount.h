/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#ifndef MACCOUNT_H
#define MACCOUNT_H

#include <vector>
#include <map>
#include <string>

#include "../MComponent/MComponent.h"
#include "../MHeader/MHeader.h"
#include "../MLabelAndEdit/MLabelAndEdit.h"
#include "../MDatabaseFake/MDatabaseFake.h"

class MAccount : public CFrameWnd, public MComponent
{
public:
    MAccount();
    ~MAccount();
    void MM_Destroy() override;

    // Height for the MLabelAndEdit
    int mv_height;
    // Space between each MLabelAndEdit
    int mv_spacing;
    // First top coordinate to place the first MLabelAndEdit
    int mv_top_first;

    // Sets the fields of MLabelAndEdit based on the provided mRow and MDatabaseFake
    void MM_Fields_Set(const MRow& pMRow, MDatabaseFake* pMDatabaseFake);
    // Sets the values of the fields in MLabelAndEdit based on the provided mRow
    void MM_Fields_Values_Set(const MRow& pMRow);
    // Save the data in the fake database
    void MM_Save(MDatabaseFake* pMDatabaseFake);

protected:
    // Message Handlers
    // Message Handler received when MAccount window is resized
    afx_msg void OnSize(UINT pNType, int pCx, int pCy);

    // Message Handlers custom
    // Message Handler custom received when the MLabel mv_mLabel_back, mv_mLabel_forward, mv_mLabel_mrow_id are mouse up clicked
    afx_msg LRESULT MM_MLabel_OnLButtonUp(WPARAM pWParam, LPARAM pLParam);

    DECLARE_MESSAGE_MAP()

private:
    // Data
    MDatabaseFake* mv_mDatabaseFake;

    // Navigation MLabels
    MLabel* mv_mLabel_back;
    MLabel* mv_mLabel_forward;
    MLabel* mv_mLabel_mrow_id;
    int mv_mRow_counter;

    // Fields
    MHeader* mv_mHeader;
    // Vector to contain the pointers of all the MComponent. It is used to access the MComponent and release the memory used for them
    std::vector<MComponent*> mv_mComponents;
    // Map to contain fields properties
    std::map<std::string, MFieldProperty> mv_fields_properties;

};

#endif