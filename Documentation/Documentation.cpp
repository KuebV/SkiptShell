//
// Created by Rob on 4/30/2023.
//

#include <iostream>
#include "Documentation.h"
#include "DocumentationObject.h"


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

