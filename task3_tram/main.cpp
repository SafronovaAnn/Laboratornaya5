#include "tram_actions.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    cout << "Управление трамваями" << endl;
    
    string line;
    while (true) {
        cout << ">>> ";
        getline(cin, line);
        
        if (line == "EXIT" || line == "exit") {
            cout << "Программа завершена." << endl;
            break;
        }
        
        if (line.empty()) continue;
        
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        
        if (cmd == "CREATE_TRAM") {
            string args;
            getline(ss, args);
            if (!args.empty() && args[0] == ' ') {
                args = args.substr(1);
            }
            handleCreateTram(args);
        }
        else if (cmd == "TRAMS_IN_STOP") {
            string stopName;
            ss >> stopName;
            handleTramsInStop(stopName);
        }
        else if (cmd == "STOPS_IN_TRAM") {
            string tramName;
            ss >> tramName;
            handleStopsInTram(tramName);
        }
        else if (cmd == "TRAMS") {
            handleTrams();
        }
        else {
            cout << "Неизвестная команда" << endl;
        }
    }
    
    return 0;
}