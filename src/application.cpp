#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#define DEFAULT_PARTICLE_COUNTER 100
#define DEFAULT_PARTICLE_RADIUS 3

#include "eventHandler.hpp"
#include "setUp.hpp"
#include "forceGeneration.hpp"
#include "positionUpdate.hpp"
#include "collsionUpdate.hpp"

int PARTICLE_COUNT;


class application {

    private:
        bool moving = false;
        bool paused = false;
        sf::Vector2f oldPos;
        sf::CircleShape* particles;
        sf::Vector2f* acceleration;

    public:

        application(int particleCount = DEFAULT_PARTICLE_COUNTER){
            PARTICLE_COUNT = particleCount;
        };

        void clean(){
            ImGui::SFML::Shutdown();
            delete[] particles;
            delete[] acceleration;
        }

        void run(){

            auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Particle Life Project");
            sf::View view = window.getDefaultView();
            view.setCenter({640, 360});
            view.setSize({1280, 720});
            window.setFramerateLimit(100);
            if (!ImGui::SFML::Init(window))
                return;

            particles = new sf::CircleShape[PARTICLE_COUNT];
            acceleration =  new sf::Vector2f[PARTICLE_COUNT];

            SetParticle(particles, DEFAULT_PARTICLE_RADIUS);

            sf::Clock clock;
            while (window.isOpen())
            {
                while (const std::optional event = window.pollEvent())
                {
                    if(moving == false){
                        ImGui::SFML::ProcessEvent(window, *event);
                    }
                    EventHandler(event, view, window, oldPos, moving, paused);
                    
                }
                
                if(!paused){

                    updateForces(particles, acceleration);
                    updatePosition(particles, acceleration);
                    // CollisionUpdate(particles, velocity);

                    ImGui::SFML::Update(window, clock.restart());               
                    ImGui::Begin("ImGui SFML window");
                    ImGui::Button("+");
                    ImGui::SameLine(30.f);
                    ImGui::Button("-");
                    ImGui::End();

                }else{
                    ImGui::SFML::Update(window, clock.restart());
                    ImGui::Begin("ImGui SFML window");
                    ImGui::Text("Simulation paused!");
                    ImGui::End();
                }

                    
                window.clear();
                ImGui::SFML::Render(window);

                window.setView(view);
                for(int i=0; i<PARTICLE_COUNT; ++i){
                    window.draw(particles[i]);
                }

                window.display();
            }
            
        }

};