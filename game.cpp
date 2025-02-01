#include "game.h"
#include "surface.h"
#include <cstdio>
#include <iostream>
#include <LDtkLoader/Project.hpp>
#include <SDL.h>



namespace Tmpl8
{
    // Declare global variables for SDL
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* tileset_texture = nullptr;

    // Declare an LDtk project and level
    ldtk::Project ldtk_project;
    const ldtk::Level* level1 = nullptr;
    const ldtk::Layer* bg_layer = nullptr;

    // -----------------------------------------------------------
    // Initialize the application
    // -----------------------------------------------------------
    void Game::Init()
    {
        // Load the LDtk project
        ldtk_project.loadFromFile("assets/Test.ldtk");
        auto& world = ldtk_project.getWorld();

        level1 = &world.getLevel(0);
        bg_layer = &level1->getLayer("Ground");
    }



    // -----------------------------------------------------------
    // Close down application
    // -----------------------------------------------------------
    void Game::Shutdown()
    {
    }

    // -----------------------------------------------------------
    // Update and render the game
    // -----------------------------------------------------------
    void Game::Tick(float deltaTime)
    {
        // Clear the screen
        screen->Clear(0);

        // Render the level
        for (const auto& tile : bg_layer->allTiles()) {
            auto [x, y] = tile.getPosition();
            auto [_x, _y, w, h] = tile.getTextureRect();

            screen->Bar(x, y, x + w, y + h, 0xFFFFFF);
        }
    }

}

// -----------------------------------------------------------