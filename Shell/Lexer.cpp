//
// Created by Rob on 4/28/2023.
//

#include "Lexer.h"
#include "../Documentation/Documentation.h"


Lexer::Keywords Lexer::ValidKeyword(const std::string &keyword) {
    const std::unordered_map<std::string, Keywords> keywordTable{
            { "int", Int},
            { "double", Double},
            { "float", Float},
            { "string", StringType},
            { "bool", Bool},
            { "int[]", IntArray},
            { "double[]", DoubleArray},
            { "float[]", FloatArray},
            { "string[]", StringArray},
            { "ref", Reference},
            { "if", If},
            { "while", While},
            { "free", Free},
            { "free*", UnsafeFree},
            { "<", Input},
            { ">", Output}
    };

    auto item = keywordTable.find(keyword);
    if (item != keywordTable.end())
        return item->second;
    else
        return Null;
}


bool Lexer::IsValidType(Lexer::Keywords keyword, std::string value) {
    std::unique_ptr<String> ptrString = std::make_unique<String>(String(value));
    ptrString->ptr_Strip(String::StripOptions::All);

    value = ptrString->ToString();
    ptrString.release();

    switch (keyword){
        case Int:{
            try{
                std::stoi(value);
                return true;
            }
            catch (std::exception &err){
                return false;
            }
        }
        case Double:{
            double _x;
            std::istringstream iss(value);
            iss >> _x;
            if (iss.fail())
                return false;
            return true;
        }
        case Float:{
            float _x;
            std::istringstream iss(value);
            iss >> _x;
            if (iss.fail())
                return false;
            return true;
        }
        case StringType:{
            size_t firstQuotation = value.find_first_of('"');
            size_t lastQuotation = value.find_last_of('"');

            if (firstQuotation == lastQuotation)
                return false;

            if (firstQuotation == std::string::npos)
                return false;

            if (lastQuotation == std::string::npos)
                return false;

            return true;
        }
        default:{
            return true;
        }
    }
}

Editor::EditorModifers Lexer::Process() {
    String lineContent(Line);
    if (lineContent.Contains(";"))
        lineContent.ptr_ReplaceSingle(";", "");

    if (Line.rfind("//", 0) == 0){
        std::vector<String> editorArgs = lineContent.Split(" ");

        Editor::EditorModifers mod = ToModifier(editorArgs[0].Substring(2).ToString());
        if (mod == Editor::EditorModifers::Unknown){
            Errors::ThrowError(Errors::InvalidEditorCommand);
            return Editor::Error;
        }

        return mod;
    }

    std::vector<String> LineElements = lineContent.Split(" ");

    if (LineElements[0].Length < 1)
        return Editor::None;

    if (LineElements[0].StartsWith('#'))
        return Editor::None;

    if (ValidKeyword(LineElements[0].ToString()) == Null && !Editor::IsDefinedVariable(LineElements[0])){
        Errors::ThrowError(Errors::InvalidKeyword);
        return Editor::Error;
    }

    if (ValidKeyword(LineElements[0].ToString()) != Null && LineElements.size() >= 2 && ValidKeyword(LineElements[0].ToString()) != Reference){
        size_t equalsOperator = lineContent.Until("=");
        String value(lineContent.Substring(equalsOperator + 1, (lineContent.Length - equalsOperator)));
        value.ptr_Strip(String::StripOptions::All);

        if (!IsValidType(ValidKeyword(LineElements[0].ToString()), value.ToString())){
            Errors::ThrowError(Errors::InvalidValue);
            return Editor::Error;
        }

        Editor::DefineVariable(LineElements[1].ToString());
    }

    if (ValidKeyword(LineElements[0].ToString()) == Reference){
        if (lineContent.Count("::") != 1){
            Errors::ThrowError(Errors::InvalidReference);
            return Editor::Error;
        }

        if (lineContent.ToString().find('(') == std::string::npos){
            Errors::ThrowError(Errors::InvalidReference);
            return Editor::Error;
        }

        if (lineContent.ToString().find(')') == std::string::npos){
            Errors::ThrowError(Errors::InvalidReference);
            return Editor::Error;
        }

        if (!Documentation::ReferenceExists(lineContent.ContentBetween(" ", "(").ToString())){
            Errors::ThrowError(Errors::ReferenceDoesNotExist);
            return Editor::Error;
        }
    }

    return Editor::None;


}

Editor::EditorModifers Lexer::ToModifier(const std::string &mod) {
    const std::unordered_map<std::string, Editor::EditorModifers> modifierTable{
            { "undo", Editor::EditorModifers::Undo},
            { "refresh", Editor::EditorModifers::Refresh},
            { "save", Editor::EditorModifers::Save},
            { "lookup", Editor::EditorModifers::Lookup}
    };

    auto item = modifierTable.find(mod);
    if (item != modifierTable.end())
        return item->second;
    else
        return Editor::EditorModifers::Unknown;
}

