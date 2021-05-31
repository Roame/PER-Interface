#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

static std::string readFile(const char *location){
    std::ifstream file;
    file.open(location);
    std::stringstream sstm;
    
    std::string line;
    if(file.is_open()){
        while(getline(file, line)){
            sstm << line << "\n";
        }
        file.close();
    } else {
        throw "Unable to open file";
    }

    return sstm.str();
}