//
// Created by Rob on 4/29/2023.
//

#include "PropertyReference.h"
#include <string>

std::string PropertyReference::getValue(std::string _key) {
    return PropertyReference::KeyPairValue[_key];
}

void PropertyReference::appendKeyPair(std::string _key, std::string _value) {
    PropertyReference::KeyPairValue.insert({_key, _value});
}