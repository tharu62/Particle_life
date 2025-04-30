#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>
#include <chrono>


#include "eventHandler.hpp"
#include "setUp.hpp"
#include "forceGeneration.hpp"
#include "positionUpdate.hpp"
#include "collsionUpdate.hpp"
#include "ImGuiManager.hpp"
#include "colorMatrix.hpp"
#include "gridSort.hpp"

#define DEFAULT_PARTICLE_COUNTER 1000
#define DEFAULT_PARTICLE_RADIUS 3
#define DEFAULT_STRENGTH 30.f
#define DEFAULT_REPULSION_FACTOR 20.f

int PARTICLE_COUNT = DEFAULT_PARTICLE_COUNTER;
int PARTICLE_RADIUS = DEFAULT_PARTICLE_RADIUS;
float STRENGHT = DEFAULT_STRENGTH;
float REPULSION_FACTOR = DEFAULT_REPULSION_FACTOR;
int GRID_SIZE = DEFAULT_PARTICLE_RADIUS * 60;

class application {

    private:
        bool moving = false;
        bool paused = false;
        bool opened = false;
        bool resetted = false;
        sf::Vector2f oldPos;
        sf::CircleShape* particles;
        sf::Vector2f* acceleration;
        std::vector<Node> grid;

    public:

        application(int particleCount = DEFAULT_PARTICLE_COUNTER){
            PARTICLE_COUNT = particleCount;
        };


        void clean(){
            ImGui::SFML::Shutdown();
            delete[] particles;
            delete[] acceleration;
        }

        void drawGridBox(sf::RenderWindow &window, sf::Vector2f center, float size){
            sf::RectangleShape box;
            box.setSize({size, size});
            box.setPosition(center);
            box.setOrigin({size/2, size/2});
            box.setOutlineColor(sf::Color::Green);
            box.setOutlineThickness(1.f);
            box.setFillColor(sf::Color::Transparent);
            window.draw(box);
        }

        void run(){

            auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Particle Life Project");
            sf::View view = window.getDefaultView();
            view.setCenter({640, 360});
            view.setSize({1280, 720});
            // window.setFramerateLimit(100);
            window.setVerticalSyncEnabled(true);
            if (!ImGui::SFML::Init(window))
                return;

            particles = new sf::CircleShape[PARTICLE_COUNT];
            acceleration =  new sf::Vector2f[PARTICLE_COUNT];
            float colorMatrix[9][9];
            
            init_colorMatrix(colorMatrix);
            // std::cout << "Color matrix initialized!" << std::endl;
            // for(int i=0; i<9; ++i){
            //     for(int j=0; j<9; ++j){
            //         std::cout << colorMatrix[i][j] << " ";
            //     }
            //     std::cout << std::endl;
            // }

            SetParticle(particles, PARTICLE_RADIUS);
            initGrid(grid, 3000, 3000, GRID_SIZE);    

            clock_t start = 0;
            clock_t end = 0;
            sf::Clock clock;
            int framerate = 0;
            while (window.isOpen())
            {
                start = std::clock();
                while (const std::optional event = window.pollEvent())
                {

                    ImGui::SFML::ProcessEvent(window, *event);
                    EventHandler(event, view, window, oldPos, moving, paused);
                    
                }
                
                if(!paused){
                    
                    cleanGrid(grid);
                    insertGrid(particles, acceleration, grid, PARTICLE_COUNT, GRID_SIZE);
                    updateForces(particles, acceleration, colorMatrix, grid);
                    updatePosition(particles, acceleration);
                    // CollisionUpdate(particles, grid, 100*PARTICLE_RADIUS);
                    // CollisionUpdate(particles, velocity);

                    ImGui::SFML::Update(window, clock.restart());   
                    manageImGui(window, clock, opened, particles, framerate, PARTICLE_COUNT, PARTICLE_RADIUS, STRENGHT, REPULSION_FACTOR, resetted);
                    if(resetted){
                        resetted = false;
                        resetParticles();
                    }

                }else{
                    ImGui::SFML::Update(window, clock.restart());
                    ImGui::Begin("ImGui SFML window");
                    ImGui::Text("Simulation paused!");
                    ImGui::End();
                }

                window.clear();
                
                window.setView(view);
                for(int i=0; i<PARTICLE_COUNT; ++i){
                    window.draw(particles[i]);
                }
                
                // // For testing grid
                // for(int i=0; i<grid.size(); ++i){
                //     drawGridBox(window, grid[i].center, 100*PARTICLE_RADIUS);
                // }
                
                ImGui::SFML::Render(window);
                    
                end = std::clock();
                framerate = (int) (CLOCKS_PER_SEC / double(end - start));

                window.display();
            }
            
        }

    private:
    
        void resetParticles(){
            PARTICLE_COUNT = DEFAULT_PARTICLE_COUNTER;
            // PARTICLE_RADIUS = DEFAULT_PARTICLE_RADIUS;
            // STRENGHT = DEFAULT_STRENGTH;
            delete[] particles;
            delete[] acceleration;
            particles = new sf::CircleShape[PARTICLE_COUNT];
            acceleration =  new sf::Vector2f[PARTICLE_COUNT];
            SetParticle(particles, PARTICLE_RADIUS);
        }

};