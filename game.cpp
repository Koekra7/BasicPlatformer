#include "game.h"
#include "surface.h"
#include <cstdio>
#include <iostream>
#include <LDtkLoader/Project.hpp>
#include <SDL.h>
#include <string>
#include "SpriteSheet.h"



namespace Tmpl8
{
    // Declare global variables for SDL
	SDL_Window* window = nullptr; // The window that is being rendered to
	SDL_Renderer* renderer = nullptr; // The renderer that is rendering to the window
	SDL_Texture* tileset_texture = nullptr; // The texture that contains the tileset

    // Declare an LDtk project and level
	ldtk::Project ldtk_project; // The LDtk project
	const ldtk::Level* level1 = nullptr; // The first level in the project
	const ldtk::Layer* bg_layer = nullptr; // The background layer of the level

    // -----------------------------------------------------------
    // Initialize the application
    // -----------------------------------------------------------
    void Game::Init()
    {
        // Load the LDtk project
		ldtk_project.loadFromFile("assets/Test.ldtk"); // Load the LDtk project from the file
		auto& world = ldtk_project.getWorld(); // Get the world from the project

		level1 = &world.getLevel(0); // Get the first level in the world

		const auto& tilesLayer = level1->getLayer("Ground"); // Get the tiles layer from the level
		const auto& gridSize = tilesLayer.getGridSize(); // Get the grid size of the layer
		const auto& tileSet = tilesLayer.getTileset(); // Get the tileset of the layer
        
		auto spritesheet = std::make_shared<SpriteSheet>(ldtk_project.getFilePath().directory() + tileSet.path, tileSet.tile_size); // Create a sprite sheet from the tileset
		tilemap = TileMap(spritesheet, gridSize.y, gridSize.x); // Create a tilemap with the sprite sheet and grid size

		for (const auto& tile : tilesLayer.allTiles()) { // Loop through all the tiles in the layer
			auto [x, y] = tile.getGridPosition(); // Get the grid position of the tile
			tilemap(y, x) = tile.tileId; // Set the tile at the grid position to the tile ID
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
	void Game::Tick(float deltaTime) // deltaTime is the time between frames
    {
        // Clear the screen
		screen->Clear(0); // Clear the screen to black

		tilemap.Draw(screen, { 0, 0 }); // Draw the tilemap to the screen
		
        
    }

}

// -----------------------------------------------------------