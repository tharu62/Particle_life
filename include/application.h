#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include "eventHandler.hpp"


class application {
    public:

        application(int particleCount);
        ~application();

        void run();

};