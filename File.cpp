//
// Created by Rob on 4/28/2023.
//

#include <sstream>
#include "File.h"

bool File::Exists(const std::string &fileName) {
    if (FILE *P_FILE = fopen(fileName.c_str(), "r")){
        fclose(P_FILE);
        return true;
    }
    return false;
}

void File::Create(const std::string &fileName) {
    std::ofstream stream;
    stream.open(fileName);
    stream.close();
}

void File::Write(const std::string &fileName, std::string &fileContents) {
    std::ofstream stream(fileName);
    stream << fileContents;
    stream.close();
}

void File::Write(const std::string &fileName, std::vector<std::string> &fileContents) {
    std::ofstream stream(fileName);
    for (const auto & fileContent : fileContents)
        stream << fileContent;
    stream.close();
}

void File::WriteLines(const std::string &fileName, std::vector<std::string> &fileContents) {
    std::ofstream stream(fileName);
    for (const auto & fileContent : fileContents)
        stream << fileContent << "\n";
    stream.close();
}

void File::Append(const std::string &fileName, std::string &fileContents) {
    std::ofstream stream(fileName, std::ios::app);
    stream << fileContents;
    stream.close();
}

void File::Append(const std::string &fileName, std::vector<std::string> &fileContents) {
    std::ofstream stream(fileName, std::ios::app);
    for (const auto& contents : fileContents)
        stream << contents;
    stream.close();
}

void File::Delete(const std::string &fileName) {
    std::remove(fileName.c_str());
}

std::vector<std::string> File::ReadAllLines(const std::string &fileName) {
    std::vector<std::string> vector;
    std::string line;

    std::ifstream stream(fileName);
    while (std::getline(stream, line)){
        vector.push_back(line);
    }
    stream.close();

    return vector;
}

std::string File::ReadAllText(const std::string &fileName) {
    std::ifstream stream(fileName);
    std::string contents;
    if (stream){
        std::ostringstream oss;
        oss << stream.rdbuf();
        contents = oss.str();
    }
    return contents;
}



