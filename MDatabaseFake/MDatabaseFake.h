/*
This file is part of the Visual Studio Solution MAccountDemoView.sln.
The Visual Studio Solution MAccountDemoView.sln is composed by the projects MAccount, MComponent, MDatabaseFake, MEdit, MHeader, MLabel, MLabelAndEdit.
This file, the solution and the project mentioned are licensed under the MIT License.See http ://opensource.org/licenses/MIT for more information.

Copyright(c) 2024 fred4code
*/

#ifndef MDATABASEFAKE_H
#define MDATABASEFAKE_H

#include <map>
#include <string>
#include <vector>

#include "../MComponent/MComponent.h"

struct MRow {
    bool mv_valid;
    std::map<std::string, std::string> fields;
};

struct MFieldProperty {
    int row;
    int col;
    int columns; // total number of columns for the row
    int mLabel_width_percent;
    int mEdit_width_percent;
};

class MDatabaseFake : public MComponent
{
public:
    MDatabaseFake();
    ~MDatabaseFake();
    void MM_Destroy() override;

    // Creates a new row in the specified table and returns the ID of the created row
    int MM_Row_Create(const std::string& pTableName, const MRow& pRecord);

    // Deletes a row from the specified table using the row ID, returns true if the row was deleted
    bool MM_Row_Delete(const std::string& pTableName, int pId);

    // Retrieves a row from the specified table using the row ID, returns an MRow object
    MRow MM_Row_Get(const std::string& pTableName, int pId);

    // Reads a row from the specified table and returns a string containing the fields and their values
    std::string MM_Row_Read(const std::string& pTableName, int pId);

    // Gets the position of a field in the specified table
    MFieldProperty Get_Field_Position(const std::string& pTableName, const std::string& PFieldName);

    // Creates a label based on the field position in the specified table
    void Create_Label(CWnd* pParentWnd, const std::string& pTableName, const std::string& PFieldName);

    // Sets a row in the specified table with the provided data, returns true if the row existed
    bool MM_Row_Set(const std::string& pTableName, int pId, const MRow& pMRow);

    // Creates an empty row in the specified table and returns the ID of the created row
    int MM_MRow_Empty_Set(const std::string& pTableName);

    // Debug: reads all records from the specified table
    void MM_Table_Read(const std::string& pTableName);

    // Debug: performs various tests and prints the results
    void MM_Data_Test_Get();

private:
    std::map<std::string, std::map<std::string, MFieldProperty>> mv_mFieldProperties;
    std::map<std::string, std::map<int, MRow>> mv_tables;
    std::map<std::string, int> mv_ids_next;

};

#endif