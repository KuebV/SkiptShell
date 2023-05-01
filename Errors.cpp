//
// Created by Rob on 4/28/2023.
//

#include "Errors.h"

static HANDLE OutputHandle;

void Errors::ThrowCustomError(const std::string &error) {
    SetConsoleTextAttribute(OutputHandle, 12);
    std::cout << error << "\n";
    SetConsoleTextAttribute(OutputHandle, 15);
}

void Errors::ThrowCustomWarning(const std::string &warning) {
    SetConsoleTextAttribute(OutputHandle, 14);
    std::cout << warning << "\n";
    SetConsoleTextAttribute(OutputHandle, 15);
}

void Errors::ThrowError(Errors::ERRORS error) {
    ThrowCustomError(FromError(error));
}

void Errors::ThrowWarning(Errors::WARNINGS warning) {
    ThrowCustomError(FromWarning(warning));
}

std::string Errors::FromError(Errors::ERRORS error) {
    const std::unordered_map<ERRORS, std::string> keywordTable{
            { ERRORS::InvalidKeyword, "Invalid Keyword!\nValid Keywords: int, double, float, bool, string, int[], double[], float[], string[], ref, if, while, free, free*"},
            { ERRORS::InvalidValue, "Invalid Value!\nCheck that the value is compatible with the data-type!"},
            { ERRORS::InvalidEditorCommand, "Invalid Editor Command\nThe specified command does not exist!"},
            { ERRORS::InvalidReference, "Invalid Reference!\nCheck that the reference is called according to the format!"},
            { ERRORS::ReferenceDoesNotExist, "Invalid Reference!\nSpecified Reference does not exist!"},
            { ERRORS::ReferenceMissingArgument, "Invalid Reference\nMissing one or more arguments, check documentation."}
    };

    auto item = keywordTable.find(error);
    if (item != keywordTable.end())
        return item->second;
    else
        return "Undefined Error";
}

std::string Errors::FromWarning(Errors::WARNINGS warning) {
    const std::unordered_map<WARNINGS, std::string> keywordTable{
            { WARNINGS::REF_NO_RETURN, "Reference does not return any value"}
    };

    auto item = keywordTable.find(warning);
    if (item != keywordTable.end())
        return item->second;
    else
        return "Undefined Warning";
}

void Errors::SetHandle(HANDLE handle) {
    OutputHandle = handle;
}


