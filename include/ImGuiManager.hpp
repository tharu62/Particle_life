#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "setUp.hpp"

/**
 * @brief Manages the ImGui window for particle simulation settings.
 */
void manageImGui(sf::RenderWindow &window, sf::Clock &clock, bool &opened, sf::CircleShape* particles, int framerate, int &PARTICLE_COUNT, 
    int &PARTICLE_RADIUS, float &STRENGHT, float &REPULSION_FACTOR, bool &resetted, bool &gridOn, float (*colorMatrix)[9]){ 

    // set initial window size (width x height) once
    ImGui::SetNextWindowSize(ImVec2(348.0f, 500.0f), ImGuiCond_Once);

    if(ImGui::Begin("ImGui SFML window", &opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove)){
        
        ImGui::Text("FPS %d", framerate);

        ImGui::Text("Particle count %d", PARTICLE_COUNT);
        ImGui::SameLine(170.f);
        if(ImGui::Button("Reset")){
            resetted = true;
        }
        
        ImGui::Text("Particle radius %d", PARTICLE_RADIUS);
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
        
        ImGui::Text("Strength %f", STRENGHT);
        ImGui::SameLine(171.f);
        if(ImGui::Button("+##3")){
            STRENGHT += 10.f;
        };
        ImGui::SameLine(197.f);
        if(ImGui::Button("-##4")){
            if(STRENGHT > 10.f){
                STRENGHT -= 10.f;
            }
            else{
                STRENGHT = 0.f;
            }
        };

        ImGui::Text("Repulsion %f", REPULSION_FACTOR);
        ImGui::SameLine(171.f);
        if(ImGui::Button("+##5")){
            REPULSION_FACTOR += 10.f;
        };
        ImGui::SameLine(197.f);
        if(ImGui::Button("-##6")){
            if(REPULSION_FACTOR > 10.f){
                REPULSION_FACTOR -= 10.f;
            }
            else{
                REPULSION_FACTOR = 0.f;
            }
        };

        ImGui::Text("Color Matrix Settings:");
        
        // fixed cell size version (aligned using absolute positions relative to child origin)
        float cellSize = 30.0f;
        float cellPadding = 1.0f;
        const int totalCellsPerSide = 10; // 9 + 1 reference

        // Start a child window to contain the grid (fixed size)
        ImGui::BeginChild("ColorMatrix", ImVec2((totalCellsPerSide * (cellSize + cellPadding) + 23), (totalCellsPerSide * (cellSize + cellPadding))), true);
        
        // Get child origin in screen coordinates
        ImVec2 origin = ImGui::GetCursorScreenPos();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        
        // Top-left corner (empty)
        draw_list->AddRectFilled(origin, 
            ImVec2(origin.x + cellSize, origin.y + cellSize), 
            IM_COL32(50, 50, 50, 255));
        draw_list->AddRect(origin, ImVec2(origin.x + cellSize, origin.y + cellSize), IM_COL32(100,100,100,255));
        
        // Top reference cells
        for(int c = 0; c < 9; ++c) {
            ImVec2 refPos = ImVec2(origin.x + (c + 1) * (cellSize + cellPadding), origin.y);
            sf::Color color = intToColor(c);
            draw_list->AddRectFilled(refPos,
                ImVec2(refPos.x + cellSize, refPos.y + cellSize),
                IM_COL32(color.r, color.g, color.b, color.a));
            draw_list->AddRect(refPos,
                ImVec2(refPos.x + cellSize, refPos.y + cellSize),
                IM_COL32(100, 100, 100, 255));
        }

        // Left reference cells and main grid (use absolute positions relative to origin)
        for(int r = 0; r < 9; ++r) {
            // left reference
            ImVec2 leftPos = ImVec2(origin.x, origin.y + (r + 1) * (cellSize + cellPadding));
            sf::Color leftColor = intToColor(r);
            draw_list->AddRectFilled(leftPos,
                ImVec2(leftPos.x + cellSize, leftPos.y + cellSize),
                IM_COL32(leftColor.r, leftColor.g, leftColor.b, leftColor.a));
            draw_list->AddRect(leftPos,
                ImVec2(leftPos.x + cellSize, leftPos.y + cellSize),
                IM_COL32(100, 100, 100, 255));

            // nine main cells in this row
            for(int c = 0; c < 9; ++c) {
                ImVec2 cellPos = ImVec2(origin.x + (c + 1) * (cellSize + cellPadding), origin.y + (r + 1) * (cellSize + cellPadding));
                
                // Draw black background for every cell
                draw_list->AddRectFilled(cellPos,
                    ImVec2(cellPos.x + cellSize, cellPos.y + cellSize),
                    IM_COL32(0, 0, 0, 255));
                draw_list->AddRect(cellPos,
                    ImVec2(cellPos.x + cellSize, cellPos.y + cellSize),
                    IM_COL32(100, 100, 100, 255));

                // Place InputFloat exactly inside the cell
                ImGui::SetCursorScreenPos(cellPos);
                ImGui::PushID(r * 9 + c);
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
                ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));

                float value = colorMatrix[r][c];
                ImU32 valueColor;
                if (value < 0) valueColor = IM_COL32(255, 0, 0, 255);
                else if (value > 0) valueColor = IM_COL32(0, 255, 0, 255);
                else valueColor = IM_COL32(128, 128, 128, 255);

                ImGui::PushStyleColor(ImGuiCol_Text, valueColor);
                ImGui::SetNextItemWidth(cellSize);
                ImGui::InputFloat("##value", &colorMatrix[r][c], 0.0f, 0.0f, "%.1f");
                ImGui::PopStyleColor(2);
                ImGui::PopStyleVar();
                ImGui::PopID();
            }
        }
        
        // restore cursor inside child (place after the block)
        ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + (totalCellsPerSide * (cellSize + cellPadding))));
        
        ImGui::EndChild();

        ImGui::Checkbox("Show Grid", &gridOn);
        
    } 

    ImGui::End();
}