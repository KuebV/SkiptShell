//
// Created by Rob on 4/28/2023.
//

#ifndef SKIPTSHELL_ERRORS_H
#define SKIPTSHELL_ERRORS_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <processenv.h>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <map>


class Errors {
public:
    static void ThrowCustomError(const std::string& error);
    static void ThrowCustomWarning(const std::string& warning);

    static void SetHandle(HANDLE handle);

    enum ERRORS{
        InvalidKeyword,
        InvalidValue,
        InvalidEditorCommand,
        InvalidReference,
        ReferenceDoesNotExist,
        ReferenceMissingArgument,


    };

    enum WARNINGS{
        REF_NO_RETURN, // Reference does not return any value


    };

    static void ThrowError(ERRORS error);
    static void ThrowWarning(WARNINGS warning);

    static std::string FromError(ERRORS error);
    static std::string FromWarning(WARNINGS warning);
};


#endif //SKIPTSHELL_ERRORS_H
