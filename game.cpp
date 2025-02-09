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

		const auto& tilesLayer = level1->getLayer("Ground");
        const auto& gridSize = tilesLayer.getGridSize();
        const auto& tileSet = tilesLayer.getTileset();
        
		Surface Tiles("assets/Sprout Lands/Tilesets/Hills.png");

        int TilePosX = 1;
        int TilePosY = 1;
		int TileMapSizeX = Tiles.GetWidth(); //getting the width of the full tilemap
		int TileMapSizeY = Tiles.GetHeight(); //getting the height of the full tilemap
        int TilePosOffsetY = 0;
		int TilePosOffsetX = 0;
        
        for (int Tile_PosY = 1; Tile_PosY <= TileMapSizeY / 16; Tile_PosY++) {
             
            for (int Tile_PosX = TilePosX; Tile_PosX <= TileMapSizeX / 16; Tile_PosX++) {
				TilePosOffsetX = 16 * Tile_PosX;  // setting the X position to the next tile
				std::cout << TilePosOffsetX << std::string(" X") << std::endl; // printing the X position
                TilePosX = Tile_PosX; 
            }

			TilePosX = 0; // resetting the X position to 0
			TilePosOffsetY = 16 * Tile_PosY; // setting the Y position to the next row
			std::cout << TilePosOffsetY << std::string(" Y") << std::endl; // printing the Y position
			TilePosY = Tile_PosY; 
		}
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