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
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return;
        }

        // Create an SDL window
        window = SDL_CreateWindow("LDtk Level", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        // Create an SDL renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return;
        }

        // Load the LDtk project
        ldtk_project.loadFromFile("D:/School Apps/Visual Studio/BasicPlatformer/assets/Test.ldtk");

        // Iterate through available worlds and find the correct one
        const ldtk::World* world = nullptr;
        for (const auto& w : ldtk_project.allWorlds()) {
            if (w.getName() == "World") {
                world = &w;
                break;
            }
        }

        if (!world) {
            std::cerr << "World not found in LDtk project" << std::endl;
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return;
        }

        level1 = &world->getLevel("BestLevel");
        bg_layer = &level1->getLayer("Ground");

        // Load the tileset BMP
        SDL_Surface* bmp_surface = SDL_LoadBMP(("assets/" + bg_layer->getTileset().path).c_str());
        if (!bmp_surface) {
            std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return;
        }

        // Create an SDL texture from the BMP surface
        tileset_texture = SDL_CreateTextureFromSurface(renderer, bmp_surface);
        SDL_FreeSurface(bmp_surface);
        if (!tileset_texture) {
            std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return;
        }
    }



    // -----------------------------------------------------------
    // Close down application
    // -----------------------------------------------------------
    void Game::Shutdown()
    {
        SDL_DestroyTexture(tileset_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // -----------------------------------------------------------
    // Update and render the game
    // -----------------------------------------------------------
    void Game::Tick(float deltaTime)
    {
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the level
        for (const auto& tile : bg_layer->allTiles()) {
            auto tile_position = tile.getPosition();
            auto tile_texture_rect = tile.getTextureRect();

            // Destination rect on the window
            SDL_Rect dest = { tile_position.x, tile_position.y, bg_layer->getCellSize(), bg_layer->getCellSize() };

            // Source texture rect from the tileset
            SDL_Rect src = { tile_texture_rect.x, tile_texture_rect.y, tile_texture_rect.width, tile_texture_rect.height };

            // Get tile flips
            int flip = (tile.flipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) | (tile.flipY ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);

            // Draw the tile
            SDL_RenderCopyEx(renderer, tileset_texture, &src, &dest, 0, nullptr, (SDL_RendererFlip)flip);
        }
        SDL_RenderPresent(renderer);
    }

}

// -----------------------------------------------------------