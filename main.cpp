#include <iostream>
#include <unordered_map>
#include <string>
#include <processenv.h>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <map>
#include "Shell/Editor.h"
#include "Property/Property.h"
#include "Property/PropertyFile.h"
#include "File.h"
#include "Documentation//Documentation.h"


using namespace std;

void CreatePropertyFile(){
    Property SkiptExecutable("PathToSkipt", "\"/path/to/skipt.exe\"", "The File Path to the Skipt Interpreter");
    std::vector<Property> properties = {SkiptExecutable};
    PropertyFile::WritePropertyFile("shell.properties", properties);
}

int main() {

    std::string propertyFile = "shell.properties";
    if (!File::Exists(propertyFile)){
        CreatePropertyFile();
        std::cout << propertyFile << " has been created. Configure then restart the application!\nPress any key to exit.";
        getch();
        exit(0);
    }

    Documentation::Init();

    bool selecting = true;

    map<int, string> menuSelection;
    menuSelection[0] = "[1] Write New Skipt";;
    menuSelection[1] = "[2] Read Documentation";
    menuSelection[2] = "[3] About Skipt";

    int selectedIndex = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    while (selecting){
        system("CLS");

        std::cout << "\n"
                     "   _____ _  _______ _____ _______ \n"
                     "  / ____| |/ /_   _|  __ \\__   __|\n"
                     " | (___ | ' /  | | | |__) | | |   \n"
                     "  \\___ \\|  <   | | |  ___/  | |   \n"
                     "  ____) | . \\ _| |_| |      | |   \n"
                     " |_____/|_|\\_\\_____|_|      |_|   \n"
                     "                                  \n"
                     "                                  \n";
        std::cout << "=====================================\n";



        for (int i = 0; i < menuSelection.size(); i++){
            if (selectedIndex == i){
                SetConsoleTextAttribute(handle, 31);
                std::cout << menuSelection[i] << "\n";
            }
            else{
                SetConsoleTextAttribute(handle, 15);
                std::cout << menuSelection[i] << "\n";
            }

            SetConsoleTextAttribute(handle, 15);
        }

        char input;
        input = getch();

        switch (input){
            case 'S':
            case 's':
                selectedIndex++;
                break;
            case 'W':
            case 'w':
                selectedIndex--;
                break;
            case 'D':
            case 'd':
                selecting = false;
                break;
        }

        if (selectedIndex > menuSelection.size() - 1 || selectedIndex < 0)
            selectedIndex = menuSelection.size() - 1;

        if (selectedIndex < 0)
            selectedIndex = 0;


        system("CLS");
    }

    switch (selectedIndex){
        case 0:{
            Editor::RunEditor(handle);
            break;
        }
        case 1:{
            Documentation::DisplayDocumentation(handle);
            break;
        }
        case 2:{
            std::cout << "\n"
                         "   _____ _  _______ _____ _______ \n"
                         "  / ____| |/ /_   _|  __ \\__   __|\n"
                         " | (___ | ' /  | | | |__) | | |   \n"
                         "  \\___ \\|  <   | | |  ___/  | |   \n"
                         "  ____) | . \\ _| |_| |      | |   \n"
                         " |_____/|_|\\_\\_____|_|      |_|   \n"
                         "                                  \n"
                         "                                  \n";
            std::cout << "Skipt was made by Robert Thompson for the CSC-1060 Term Project\nDevelopment Time:\nInterpreter: 4 Months\nShell: 2.5 Days\n\nIf you enjoy your sleep schedule, don't write an interpreter";
            break;
        }
    }

    int l;
    cin >> l;

}
