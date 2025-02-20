# Overview
This repository contains the MAccountDemoView solution.
MAccountDemoView is a demo data entry form for an Account entity written in C++ with MFC in Visual Studio 2019.
A fake database is implemented where new records are added and modified.
By downloading and opening the MAccountDemoView.sln solution, the startup project (which should already be set correctly) is MAccount. The default build configuration is Debug, x64.

Compiling MAccount will result in the following screen:

![image](https://github.com/user-attachments/assets/9c573a37-6663-41f4-a30f-39cab87d603f)


To save the data, simply modify the desired fields and press "<" to navigate back or ">" to navigate forward in the records.
To add a new record, navigate forward by clicking the ">" button until the fields are empty. Enter the desired information, then press "<" or ">" to save, as mentioned before.

# Note
Each project defines a standalone object and can be compiled and run independently. The Main.cpp file in each project is used as a test unit to test the object.
Each project starts as a C++ Console Application and is then converted into an MFC C++ application by setting the following project properties:
1) Properties > Configuration Properties > Advanced > Use of MFC > Use MFC in a Shared DLL
2) Properties > Linker > System > SubSystem > Windows (/SUBSYSTEM:WINDOWS)
To analyze the code, it may be useful to follow the order: MComponent, MLabel, MEdit, MLabelAndEdit, MHeader, MDatabaseFake, MAccount
All objects derive from the base class MComponent

# Naming Conventions
Each class that is defined starts with M + UpperCamelCase. For example, a class that creates a label will be named MLabel.
Variables inside classes start with mv_ + snake_case
Variables within methods are written in snake_case
Parameters in methods start with p lowercase + UpperCamelCase
