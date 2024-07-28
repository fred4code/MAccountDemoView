/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MAccount.h"

MAccount::MAccount()
{
    mv_mRow_counter = 0;

    // Fake database to contains some data
    mv_mDatabaseFake = new MDatabaseFake();
    mv_mComponents.push_back(mv_mDatabaseFake);

    // Get the Account with id 0
    MRow mRow = mv_mDatabaseFake->MM_Row_Get("Account", mv_mRow_counter);

    // Create the main window with the title "Account"
    Create(NULL, _T("Account"), WS_OVERLAPPEDWINDOW, CRect(0, 0, 1920, 1080));

    // Create and initialize the MHeader
    mv_mHeader = new MHeader(this, 0, 50, "Account");
    mv_mComponents.push_back(mv_mHeader);

    // Create and initialize the navigation MLabels
    mv_mLabel_back = new MLabel(this, "mv_mLabel_back", 50, 0, 50 + 20, 50, 50, _T("<"));
    mv_mLabel_back->MM_Text_Align_Set(SS_CENTER);
    mv_mLabel_back->MM_Background_Color_Set(220, 220, 220);
    mv_mComponents.push_back(mv_mLabel_back);
    
    mv_mLabel_forward = new MLabel(this, "mv_mLabel_forward", 50, 50 + 10, 50 + 20, 50, 50, _T(">"));
    mv_mLabel_forward->MM_Text_Align_Set(SS_CENTER);
    mv_mLabel_forward->MM_Background_Color_Set(220, 220, 220);
    mv_mComponents.push_back(mv_mLabel_forward);
    
    CString mRow_id;
    mRow_id.Format(_T("%d"), mv_mRow_counter);
    mv_mLabel_mrow_id = new MLabel(this, "mv_mLabel_forward", 50, 50 + 10 + 50 + 10, 50 + 20, 150, 50, mRow_id);
    mv_mLabel_mrow_id->MM_Text_Align_Set(SS_CENTER);
    mv_mLabel_mrow_id->MM_Background_Color_Set(220, 220, 220);
    mv_mComponents.push_back(mv_mLabel_mrow_id);

    // Initialize the layout parameters
    // first top coordinate to place the first MLabelAndEdit
    mv_top_first = 50 + 50 + 20 + 20;
    // height of MLabelAndEdit
    mv_height = 50;
    // space between each MLabelAndEdit
    mv_spacing = 10;

    // Create empty MLabelAndEdit objects
    MM_Fields_Set(mRow, mv_mDatabaseFake);

    // Populate the MLabelAndEdit objects
    MM_Fields_Values_Set(mRow);
}

void MAccount::MM_Destroy()
{
    for (MComponent* mComponent : mv_mComponents) {
        mComponent->MM_Destroy();
        delete mComponent;
        mComponent = nullptr;
    }
}

MAccount::~MAccount()
{
    MM_Destroy();
}

void MAccount::MM_Fields_Set(const MRow& pMRow, MDatabaseFake* pMDatabaseFake)
{
    CRect cRect;
    GetClientRect(&cRect);
    int windowWidth = cRect.Width();

    // Loop the fields in pMRow
    for (std::map<std::string, std::string>::const_iterator field = pMRow.fields.begin(); field != pMRow.fields.end(); ++field)
    {
        CString mLabel_text(field->first.c_str());
        mLabel_text += L":";
        CString mEdit_text(field->second.c_str());
        CString field_name(field->first.c_str());

        // Get the field position
        MFieldProperty mFieldProperty = pMDatabaseFake->Get_Field_Position("Account", field->first);
        mv_fields_properties[field->first] = mFieldProperty; // Memorizza la posizione del campo

        // Calculate column width
        int width_column = windowWidth / mFieldProperty.columns; // Larghezza di ciascuna colonna
        int left = (mFieldProperty.col - 1) * width_column;
        int top = mv_top_first + (mFieldProperty.row - 1) * (mv_height + mv_spacing); // Spazio dal top più altezza riga

        int mLabel_width = (mFieldProperty.mLabel_width_percent * width_column) / 100;
        int mEdit_width = (mFieldProperty.mEdit_width_percent * width_column) / 100;

        // Create MLabelAndEdit
        MLabelAndEdit* mLabelAndEdit = new MLabelAndEdit(this, field_name, left, top, mLabel_width, mEdit_width, mv_height, mLabel_text, "");

        // Set MLabel properties
        mLabelAndEdit->MM_MLabel_Padding_BackGround_Color_Set(220, 220, 220);
        mLabelAndEdit->MM_MLabel_BackGround_Color_Set(220, 220, 220);
        mLabelAndEdit->MM_MLabel_Padding_Left_Set(10);
        mLabelAndEdit->MM_MLabel_Padding_Right_Set(5);
        
        // Set MEdit properties
        mLabelAndEdit->MM_MEdit_Padding_BackGround_Color_Set(255, 255, 255);
        mLabelAndEdit->MM_MEdit_BackGround_Color_Set(255, 255, 255);

        // Add the created control to the vector
        mv_mComponents.push_back(mLabelAndEdit);
    }
}

void MAccount::MM_Fields_Values_Set(const MRow& pMRow)
{
    for (size_t i = 0; i < mv_mComponents.size(); ++i)
    {
        MComponent* mComponent = mv_mComponents[i];
        if (mComponent != nullptr)
        {
            MLabelAndEdit* mLabelAndEdit = dynamic_cast<MLabelAndEdit*>(mComponent);
            if (mLabelAndEdit != nullptr)
            {
                CString field_name = mLabelAndEdit->mv_name;
                std::string field_name_string = std::string(CT2A(field_name));

                if (pMRow.fields.find(field_name_string) != pMRow.fields.end())
                {
                    CString edit_text(pMRow.fields.at(field_name_string).c_str());
                    mLabelAndEdit->MM_MEdit_Text_Set(edit_text);
                }
            }
        }
    }
}

void MAccount::OnSize(UINT pNType, int pCx, int pCy)
{
    CFrameWnd::OnSize(pNType, pCx, pCy);

    // MHeader - resizing
    if (mv_mHeader != nullptr)
    {
        mv_mHeader->MM_Resize(0, 0, pCx, 50);
    }

    // MLabelAndEdit resizing
    for (size_t i = 0; i < mv_mComponents.size(); ++i)
    {
        MComponent* mComponent = mv_mComponents[i];
        if (mComponent != nullptr)
        {
            MLabelAndEdit* mLabelAndEdit = dynamic_cast<MLabelAndEdit*>(mComponent);
            if (mLabelAndEdit != nullptr)
            {
                // Ottieni il nome del campo associato al controllo
                CString field_name = mLabelAndEdit->mv_name;

                // Ottieni la posizione del campo dal vettore fieldPositions
                MFieldProperty mFieldProperty = mv_fields_properties[std::string(CT2A(field_name))];

                // Left, Top coordinates
                int column_width = pCx / mFieldProperty.columns;
                int left = (mFieldProperty.col - 1) * column_width;
                int top = mv_top_first + (mFieldProperty.row - 1) * (mv_height + mv_spacing);

                // MLabel and MEdit coordinates
                int mLabel_width = (mFieldProperty.mLabel_width_percent * column_width) / 100;
                int mEdit_width = (mFieldProperty.mEdit_width_percent * column_width) / 100;

                mLabelAndEdit->MM_Resize(left, top, mLabel_width, mEdit_width, mv_height);
            }
        }
    }
}

void MAccount::MM_Save(MDatabaseFake* pMDatabaseFake)
{
    MRow mRow;
    for (size_t i = 0; i < mv_mComponents.size(); ++i)
    {
        MComponent* mComponent = mv_mComponents[i];
        if (mComponent != nullptr)
        {
            MLabelAndEdit* mLabelAndEdit = dynamic_cast<MLabelAndEdit*>(mComponent);
            if (mLabelAndEdit != nullptr)
            {
                CString field_name = mLabelAndEdit->mv_name;
                CString field_value = mLabelAndEdit->MM_MEdit_Text_Get();
                mRow.fields[std::string(CT2A(field_name))] = std::string(CT2A(field_value));
            }
        }
    }
    pMDatabaseFake->MM_Row_Set("Account", mv_mRow_counter, mRow);
}

LRESULT MAccount::MM_MLabel_OnLButtonUp(WPARAM pWParam, LPARAM pLParam)
{
    MMessage* mMessage = reinterpret_cast<MMessage*>(pLParam);
    if (mMessage)
    {
        if (mMessage->mv_mComponent_name == _T("mv_mLabel_forward"))
        {
            MM_Save(mv_mDatabaseFake);

            mv_mRow_counter++;
            MRow mRow_1 = mv_mDatabaseFake->MM_Row_Get("Account", mv_mRow_counter);
            if (mRow_1.mv_valid == true)
            {
                MM_Fields_Values_Set(mRow_1);
            }
            else
            {
                mv_mRow_counter = mv_mDatabaseFake->MM_MRow_Empty_Set("Account");
                MRow newRow = mv_mDatabaseFake->MM_Row_Get("Account", mv_mRow_counter);
                MM_Fields_Values_Set(newRow);
            }

        }
        else if (mMessage->mv_mComponent_name == _T("mv_mLabel_back"))
        {
            MM_Save(mv_mDatabaseFake);

            mv_mRow_counter--;
            MRow mRow_1 = mv_mDatabaseFake->MM_Row_Get("Account", mv_mRow_counter);
            if (mRow_1.mv_valid == true)
            {
                MM_Fields_Values_Set(mRow_1);
            }
            else
            {
                mv_mRow_counter++;
            }
        }

        CString mRow_id;
        mRow_id.Format(_T("%d"), mv_mRow_counter);
        mv_mLabel_mrow_id->MM_Text_Set(mRow_id);

        delete mMessage;
    }

    return 0;
}

BEGIN_MESSAGE_MAP(MAccount, CFrameWnd)
    ON_WM_SIZE()
    ON_MESSAGE(WM_MMessage, &MAccount::MM_MLabel_OnLButtonUp)
END_MESSAGE_MAP()