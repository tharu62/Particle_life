#include "application.cpp"

int main(int argc, char* argv[])
{
    application ParticleLifeApp = application(atoi(argv[1]));
    ParticleLifeApp.run();
    ParticleLifeApp.clean();

    return 0;
}