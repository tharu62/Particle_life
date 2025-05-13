#include <iostream>
#include <string>

void handle(int size, char* input[])
{
    
    if(size == 1){
        
        std::cerr << "\033[0;31m" << "error: invalid parameter value." << std::endl;
        std::cerr << "Use the command <help> to check all possible correct parameter values" << std::endl;
        exit(0);
    }

    if(atoi(input[1]) < 0){

        std::cerr << "\033[0;31m" << "error: invalid parameter value." << std::endl;
        std::cerr << "Use the command <help> to check all possible correct parameter values" << std::endl;
        exit(0);
    }

    if((std::string)input[1] == "help"){
        
        std::cout << std::endl;
        std::cout << "  cmd syntax : simulator.exe <arg1> " << std::endl;
        std::cout << "  <arg1> = number of bodies to simulate " << std::endl;
        std::cout << std::endl;
        exit(0);
    }

    return;
}