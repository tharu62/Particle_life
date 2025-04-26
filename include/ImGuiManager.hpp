#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

#include "setUp.hpp"


void manageImGui(sf::RenderWindow &window, sf::Clock &clock, bool &opened, sf::CircleShape* particles, int framerate, int &PARTICLE_COUNT, int &PARTICLE_RADIUS, float &STRENGHT, bool &resetted){
    ImGui::SFML::Update(window, clock.restart());               
    if(ImGui::Begin("ImGui SFML window", &opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize)){
        
        ImGui::Text("FPS: %d", framerate);

        ImGui::Text("Particle count: %d", PARTICLE_COUNT);
        ImGui::SameLine(170.f);
        if(ImGui::Button("Reset")){
            resetted = true;
        }
        
        ImGui::Text("Particle radius: %d", PARTICLE_RADIUS);
        ImGui::SameLine(171.f);
        if(ImGui::Button("+##1")){
            PARTICLE_RADIUS++;
            for(int i=0; i<PARTICLE_COUNT; ++i){
                particles[i].setRadius(PARTICLE_RADIUS);
            }
        };
        ImGui::SameLine(197.f);
        if(ImGui::Button("-##2")){
            if(PARTICLE_RADIUS > 1){
                PARTICLE_RADIUS--;
                for(int i=0; i<PARTICLE_COUNT; ++i){
                    particles[i].setRadius(PARTICLE_RADIUS);
                }
            }
        };
        
        ImGui::Text("Strength: %f", STRENGHT);
        ImGui::SameLine(171.f);
        if(ImGui::Button("+##3")){
            STRENGHT += 1.f;
        };
        ImGui::SameLine(197.f);
        if(ImGui::Button("-##4")){
            if(STRENGHT > 0.f){
                STRENGHT -= 1.f;
            }
        };

    } 

    ImGui::End();
}