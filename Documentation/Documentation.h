//
// Created by Rob on 4/30/2023.
//

#ifndef SKIPTSHELL_DOCUMENTATION_H
#define SKIPTSHELL_DOCUMENTATION_H

#include <fstream>
#include <memory>
#include "../File.h"
#include "DocumentationObject.h"

class Documentation {
public:
    static void Init();
    static std::vector<DocumentationObject> Lookup(std::string txt);
    static bool ReferenceExists(const std::string& text);
private:

};


#endif //SKIPTSHELL_DOCUMENTATION_H
