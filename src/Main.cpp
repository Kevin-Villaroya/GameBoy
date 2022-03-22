#include <iostream>
#include "console/Console.h"

int main(int argc, char* argv[]){

    if(argc != 2){
        std::cerr << "Need the path of the rom" << std::endl;
        return 1;
    }

    Console gameboy(argv[1]);

    return gameboy.run();
}
