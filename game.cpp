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
#include <chrono>



namespace Tmpl8
{
    // Declare an LDtk project and level
	ldtk::Project ldtk_project; // The LDtk project
	const ldtk::Level* level = nullptr; // The first level in the project
	//const ldtk::Layer* bg_layer = nullptr; // The background layer of the level
	

    // -----------------------------------------------------------
    // Initialize the application
    // -----------------------------------------------------------
    void Game::Init()
    {
        // Load the LDtk project
		ldtk_project.loadFromFile("assets/Test.ldtk"); // Load the LDtk project from the file
		loadLevel(0);
		playerHealth = 100;
		
    }

    // -----------------------------------------------------------
    // Close down application
    // -----------------------------------------------------------
    void Game::Shutdown()
    {
    }


	Sprite background(new Surface("assets/pixelBackground.jpg"), 1); // Create a background sprite

	void Game::Tick(float deltaTime) // deltaTime is the time between frames
    {
		deltaTime /= 1000; // Convert deltaTime to seconds


		// Calculate elapsed time
		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
		

		// Display elapsed seconds
		std::cout << "Elapsed time: " << elapsed << " seconds\n";
		std::string elapsedTimeText = "Elapsed time: " + std::to_string(elapsed) + " seconds";



        // Clear the screen
		screen->Clear(0); // Clear the screen to black
		background.Draw(screen, 0, -250 ); // Draw the background to the screen

		
		if (ui.pressedPlay(screen, true) != true && gameOver == false)
		{
			ui.showMouse(true, screen, mouseX, mouseY); // show the mouse on the screen
			ui.pressedPlay(screen, true); // show the play button on the screen
		}
		

		if (ui.pressedPlay(screen, true) && gameOver == false ) // Check if the play button is pressed
		{
			
			tilemap.Draw(screen, { 0, 0 }); // Draw the tilemap to the screen
			tilemap2.Draw(screen, { 0, 0 }); // Draw the tilemap2 to the screen
			tilemap3.Draw(screen, { 0, 0 }); // Draw the tilemap3 to the screen
			tilemap4.Draw(screen, { 0, 0 }); // Draw the tilemap4 to the screen
			
			if (startedTimer == false) 
			{
				startTime = std::chrono::steady_clock::now();
				startedTimer = true;
			}
			
			screen->Print(const_cast<char*>(elapsedTimeText.c_str()), 200, 10, 0xFFFFFF); // display the timer at 200,10

			eggsprite = eggsheet.get()->GetSprite(0); //setting the egg/coin sprite

			//for (const auto& box : hitboxes)
			//{
			//	screen->Box(box.x, box.y, box.x + box.w, box.y + box.h, 0xff0000); // Draw the hitbox to the screen
			//}
			//for (const auto& box : coins)
			//{
			//	screen->Box(box.x, box.y, box.x + box.w, box.y + box.h, 0xff00ff); // Draw the hitbox to the screen
			//}
			
			coin.addCoin(screen, coins, player.GetPosition(), playerSize, eggsprite, deltaTime); // drawing the egg/coin
			
			
			playersprite = charactersheet.get()->GetSprite(player.currentframe()); // setting the player sprite

			player.addCollisions(true, hitboxes); //adds collision between player and hitboxes
			player.movePlayer(400, 20, true, 450, deltaTime); // Move the player
			player.Draw(screen, playersprite, true); // Draw the player to the screen

			float Damage = damageObject.getDamage(level->getLayer("Entities"), player.GetPosition(), hitboxes, playerSize); // Get the damage from the hitbox layer
			std::cout << Damage << '\n'; // Print the damage to the console
			playerHealth -= Damage;

			if (playerHealth <= 0)
			{
				gameOver = true;
				std::cout << "Game Over" << '\n';
			}

			a_finish.LevelFinish(screen, finishRect, true, playerSize, player.GetPosition().x, player.GetPosition().y); // making / drawing the finish

			if (a_finish.isFinishHit() == currentLevel + 1 && currentLevel != 1) // resetting the playerposition when the finish is reached
			{
				loadLevel(currentLevel + 1);
				coin.resetCheck();
			}

			player.playerHealth(screen, { 20, 10, 100, 20 }, playerHealth);
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

		const auto& assetsLayer = level->getLayer("AssetsLayer"); // Get the assets layer from the level
		const auto& assetsSet = assetsLayer.getTileset(); // Get the tileset of the layer

		const auto& textLayer = level->getLayer("TextLayer"); // Get the assets layer from the level
		const auto& textSet = textLayer.getTileset(); // Get the tileset of the layer
		const auto& textSize = textLayer.getGridSize(); // Get the grid size of the layer

		const auto& lavaLayer = level->getLayer("Lava"); // Get the assets layer from the level
		const auto& lavaSet = lavaLayer.getTileset(); // Get the tileset of the layer

		const auto& entitiesLayer = level->getLayer("Entities"); // Get the entities layer from the level
		const auto& hitBoxLayer = entitiesLayer.getEntitiesByName("HitBox"); // Get the tileset of the layer
		const auto& coinLayer = entitiesLayer.getEntitiesByName("Coin_Spawn");
		
		const auto& finishLayer = entitiesLayer.getEntitiesByName("Finish"); // Get the tileset of the layer
		const auto& finish = entitiesLayer.getEntity(finishLayer[0].get().iid);

		finishRect = { finish.getPosition().x, finish.getPosition().y, finish.getSize().x, finish.getSize().y };

		int playerstartX = 8 * entitiesLayer.getEntitiesByName("Start_Pos")[0].get().getGridPosition().x;
		int playerstartY = 8 * entitiesLayer.getEntitiesByName("Start_Pos")[0].get().getGridPosition().y;
		 
		playerSize = { playerstartX, playerstartY, 16, 16 }; // setting the player size to 16x16
		player = Player(playerSize, 0, 0); // Create a player with a size of 16x16
		a_finish = Finish();

		hitboxes.clear(); // destruct the hitboxes
		for (const auto& entity : hitBoxLayer) // Loop through all the entities in the layer
		{
			hitboxes.push_back({ entity.get().getPosition().x, entity.get().getPosition().y, entity.get().getSize().x, entity.get().getSize().y }); // Add the entity to the hitboxes vector
		}
		coins.clear();
		for (const auto& entity : coinLayer)
		{
			coins.push_back({ entity.get().getPosition().x, entity.get().getPosition().y, entity.get().getSize().x, entity.get().getSize().y });
		}
		eggsheet = std::make_shared<SpriteSheet>("assets/Sprout Lands/objects/Egg_item.png", 16);

        charactersheet = std::make_shared<SpriteSheet>("assets/Sprout Lands/Characters/Basic charakter Spritesheet.png", 48);
		
		auto spritesheet = std::make_shared<SpriteSheet>(ldtk_project.getFilePath().directory() + tileSet.path, tileSet.tile_size); // Create a sprite sheet from the tileset
		tilemap = TileMap(spritesheet, gridSize.y, gridSize.x); // Create a tilemap with the sprite sheet and grid size

		for (const auto& tile : tilesLayer.allTiles()) { // Loop through all the tiles in the layer
			auto [x, y] = tile.getGridPosition(); // Get the grid position of the tile
			tilemap(y, x) = tile.tileId; // Set the tile at the grid position to the tile ID
		}

		auto spritesheet2 = std::make_shared<SpriteSheet>(ldtk_project.getFilePath().directory() + assetsSet.path, tileSet.tile_size); // Create a sprite sheet from the tileset
		tilemap2 = TileMap(spritesheet2, gridSize.y, gridSize.x); // Create a tilemap with the sprite sheet and grid size

		for (const auto& tile : assetsLayer.allTiles()) // Loop through all the tiles in the layer
		{
			auto [x, y] = tile.getGridPosition(); // Get the grid position of the tile
			tilemap2(y, x) = tile.tileId; // Set the tile at the grid position to the tile ID
		}

		auto spritesheet3 = std::make_shared<SpriteSheet>(ldtk_project.getFilePath().directory() + textSet.path, textSet.tile_size); // Create a sprite sheet from the tileset
		tilemap3 = TileMap(spritesheet3, textSize.y, textSize.x); // Create a tilemap with the sprite sheet and grid size

		for (const auto& tile : textLayer.allTiles()) // Loop through all the tiles in the layer
		{
			auto [x, y] = tile.getGridPosition(); // Get the grid position of the tile
			tilemap3(y, x) = tile.tileId; // Set the tile at the grid position to the tile ID
		}

		auto spritesheet4 = std::make_shared<SpriteSheet>(ldtk_project.getFilePath().directory() + lavaSet.path, tileSet.tile_size); // Create a sprite sheet from the tileset
		tilemap4 = TileMap(spritesheet4, gridSize.y, gridSize.x); // Create a tilemap with the sprite sheet and grid size

		for (const auto& tile : lavaLayer.allTiles()) // Loop through all the tiles in the layer
		{
			auto [x, y] = tile.getGridPosition(); // Get the grid position of the tile
			tilemap4(y, x) = tile.tileId; // Set the tile at the grid position to the tile ID
		}
	}

}

// -----------------------------------------------------------