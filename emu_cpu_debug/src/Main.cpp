#include <iostream>
#include "console/Gameboy.h"

#define mycout std::cout <<  __FILE__  << "(" << __LINE__ << ") "
#define cout mycout

int main(int argc, char* argv[]){

    if(argc < 2){
        std::cerr << "Need the path of the rom" << std::endl;
        return 1;
    }

    Gameboy gameboy(argv[1]);
    
    if(argc == 3 && std::string(argv[2]) == "-d"){
        gameboy.debugMode();
    }

    return gameboy.run();
}
