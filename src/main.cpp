#include "application.cpp"
#include "main_input_handler.hpp"

int main(int argc, char* argv[])
{
    handle(argc, argv);
    
    application ParticleLifeApp = application(atoi(argv[1]));
    ParticleLifeApp.run();
    ParticleLifeApp.clean();

    return 0;
}