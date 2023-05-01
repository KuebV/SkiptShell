//
// Created by Rob on 4/28/2023.
//

#ifndef SKIPTSHELL_FILE_H
#define SKIPTSHELL_FILE_H

#include <fstream>
#include <string>
#include <vector>


class File {
public:
    static bool Exists(const std::string& fileName);
    static void Create(const std::string& fileName);
    static void Write(const std::string& fileName, std::string& fileContents);
    static void Write(const std::string& fileName, std::vector<std::string>& fileContents);
    static void WriteLines(const std::string& fileName, std::vector<std::string>& fileContents);

    static void Append(const std::string& fileName, std::string& fileContents);
    static void Append(const std::string& fileName, std::vector<std::string>& fileContents);

    static void Delete(const std::string& fileName);

    static std::vector<std::string> ReadAllLines(const std::string& fileName);
    static std::string ReadAllText(const std::string& fileName);

};


#endif //SKIPTSHELL_FILE_H
