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
    menuSelection[0] = "[1] Write New Skipt";
    menuSelection[1] = "[2] Execute Skipt";
    menuSelection[2] = "[3] Read Documentation";
    menuSelection[3] = "[4] About Skipt";

    int selectedIndex = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    while (selecting){
        system("CLS");

        for (int i = 0; i < menuSelection.size(); i++){
            if (selectedIndex == i){
                SetConsoleTextAttribute(handle, 31);
                std::cout << menuSelection[i] << "\n";
            }
            else{
                SetConsoleTextAttribute(handle, 15);
                std::cout << menuSelection[i] << "\n";
            }
        }

        char input;
        input = getch();

        switch (input){
            case 's':
                selectedIndex++;
                break;

            case 'w':
                selectedIndex--;
                break;
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
    }

    int l;
    cin >> l;

}
