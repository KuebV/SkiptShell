//
// Created by Rob on 4/29/2023.
//

#ifndef SKIPTSHELL_PROPERTYREFERENCE_H
#define SKIPTSHELL_PROPERTYREFERENCE_H

#include <string>
#include <map>

class PropertyReference {
public:
    std::string getValue(std::string _key);
    void appendKeyPair(std::string _key, std::string _value);
private:
    std::map<std::string, std::string> KeyPairValue;
};



#endif //SKIPTSHELL_PROPERTYREFERENCE_H
