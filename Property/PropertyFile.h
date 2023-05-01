//
// Created by Rob on 4/29/2023.
//

#ifndef SKIPTSHELL_PROPERTYFILE_H
#define SKIPTSHELL_PROPERTYFILE_H


#include <string>
#include <vector>

#include <fstream>
#include <sstream>
#include "Property.h"
#include "PropertyReference.h"

class PropertyFile {
public:
    static void WritePropertyFile(std::string fileName, std::vector<Property> properties);
    static bool fileExists(const std::string& fileName);
    static PropertyReference ReadPropertyFile(std::string _file);
};


#endif //SKIPTSHELL_PROPERTYFILE_H
