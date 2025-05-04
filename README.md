# PARTICLE LIFE (WORKING IN PROGRESS )

This program is a simulation of living particles with a defined set of rules that results in a peculiar behaviour.

## INSTALL
To run the program, first download the repository in your prefered folder, you can use this command from terminal :
```bash
 git clone https://github.com/tharu62/Gravity_simulation.git
```
Then you will need to build the program using CMake. On Windows 11 you will need to install the necessary MingW compiler compatible with SFML Ver.3.0.0
You can find all necessary information in their website. 

To compile on Windows 11, from the Particle_Life directory use this commands from terminal :
```bash
 mkdir build
 cd build
 cmake ..
 cmake --build build
```

To compile on Linux. from the Particle_life directory use this commands form terminal :
```bash
 cmake -B build
 cmake --build build
```