//
// Created by Rob on 4/30/2023.
//

#include <iostream>
#include "Documentation.h"
#include "DocumentationObject.h"
#include "../String.h"

#define CONSOLE_COLOR_RESET SetConsoleTextAttribute(outputHandle, 15)
#define CONSOLE_COLOR_RED SetConsoleTextAttribute(outputHandle, 12)
#define CONSOLE_COLOR_GREEN SetConsoleTextAttribute(outputHandle, 10)
#define CONSOLE_COLOR_BLUE SetConsoleTextAttribute(outputHandle, 9)
#define CONSOLE_COLOR_AQUA SetConsoleTextAttribute(outputHandle, 11)
#define CONSOLE_COLOR_PURPLE SetConsoleTextAttribute(outputHandle, 13)
#define CONSOLE_COLOR_YELLOW SetConsoleTextAttribute(outputHandle, 14)


static std::vector<DocumentationObject> DocObjects;

std::vector<DocumentationObject> Documentation::Lookup(std::string txt) {
    std::unique_ptr<std::string> fileName = std::make_unique<std::string>("documentation.txt");
    std::vector<std::string> fileContents = File::ReadAllLines(*fileName);

    std::vector<DocumentationObject> returnObjects;

    for (DocumentationObject & DocObject : DocObjects){
        if (DocObject.Arguments.find(txt) != std::string::npos){
            returnObjects.push_back(DocObject);
        }
    }

    return returnObjects;
}

void Documentation::Init() {
    std::unique_ptr<std::string> fileName = std::make_unique<std::string>("documentation.txt");
    std::vector<std::string> fileContents = File::ReadAllLines(*fileName);

    for (int i = 0; i < fileContents.size(); i++){
        if (isblank(fileContents[i][0])){
            continue;
        }

        DocumentationObject obj;

        if (fileContents[i][0] != '#'){
            obj.Arguments = fileContents[i];
            obj.Comment = fileContents[i + 1];
            obj.Examples = fileContents[i + 2];

            i += 3;

            DocObjects.push_back(obj);
            std::cout << "[Documentation.cpp] Added Object To DocumentationObject\n";
        }

    }
}

bool Documentation::ReferenceExists(const std::string &text) {
    for (DocumentationObject & object : DocObjects){
        std::unique_ptr<std::string> functionCall = std::make_unique<std::string>(object.Arguments);
        std::unique_ptr<int> endFunction = std::make_unique<int>(object.Arguments.find('('));
        *functionCall = functionCall->substr(0, *endFunction);

        if (text == *functionCall){
            return true;
        }
    }

    return false;
}

void Documentation::DisplayDocumentation(HANDLE outputHandle) {
    while (true){
        CONSOLE_COLOR_RESET;

        system("CLS");
        std::cout << "Skipt Documentation\nType a keyword below to search:\n============================\n>>> ";

        std::unique_ptr<std::string> userInput = std::make_unique<std::string>();
        std::getline(std::cin, *userInput);

        std::vector<DocumentationObject> obj = Documentation::Lookup(*userInput);

        std::cout << "\nResults for \"" << *userInput << "\" | (" << obj.size() << ")\n---------------";
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
        std::cout << "\n\n===============================\n";
        CONSOLE_COLOR_RED;
        std::cout << "Press ENTER to re-search\n";

        std::unique_ptr<std::string> emptyInput = std::make_unique<std::string>();
        std::getline(std::cin, *emptyInput);
    }
}



