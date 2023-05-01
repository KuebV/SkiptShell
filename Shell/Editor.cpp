#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-unused-return-value"

#include <memory>
#include "Editor.h"
#include "../File.h"
#include "../String.h"
#include "../Errors.h"
#include "Lexer.h"
#include "../Property/PropertyFile.h"
#include "../Documentation/DocumentationObject.h"
#include "../Documentation/Documentation.h"

#define CONSOLE_COLOR_RESET SetConsoleTextAttribute(outputHandle, 15)
#define CONSOLE_COLOR_RED SetConsoleTextAttribute(outputHandle, 12)
#define CONSOLE_COLOR_GREEN SetConsoleTextAttribute(outputHandle, 10)
#define CONSOLE_COLOR_BLUE SetConsoleTextAttribute(outputHandle, 9)
#define CONSOLE_COLOR_AQUA SetConsoleTextAttribute(outputHandle, 11)
#define CONSOLE_COLOR_PURPLE SetConsoleTextAttribute(outputHandle, 13)
#define CONSOLE_COLOR_YELLOW SetConsoleTextAttribute(outputHandle, 14)

static std::vector<std::string> FileLines;
static std::vector<std::string> DefinedVariables;

static std::unique_ptr<std::string> skiptFileName = std::make_unique<std::string>("");
static PropertyReference propRef;


void Editor::RunEditor(HANDLE outputHandle) {
    system("CLS");

    std::cin.clear();
    fflush(stdin);

    if ((*skiptFileName).empty()){
        propRef = PropertyFile::ReadPropertyFile("shell.properties");
        Errors::SetHandle(outputHandle);

        std::cout << "What should the skipt file be created?\n";
        skiptFileName = std::make_unique<std::string>();
        std::getline(std::cin, *skiptFileName);

        if (skiptFileName->find(".skipt") == std::string::npos){
            *skiptFileName += ".skipt";
        }

        if (File::Exists(*skiptFileName)){
            FileLines = File::ReadAllLines(*skiptFileName);
        }
        else{
            File::Create(*skiptFileName);
            SetConsoleTextAttribute(outputHandle, 10);
            std::cout << "\n>>> " << *skiptFileName << " has been created!\n    Press any key to proceed to the shell.\n";
            CONSOLE_COLOR_RESET;

            getch();
        }
    }

    system("CLS");

    CONSOLE_COLOR_RED;
    std::cout << "Alert: Skipt Shell is not an editor or IDE! It will catch formatting errors, but not runtime errors!\n";
    CONSOLE_COLOR_RESET;
    std::cout << "-------------------------------------------------------------" << "\n";
    std::cout << "File Name: " << *skiptFileName << "\n";
    std::cout << "-------------------------------------------------------------" << "\n";

    bool writing = true;
    int lineIndex = 1;

    if (FileLines.size() > 0){
        for (int i = 0; i < FileLines.size(); i++){
            std::cout << "[" << i + 1 << "]: >>> " << FileLines[i] << "\n";
        }

        lineIndex = FileLines.size() + 1;
    }


    while (writing){
        std::cin.clear();
        fflush(stdin);

        std::cout << "[" << lineIndex << "]: >>> ";

        std::unique_ptr<std::string> ptrInput = std::make_unique<std::string>();
        std::getline(std::cin, *ptrInput);
        String input(*ptrInput);

        // Free the pointer input, and allow String Input to handle everything
        ptrInput.release();

        Lexer lexer(input.ToString());
        EditorModifers modifers = lexer.Process();
        switch (modifers){
            case EditorModifers::Lookup:{
                String lookupArgument = input.Substring(input.Until(" ") + 1, (input.Length - input.Until(" ") + 1));
                std::vector<DocumentationObject> obj = Documentation::Lookup(lookupArgument.ToString());
                for (int i = 0; i < obj.size(); i++){
                    std::cout << "------------------------------\n";
                    CONSOLE_COLOR_GREEN;
                    std::cout << obj[i].Arguments << "\n";
                    CONSOLE_COLOR_YELLOW;
                    std::cout << obj[i].Comment << "\n";
                    CONSOLE_COLOR_AQUA;
                    std::cout << obj[i].Examples << "\n\n";
                    CONSOLE_COLOR_RESET;
                }
                std::cout << "------------------------------\n";
                break;
            }
            case EditorModifers::Undo:{
                FileLines.pop_back();
                RunEditor(outputHandle);
                break;
            }
            case EditorModifers::Refresh:{
                RunEditor(outputHandle);
                break;
            }
            case EditorModifers::Save:{
                system("CLS");
                CONSOLE_COLOR_GREEN;
                File::WriteLines(*skiptFileName, FileLines);
                std::cout << *skiptFileName << " has been saved!\nPress any key to return to the editor...";
                getch();
                CONSOLE_COLOR_RESET;
                RunEditor(outputHandle);
                break;
            }
            case EditorModifers::Warning:
            case EditorModifers::None:{
                FileLines.push_back(input.ToString());
                lineIndex++;
            }


        }

    }


}

void Editor::DefineVariable(const std::string &var) {
    DefinedVariables.push_back(var);
}

std::vector<std::string> Editor::GetVariables() {
    return DefinedVariables;
}

bool Editor::IsDefinedVariable(const std::string &var) {
    for (const auto & DefinedVariable : DefinedVariables){
        if (DefinedVariable == var)
            return true;
    }
    return false;
}

bool Editor::IsDefinedVariable(String& var) {
    var.ptr_Strip(String::StripOptions::All);
    for (const auto & DefinedVariable : DefinedVariables){
        if (DefinedVariable == var.ToString())
            return true;
    }
    return false;
}

void Editor::StartSkipt(const LPCTSTR &path) {
    STARTUPINFO startupinfo;
    PROCESS_INFORMATION processInformation;

    ZeroMemory(&startupinfo, sizeof(startupinfo));
    startupinfo.cb = sizeof(startupinfo);
    ZeroMemory(&processInformation, sizeof(processInformation));

    CreateProcess(path,
                  "",
                  NULL,
                  NULL,
                  FALSE,
                  0,
                  NULL,
                  NULL,
                  &startupinfo,
                  &processInformation);
}


#pragma clang diagnostic pop