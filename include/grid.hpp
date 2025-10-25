#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

extern float maximumDistance;
sf::Vector2f topLeftgridCorner;
sf::Vector2f topRightgridCorner;
sf::Vector2f bottomLeftgridCorner;
sf::Vector2f bottomRightgridCorner;

struct Node{
    sf::Vector2f center;
    std::vector<int> particles;
};

/**
 * @brief Initializes the grid with nodes based on the specified width, height, and grid size.
 * 
 * @param grid The grid of nodes to be initialized.
 * @param width_unit is the width of the area to cover with the grid in number of grid cells.
 * @param height_unit is the height of the area to cover with the grid in number of grid cells.
 * @param gridSize The size of each grid cell.
 */
void initGrid(std::vector<Node> &grid, int width_unit, int height_unit, float gridSize, sf::Vector2f centerPoint = sf::Vector2f(640.f, 320.f))
{
    for(int i=0; i<grid.size(); ++i){
        grid[i].particles.clear();
    }
    grid.clear();

    // uncenterd grid
    // for(int i=0; i<width_unit; ++i){
    //     for(int j=0; j<height_unit; ++j){
    //         grid.push_back(Node());
    //         grid.back().center = {(float)i*gridSize + gridSize/2, (float)j*gridSize + gridSize/2};
    //     }
    // }

    float totalWidth  = width_unit  * gridSize;
    float totalHeight = height_unit * gridSize;

    // top-left corner so the whole grid is centered on centerPoint
    sf::Vector2f topLeft = { centerPoint.x - totalWidth * 0.5f, centerPoint.y - totalHeight * 0.5f };
    sf::Vector2f topRight = { centerPoint.x + totalWidth * 0.5f, centerPoint.y - totalHeight * 0.5f };
    sf::Vector2f bottomLeft = { centerPoint.x - totalWidth * 0.5f, centerPoint.y + totalHeight * 0.5f };
    sf::Vector2f bottomRight = { centerPoint.x + totalWidth * 0.5f, centerPoint.y + totalHeight * 0.5f };

    topLeftgridCorner = topLeft;
    topRightgridCorner = topRight;
    bottomLeftgridCorner = bottomLeft;
    bottomRightgridCorner = bottomRight;

    for (int i = 0; i < width_unit; ++i) {
        for (int j = 0; j < height_unit; ++j) {
            grid.push_back(Node());
            grid.back().center = {
                topLeft.x + i * gridSize + gridSize * 0.5f,
                topLeft.y + j * gridSize + gridSize * 0.5f
            };
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
    gridSize /= 2;
    for(int i=0; i<grid.size(); ++i){
        if(position.x < (grid[i].center.x + gridSize) && position.x >= (grid[i].center.x - gridSize) && position.y < (grid[i].center.y + gridSize) && position.y >= (grid[i].center.y - gridSize)){
            return i;
        }
    }
    return -1;
}


/**
 * @brief Inserts particles into the appropriate nodes in the grid based on their positions.
 */
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