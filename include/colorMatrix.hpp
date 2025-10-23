#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief Initializes the color matrix used for color manipulation.
 */
void init_colorMatrix(float colorMatrix[][9]){
    for(int i=0; i<9; ++i){
        for(int j=0; j<9; ++j){
            if(i == j){
                colorMatrix[i][j] = 1.f;
            }
            else{
                colorMatrix[i][j] = 0.f;
            }
        }
    }

    colorMatrix[0][0] = 8.f;
    colorMatrix[1][1] = -1.f;
    colorMatrix[2][2] = 10.f;

    colorMatrix[0][1] = -10.f;
    colorMatrix[1][0] = -10.f;

    colorMatrix[1][2] = -10.f;
    colorMatrix[2][1] = -10.f;

    colorMatrix[0][2] = -1.f;
    colorMatrix[2][0] = +1.f;
}

/**
 * @brief Converts a SFML color to an integer representation.
 * 
 * @param color The SFML color to convert.
 * @return An integer representing the color.
 */
int colorToInt(sf::Color color){
    switch(color.toInteger()){
        case sf::Color::Red.toInteger():
            return 0;
            break;
        case sf::Color::Green.toInteger():
            return 1;
            break;
        case sf::Color::Blue.toInteger():
            return 2;
            break;
        case sf::Color::Magenta.toInteger():
            return 3;
            break;
        case sf::Color::Cyan.toInteger():
            return 4;
            break;
        case sf::Color::Yellow.toInteger():
            return 5;
            break;
        case sf::Color::White.toInteger():
            return 6;
            break;
        case sf::Color::Black.toInteger():
            return 7;
            break;
        case sf::Color::Transparent.toInteger():
            return 8;
            break;
        default:
            return 0;
            break;
    }
}

/**
 * @brief Converts an integer representation to a SFML color.
 * 
 * @param color The integer representing the color.
 * @return The corresponding SFML color.
 */
sf::Color intToColor(int color){
    switch(color){
        case 0:
            return sf::Color::Red;
            break;
        case 1:
            return sf::Color::Green;
            break;
        case 2:
            return sf::Color::Blue;
            break;
        case 3:
            return sf::Color::Magenta;
            break;
        case 4:
            return sf::Color::Cyan;
            break;
        case 5:
            return sf::Color::Yellow;
            break;
        case 6:
            return sf::Color::White;
            break;
        case 7:
            return sf::Color::Black;
            break;
        case 8:
            return sf::Color::Transparent;
            break;
        default:
            return sf::Color(255, 255, 255, 255);
    }
}
