#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"


void EventHandler(std::optional<sf::Event> event, sf::View &view, sf::RenderWindow &window, sf::Vector2f &oldPos, bool &moving, bool &paused){

    if(const auto* PkeyPressed = event->getIf<sf::Event::KeyPressed>()){
        if(PkeyPressed->scancode == sf::Keyboard::Scan::P){
            paused = !paused;
        }
    }

    if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>()){
        
        if(mouseWheelScrolled->delta > 0){
            view.zoom(0.5);
            // std::cout << "zoom down" << std::endl;

        }else{
            view.zoom(2);
            // std::cout << "zoom up" << std::endl;
        }
    }

    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
        moving = true;
        oldPos = window.mapPixelToCoords(sf::Vector2i(mouseButtonPressed->position.x, mouseButtonPressed->position.y));
    }

    if(const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()){
        moving = false;
    }

    if(const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()){
        
        if (moving){
            const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(mouseMoved->position.x, mouseMoved->position.y));
            const sf::Vector2f deltaPos = oldPos - newPos;
            view.setCenter(view.getCenter() + deltaPos);
            window.setView(view);
            oldPos = window.mapPixelToCoords(sf::Vector2i(mouseMoved->position.x, mouseMoved->position.y));
        }
    }
    
    if (event->is<sf::Event::Closed>()){
        window.close();
    }

}
