cmake_minimum_required(VERSION 3.24)
project(SkiptShell)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(SkiptShell main.cpp Shell/Editor.cpp Shell/Editor.h String.cpp String.h File.cpp File.h Shell/Lexer.cpp Shell/Lexer.h Errors.cpp Errors.h Property/PropertyFile.cpp Property/PropertyFile.h Property/PropertyReference.cpp Property/PropertyReference.h Property/Property.h Documentation/Documentation.cpp Documentation/Documentation.h Documentation/DocumentationObject.h)
