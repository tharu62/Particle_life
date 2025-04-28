#include "application.cpp"

int main(int argc, char* argv[])
{

    // if(argc == 1) {
    //     return -1;
    // }
    // else {
    //     application ParticleLifeApp = application(atoi(argv[1]));
    //     ParticleLifeApp.run();
    //     ParticleLifeApp.clean();
    // }

    application ParticleLifeApp = application(atoi(argv[1]));
    ParticleLifeApp.run();
    ParticleLifeApp.clean();

    return 0;
}