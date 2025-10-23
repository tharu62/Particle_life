#include <iostream>
#include <string>

/**
 * @brief Handles command line input for the particle simulation application.
 */
void handle(int size, char* input[])
{
    
    if(size == 1){
        
        std::cout << std::endl;
        std::cerr << "\033[0;31m" << "[error] " << "\33[m" <<  "Invalid argument." << std::endl;
        std::cerr << "\033[0;31m" << "[error] " << "\33[m" << "Number of particles required as parameter." << std::endl;
        std::cerr << "\33[m" << "[help] Use the command <help> to check all possible correct argument" << std::endl;
        std::cout << std::endl;
        exit(0);
    }

    if(atoi(input[1]) < 0){

        std::cout << std::endl;
        std::cerr << "\033[0;31m" << "[error] " << "\33[m" << "Invalid argument." << std::endl;
        std::cerr << "\033[0;31m" << "[error] " << "\33[m" << "Negative number of particles not allowed." << std::endl;
        std::cerr << "\33[m" << "[help] Use the command <help> to check all possible correct argument" << std::endl;
        std::cout << std::endl;
        exit(0);
    }

    if(atoi(input[1]) > 5000){

        std::cout << std::endl;
        std::cerr << "\033[0;31m" << "[error] " << "\33[m" << "Invalid argument." << std::endl;
        std::cerr << "\033[0;31m" << "[error] " << "\33[m" << "The maximum number of particles is 5000" << std::endl;
        std::cerr << "\33[m" << "[help] Use the command <help> to check all possible correct argument" << std::endl;
        std::cout << std::endl;
        exit(0);
    }

    if((std::string)input[1] == "help"){
        
        std::cout << std::endl;
        std::cout << "[run] main.exe <arg> " << std::endl;
        std::cout << "[run] <arg> = number of particles to simulate, it must be an integer between 0 and 5000." << std::endl;
        std::cout << std::endl;
        exit(0);
    }

    return;
}