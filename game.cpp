#include "game.h"
#include "SpriteSheet.h"
#include "surface.h"
#include "Player.h"

#include <cstdio>
#include <iostream>
#include <LDtkLoader/Project.hpp>
#include <SDL.h>
#include <string>
#include <vector>
#include <Windows.h>



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

		const auto& entitiesLayer = level1->getLayer("Entities"); // Get the entities layer from the level
		const auto& entitiesSet = entitiesLayer.getEntitiesByName("HitBox"); // Get the tileset of the layer
		const auto& entitie = entitiesLayer.getEntity(entitiesSet[0].get().iid); // Get the entity by ID

		playerSize = { 0, 0, 20, 20 }; // setting the player size to 20x20
		player = Player(playerSize, 100, 100, 0, 0); // Create a player with a size of 20x20
		

		for (const auto& entity : entitiesSet) // Loop through all the entities in the layer
		{
			hitboxes.push_back({ entity.get().getPosition().x, entity.get().getPosition().y, entity.get().getSize().x, entity.get().getSize().y }); // Add the entity to the hitboxes vector
		}

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


    
	void Game::Tick(float deltaTime) // deltaTime is the time between frames
    {
        // Clear the screen
		screen->Clear(0); // Clear the screen to black

		tilemap.Draw(screen, { 0, 0 }); // Draw the tilemap to the screen

		for (const auto& box : hitboxes)
		{
			screen->Box(box.x, box.y, box.x + box.w, box.y + box.h, 0xff0000); // Draw the hitbox to the screen
		}

		player.Draw(screen, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, 1, 2, 0.05, true, 20, hitboxes);

    }

}

// -----------------------------------------------------------