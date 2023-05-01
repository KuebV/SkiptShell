//
// Created by Rob on 4/28/2023.
//

#ifndef SKIPTSHELL_LEXER_H
#define SKIPTSHELL_LEXER_H


#include <string>
#include "../String.h"
#include <sstream>
#include "../Errors.h"
#include "Editor.h"

class Lexer {
public:
    enum Keywords{
        Int,
        Double,
        Float,
        StringType,
        Bool,
        Reference,
        If,
        While,
        IntArray,
        DoubleArray,
        FloatArray,
        StringArray,
        Free,
        UnsafeFree,
        Null,
        Input,
        Output
    };

    explicit Lexer(const std::string& line){
        String lineString(line);

        Line = lineString.ToString();
    }

    static Keywords ValidKeyword(const std::string& keyword);

    Editor::EditorModifers Process();

    static bool IsValidType(Keywords keyword, std::string value);
    static Editor::EditorModifers ToModifier(const std::string& mod);


private:
    std::string Line;
};


#endif //SKIPTSHELL_LEXER_H
