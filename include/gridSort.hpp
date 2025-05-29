#pragma once


#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

extern float maximumDistance;

struct Node{
    sf::Vector2f center;
    std::vector<int> particles;
};

/**
 * @brief Initializes the grid with nodes based on the specified width, height, and grid size.
 * 
 * @param grid The grid of nodes to be initialized.
 * @param width The width of the area to cover with the grid.
 * @param height The height of the area to cover with the grid.
 * @param gridSize The size of each grid cell.
 */
void initGrid(std::vector<Node> &grid, int width, int height, float gridSize)
{
    for(int i=0; i<grid.size(); ++i){
        grid[i].particles.clear();
    }
    grid.clear();
    
    
    float gridWidth = width / gridSize;
    float gridHeight = height / gridSize;

    for(int i=0; i<gridWidth-1; ++i){
        for(int j=0; j<gridHeight; ++j){
            grid.push_back(Node());
            grid.back().center = {i*gridSize + gridSize/2 - width/4, j*gridSize + gridSize/2 - height/4};
        }
    }
}

/**
 * @brief Cleans the grid by clearing the particles in each node.
 * 
 * @param grid The grid of nodes to be cleaned.
 */
void cleanGrid(std::vector<Node> &grid)
{
    for(int i=0; i<grid.size(); ++i){
        grid[i].particles.clear();
    }
}

/**
 * @brief Finds the index of the node in the grid that contains the given position.
 * 
 * @param grid The grid of nodes.
 * @param position The position to check.
 * @param gridSize The size of each grid cell.
 * @return The index of the node containing the position, or -1 if not found.
 */
int findNodeFromGrid(std::vector<Node> &grid, sf::Vector2f position, int gridSize)
{
    for(int i=0; i<grid.size(); ++i){
        if(position.x < (grid[i].center.x + gridSize/2) && position.x >= (grid[i].center.x - gridSize/2) && position.y < (grid[i].center.y + gridSize/2) && position.y >= (grid[i].center.y - gridSize/2)){
            return i;
        }
    }
    return -1;
}


void insertGrid(sf::CircleShape* particles, sf::Vector2f* acceleration, std::vector<Node> &grid, int PARTICLE_COUNT, int gridSize)
{
    for(int i=0; i<PARTICLE_COUNT; ++i){

        /******************************************** Alternative insertion method ****************************************/
        // for(int j=0; j<grid.size(); ++j){
        //     if(particles[i].getPosition().x < (grid[j].center.x + gridSize/2) && particles[i].getPosition().x >= (grid[j].center.x - gridSize/2) && particles[i].getPosition().y < (grid[j].center.y + gridSize/2) && particles[i].getPosition().y >= (grid[j].center.y - gridSize/2)){
        //         grid[j].particles.push_back(i);
        //         continue;
        //     }
        // } 
        /******************************************************************************************************************/

        int j = findNodeFromGrid(grid, particles[i].getPosition(), gridSize);
        if(j != -1){
            grid[j].particles.push_back(i);
        }
    }

}