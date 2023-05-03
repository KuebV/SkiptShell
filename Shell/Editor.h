//
// Created by Rob on 4/28/2023.
//

#ifndef SKIPTSHELL_EDITOR_H
#define SKIPTSHELL_EDITOR_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <processenv.h>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <map>
#include "../String.h"


class Editor {
public:
    static void RunEditor(HANDLE outputHandle);
    static std::string fileName;

    enum EditorModifers{
        Undo,
        DeleteLine,
        Error,
        Warning,
        Refresh,
        Save,
        Lookup,
        Clear,
        Help,
        Unknown,
        None
    };

    static void DefineVariable(const std::string& var);
    static std::vector<std::string> GetVariables();
    static bool IsDefinedVariable(const std::string& var);
    static bool IsDefinedVariable(String& var);
private:

    static HANDLE _handle;
    static void StartSkipt(const LPCTSTR& path);

};


#endif //SKIPTSHELL_EDITOR_H
