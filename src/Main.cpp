#include <iostream>
#include "cpu/Processor.h"
#include "cpu/instruction/instructionError/UnknownInstructionException.h"

int main(int argc, char* argv[]){

    if(argc != 2){
        std::cerr << "Need the path of the rom" << std::endl;
        return 1;
    }

    Processor cpu(argv[1]);
    
    cpu.printMetadata();

    try{
        cpu.run();
    }catch(UnknownInstructionException &error){
        std::cerr << error.what() << std::endl;
        return 1;
    }

    return 0;
}
