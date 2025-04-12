#include "game.h"
#include "SpriteSheet.h"
#include "surface.h"
#include "Player.h"
#include "Entities.h"
#include "UI.h"

#include <cstdio>
#include <iostream>
#include <LDtkLoader/Project.hpp>
#include <SDL.h>
#include <string>
#include <vector>
#include <Windows.h>



namespace Tmpl8
{
    // Declare an LDtk project and level
	ldtk::Project ldtk_project; // The LDtk project
	const ldtk::Level* level = nullptr; // The first level in the project

	const ldtk::Layer* bg_layer = nullptr; // The background layer of the level

    // -----------------------------------------------------------
    // Initialize the application
    // -----------------------------------------------------------
    void Game::Init()
    {
        // Load the LDtk project
		ldtk_project.loadFromFile("assets/Test.ldtk"); // Load the LDtk project from the file
		loadLevel(0);
		playerSize = { 100, 100, 20, 20 }; // setting the player size to 20x20
		player = Player(playerSize, 0, 0); // Create a player 
		playerHealth = 100;
    }

    // -----------------------------------------------------------
    // Close down application
    // -----------------------------------------------------------
    void Game::Shutdown()
    {
    }


    
	void Game::Tick(float deltaTime) // deltaTime is the time between frames
    {
		deltaTime /= 1000; // Convert deltaTime to seconds

        // Clear the screen
		screen->Clear(0); // Clear the screen to black
		
		if (ui.pressedPlay(screen, true) != true && gameOver == false)
		{
			ui.showMouse(true, screen, mouseX, mouseY); // show the mouse on the screen
			ui.pressedPlay(screen, true); // show the play button on the screen
		}
		

		if (ui.pressedPlay(screen, true) && gameOver == false ) // Check if the play button is pressed
		{
			
			tilemap.Draw(screen, { 0, 0 }); // Draw the tilemap to the screen

			for (const auto& box : hitboxes)
			{
				screen->Box(box.x, box.y, box.x + box.w, box.y + box.h, 0xff0000); // Draw the hitbox to the screen
			}

			player.addCollisions(true, hitboxes); //adds collision between player and hitboxes
			player.movePlayer(400, 20, true, 450, deltaTime); // Move the player
			player.Draw(screen); // Draw the player to the screen

			float Damage = damageObject.getDamage(level->getLayer("Entities"), player.GetPosition(), hitboxes, playerSize); // Get the damage from the hitbox layer
			std::cout << Damage << '\n'; // Print the damage to the console
			playerHealth -= Damage;

			if (playerHealth <= 0)
			{
				gameOver = true;
				std::cout << "Game Over" << '\n';
			}


			a_finish.LevelFinish(screen, finishRect, true, playerSize, player.GetPosition().x, player.GetPosition().y); // making / drawing the finish

			if (a_finish.isFinishHit() == 1 && currentLevel != 1) // resetting the playerposition when the finish is reached
			{
				player.setPlayerPos(100, 100);
				loadLevel(currentLevel + 1);
			}

			player.playerHealth(screen, { 20, 10, 100, 20 }, playerHealth);

			//std::cout << currentLevel << '\n';
		}

		
    }

	const char* levelNames[] = { // all the levels
		"Level_0",
		"Level_1"
	};


	void Game::loadLevel(int id) // change to using names
	{
		auto& world = ldtk_project.getWorld(); // Get the world from the project
		level = &world.getLevel(levelNames[id]); // Get the first level in the world

		currentLevel = id;

		const auto& tilesLayer = level->getLayer("Ground"); // Get the tiles layer from the level
		const auto& gridSize = tilesLayer.getGridSize(); // Get the grid size of the layer
		const auto& tileSet = tilesLayer.getTileset(); // Get the tileset of the layer

		const auto& entitiesLayer = level->getLayer("Entities"); // Get the entities layer from the level
		const auto& hitBoxLayer = entitiesLayer.getEntitiesByName("HitBox"); // Get the tileset of the layer
		

		const auto& finishLayer = entitiesLayer.getEntitiesByName("Finish"); // Get the tileset of the layer
		const auto& finish = entitiesLayer.getEntity(finishLayer[0].get().iid);

		finishRect = { finish.getPosition().x, finish.getPosition().y, finish.getSize().x, finish.getSize().y };

		playerSize = { 100, 100, 20, 20 }; // setting the player size to 20x20
		player = Player(playerSize, 0, 0); // Create a player with a size of 20x20
		a_finish = Finish();

		hitboxes.clear(); // destruct the hitboxes
		for (const auto& entity : hitBoxLayer) // Loop through all the entities in the layer
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

}

// -----------------------------------------------------------