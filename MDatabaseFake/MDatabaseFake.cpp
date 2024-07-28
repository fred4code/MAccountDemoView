/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#include "MDatabaseFake.h"

#include <iostream>

MDatabaseFake::MDatabaseFake() {
    // Initialize field positions for the "Account" table
    mv_mFieldProperties["Account"]["FirstName"] = { 1, 1, 2, 30, 70 };
    mv_mFieldProperties["Account"]["LastName"] = { 1, 2, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Email"] = { 2, 1, 2, 30, 70 };
    mv_mFieldProperties["Account"]["PhoneNumber"] = { 2, 2, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Address"] = { 3, 1, 2, 30, 70 };
    mv_mFieldProperties["Account"]["City"] = { 3, 2, 2, 30, 70 };
    mv_mFieldProperties["Account"]["State"] = { 4, 1, 2, 30, 70 };
    mv_mFieldProperties["Account"]["ZipCode"] = { 4, 2, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Country"] = { 5, 1, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Birthdate"] = { 5, 2, 2, 30, 70 };
    mv_mFieldProperties["Account"]["AccountBalance"] = { 6, 1, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Gender"] = { 6, 2, 2, 30, 70 };
    mv_mFieldProperties["Account"]["MaritalStatus"] = { 7, 1, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Occupation"] = { 7, 2, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Company"] = { 8, 1, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Nationality"] = { 8, 2, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Language"] = { 9, 1, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Education"] = { 9, 2, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Income"] = { 10, 1, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Hobbies"] = { 10, 2, 2, 30, 70 };
    mv_mFieldProperties["Account"]["Membership"] = { 11, 1, 2, 30, 70 };

    // Add some records to the "Account" table
    MRow mRaw_account_1;
    mRaw_account_1.fields["FirstName"] = "Mario";
    mRaw_account_1.fields["LastName"] = "Rossi";
    mRaw_account_1.fields["Email"] = "mario.rossi@example.com";
    mRaw_account_1.fields["PhoneNumber"] = "123-456-7890";
    mRaw_account_1.fields["Address"] = "123 Main St";
    mRaw_account_1.fields["City"] = "Rome";
    mRaw_account_1.fields["State"] = "RM";
    mRaw_account_1.fields["ZipCode"] = "00100";
    mRaw_account_1.fields["Country"] = "Italy";
    mRaw_account_1.fields["Birthdate"] = "1980-01-01";
    mRaw_account_1.fields["AccountBalance"] = "5000";
    mRaw_account_1.fields["Gender"] = "Male";
    mRaw_account_1.fields["MaritalStatus"] = "Single";
    mRaw_account_1.fields["Occupation"] = "Engineer";
    mRaw_account_1.fields["Company"] = "TechCorp";
    mRaw_account_1.fields["Nationality"] = "Italian";
    mRaw_account_1.fields["Language"] = "Italian";
    mRaw_account_1.fields["Education"] = "Master's Degree";
    mRaw_account_1.fields["Income"] = "70000";
    mRaw_account_1.fields["Hobbies"] = "Reading, Travelling";
    mRaw_account_1.fields["Membership"] = "Library";
    int id1 = MM_Row_Create("Account", mRaw_account_1);

    MRow mRaw_account_2;
    mRaw_account_2.fields["FirstName"] = "Luigi";
    mRaw_account_2.fields["LastName"] = "Verdi";
    mRaw_account_2.fields["Email"] = "luigi.verdi@example.com";
    mRaw_account_2.fields["PhoneNumber"] = "987-654-3210";
    mRaw_account_2.fields["Address"] = "456 Side St";
    mRaw_account_2.fields["City"] = "Milan";
    mRaw_account_2.fields["State"] = "MI";
    mRaw_account_2.fields["ZipCode"] = "20100";
    mRaw_account_2.fields["Country"] = "Italy";
    mRaw_account_2.fields["Birthdate"] = "1985-02-02";
    mRaw_account_2.fields["AccountBalance"] = "3000";
    mRaw_account_2.fields["Gender"] = "Male";
    mRaw_account_2.fields["MaritalStatus"] = "Married";
    mRaw_account_2.fields["Occupation"] = "Designer";
    mRaw_account_2.fields["Company"] = "DesignStudio";
    mRaw_account_2.fields["Nationality"] = "Italian";
    mRaw_account_2.fields["Language"] = "Italian";
    mRaw_account_2.fields["Education"] = "Bachelor's Degree";
    mRaw_account_2.fields["Income"] = "50000";
    mRaw_account_2.fields["Hobbies"] = "Painting, Running";
    mRaw_account_2.fields["Membership"] = "Gym";
    int id2 = MM_Row_Create("Account", mRaw_account_2);
}

void MDatabaseFake::MM_Destroy() {
    mv_tables.clear();
    mv_ids_next.clear();
    mv_mFieldProperties.clear();
}

MDatabaseFake::~MDatabaseFake() {
    MM_Destroy();
}

int MDatabaseFake::MM_Row_Create(const std::string& pTableName, const MRow& pMRow) {
    int id = mv_ids_next[pTableName]++;
    mv_tables[pTableName][id] = pMRow;
    return id;
}

bool MDatabaseFake::MM_Row_Delete(const std::string& pTableName, int pId) {
    return mv_tables[pTableName].erase(pId) > 0;
}

MRow MDatabaseFake::MM_Row_Get(const std::string& pTableName, int pId) {

    MRow mRow;
    if (mv_tables[pTableName].find(pId) != mv_tables[pTableName].end()) {
        mRow = mv_tables[pTableName][pId];
        mRow.mv_valid = true;
    }
    else {
        mRow.mv_valid = false;
    }
    return mRow;
}

std::string MDatabaseFake::MM_Row_Read(const std::string& pTableName, int pId) {
    try {
        MRow record = MM_Row_Get(pTableName, pId);
        std::string result;
        for (std::map<std::string, std::string>::iterator field = record.fields.begin(); field != record.fields.end(); ++field) {
            result += field->first + ": " + field->second + "\n";
        }
        return result;
    }
    catch (const std::runtime_error& e) {
        return e.what();
    }
}

void MDatabaseFake::MM_Table_Read(const std::string& pTableName) {
    if (mv_tables.find(pTableName) != mv_tables.end()) {
        for (std::map<int, MRow>::iterator record = mv_tables[pTableName].begin(); record != mv_tables[pTableName].end(); ++record) {
            std::cout << "ID: " << record->first << std::endl;
            for (std::map<std::string, std::string>::iterator field = record->second.fields.begin(); field != record->second.fields.end(); ++field) {
                std::cout << "  " << field->first << ": " << field->second << std::endl;
            }
        }
    }
    else {
        std::cout << "Table not found!" << std::endl;
    }
}

MFieldProperty MDatabaseFake::Get_Field_Position(const std::string& pTableName, const std::string& pFieldName) {
    if (mv_mFieldProperties.find(pTableName) != mv_mFieldProperties.end() &&
        mv_mFieldProperties[pTableName].find(pFieldName) != mv_mFieldProperties[pTableName].end()) {
        return mv_mFieldProperties[pTableName][pFieldName];
    }
    else {
        throw std::runtime_error("Field position not found!");
    }
}

void MDatabaseFake::Create_Label(CWnd* pParentWnd, const std::string& pTableName, const std::string& pFieldName) {
    MFieldProperty pos = Get_Field_Position(pTableName, pFieldName);
    CRect parentRect;
    pParentWnd->GetClientRect(&parentRect);

    int totalCols = pos.col;
    int colWidth = parentRect.Width() / totalCols;
    int rowHeight = 50;

    int left = (pos.col - 1) * colWidth;
    int top = (pos.row - 1) * rowHeight;
    int right = left + colWidth;
    int bottom = top + rowHeight;

    CStatic* pLabel = new CStatic();
    pLabel->Create(CString(pFieldName.c_str()), WS_CHILD | WS_VISIBLE | SS_CENTER,
        CRect(left, top, right, bottom), pParentWnd);
}

bool MDatabaseFake::MM_Row_Set(const std::string& pTableName, int pId, const MRow& pMRow) {
    if (mv_tables[pTableName].find(pId) != mv_tables[pTableName].end()) {
        mv_tables[pTableName][pId] = pMRow;
        return true;
    }
    else {
        return false;
    }
}

int MDatabaseFake::MM_MRow_Empty_Set(const std::string& pTableName) {
    MRow emptyRow;
    for (std::map<std::string, MFieldProperty>::iterator it = mv_mFieldProperties[pTableName].begin(); it != mv_mFieldProperties[pTableName].end(); ++it) {
        emptyRow.fields[it->first] = ""; // Imposta ogni campo a una stringa vuota
    }

    int id = mv_ids_next[pTableName]++;
    mv_tables[pTableName][id] = emptyRow;
    return id;
}

void MDatabaseFake::MM_Data_Test_Get() {

    // Print all records of Account table
    std::cout << "All records of 'Account' table:" << std::endl;
    MM_Table_Read("Account");

    // Get the record with id 0 from the Account table
    std::cout << "Record with ID " << 0 << " in 'Account' table:\n" << MM_Row_Read("Account", 0) << std::endl;

    // Delete the record with id 1 from the Account table
    MM_Row_Delete("Account", 1);
    std::cout << "Record with ID " << 1 << " deleted from 'Account' table." << std::endl;
    std::cout << "All records of 'Account' table after delete:" << std::endl;
    MM_Table_Read("Account");

    // Get position of a field
    try {
        MFieldProperty pos = Get_Field_Position("Account", "FirstName");
        std::cout << "Position of 'FirstName' in 'Account': (" << pos.row << ", " << pos.col << ")" << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}
