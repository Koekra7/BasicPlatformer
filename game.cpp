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
	
    std::vector<Rect> UIbuttons =  // ui buttons list
	{
		{350,250,85,30}, // #0 // start button
		{710, 477, 70, 20}, // #1 // reset button
		{50,110,90,20}, // #2 // upgrade speed button
		{50,142,90,20} // #3 // upgrade jump button
    };
	

    void Game::Init()
    {
        // Load the LDtk project
		ldtk_project.loadFromFile("assets/Test.ldtk"); // Load the LDtk project from the file
		loadLevel(0); // loading the first level  
		playerHealth = 100; // setting playerhealth
		ui = UI(screen, UIbuttons); // setting UI
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
		std::string elapsedTimeText = "Elapsed time: " + std::to_string(elapsed) + " seconds";
		std::string eggcounter = "Amount of eggs: " + std::to_string(coin.getCoins());

		
        // Clear the screen
		screen->Clear(0); // Clear the screen to black
		background.Draw(screen, 0, -250 ); // Draw the background to the screen

		screen->Print(const_cast<char*>(eggcounter.c_str()), 350, 10, 0xFFFFFF); // display the egg counter

		
		if (showUI == true && gameOver == false) // display the ui if the game has not started and player is not dead
		{
			ui.showMouse(true, screen, mouseX, mouseY); // show the mouse on the screen
			ui.pressedPlay(); // show the play button on the screen
			ui.draw(true);
			ui.checkButtons();
			UITextmap.Draw(screen, { 0, 0 });
			screen->Print(const_cast<char*>(finishTime.c_str()), 325, 200, 0xFFFFFF);
			startTime = now;
		}

		ui.makeUsable(player, coin); // giving the coins/eggs the ability to do something 

		if (ui.pressedPlay() && gameOver == false) // Check if the play button is pressed
		{
			showUI = false; // stopping the UI from displaying

			float Damage = damageObject.getDamage(level->getLayer("Entities"), player.GetPosition(), hitboxes, playerSize); // Get the damage from the hitbox layer
			playerHealth -= Damage; // setting the playerhealth

			player.addCollisions(true, hitboxes); //adds collision between player and hitboxes
			player.movePlayer(400, 20, true, 450, deltaTime); // Move the player

			// if the order looks wierd it is just so that everything dispalys correctly
			tilemap4.Draw(screen, { 0, 0 }); // Draw the tilemap4 to the screen
			tilemap.Draw(screen, { 0, 0 }); // Draw the tilemap to the screen
			coin.addCoin(screen, coins, player.GetPosition(), playerSize, eggsprite, deltaTime); // drawing the egg/coin
			player.Draw(screen, playersprite, false); // Draw the player to the screen
			tilemap2.Draw(screen, { 0, 0 }); // Draw the tilemap2 to the screen
			tilemap3.Draw(screen, { 0, 0 }); // Draw the tilemap3 to the screen

			a_finish.LevelFinish(screen, finishRect, false, playerSize, player.GetPosition().x, player.GetPosition().y); // making / drawing the finish
			
			
			if (startedTimer == false) //resseting the startTime for the timer to when the game starts
			{
				startTime = std::chrono::steady_clock::now();
				startedTimer = true;
			}
			
			screen->Print(const_cast<char*>(elapsedTimeText.c_str()), 200, 10, 0xFFFFFF); // display the timer at 200,10

			//setting some sprites
			eggsprite = eggsheet.get()->GetSprite(0); //setting the egg/coin sprite
			GameOver = GameOverSheet.get()->GetSprite(0);
			playersprite = charactersheet.get()->GetSprite(player.currentframe()); // setting the player sprite
			victory = victorySheet.get()->GetSprite(0);

			//for (const auto& box : hitboxes)
			//{
			//	screen->Box(box.x, box.y, box.x + box.w, box.y + box.h, 0xff0000); // Draw the hitbox to the screen
			//}
			//for (const auto& box : coins)
			//{
			//	screen->Box(box.x, box.y, box.x + box.w, box.y + box.h, 0xff00ff); // Draw the hitbox to the screen
			//}
			
			

			if (a_finish.isFinishHit() == currentLevel + 1 && currentLevel != 4) // resetting the playerposition when the finish is reached
			{
				loadLevel(currentLevel + 1);
				coin.resetCheck();
			}
			if (a_finish.isFinishHit() == currentLevel + 1 && currentLevel == 4) // stopping the timer
			{
				finishtime = elapsed;
				finishTime = elapsedTimeText;
				std::cout << elapsed << '\n';
			}
			if (playerHealth <= 0) // if player is dead stop the timer
			{
				finishtime = elapsed;
				finishTime = elapsedTimeText;
			}

			player.playerHealth(screen, { 20, 10, 100, 20 }, playerHealth);
		}


		
		if (a_finish.isFinishHit() == currentLevel + 1 && currentLevel == 4 && showUI == false) // when player finishes the game =)
		{
			victory.Draw(screen, { 375,200 }); // draw the victory
			ui.resetPlay(); // resetting some UI elements

			if (elapsed - finishtime >= 3) // if 3 seconds have passed reset the level
			{
				showUI = true;
				coin.resetCheck();
				loadLevel(0);
			}
		}

		if (playerHealth <= 0) //when player dies reset everything
		{
			gameOver = true;
			std::cout << "Game Over" << '\n';
			GameOver.Draw(screen, { 375,200 });

			loadLevel(0);
			ui.resetPlay();
			showUI = true;
			coin.resetCheck();
			coin.setCoins(0);
			player.SetSpeed(1, 1);

			if (elapsed - finishtime == 3) // if 3 seconds have passed reset gameOver and playerHealth
			{
				gameOver = false;
				playerHealth = 100;
			}
		}
		
			
		
    }


	const char* levelNames[] = { // setting all the levelNames
		"Level_0",
		"Level_1",
		"Level_2",
		"Level_3",
		"Level_4"
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

		const auto& UItextLayer = level->getLayer("UITextLayer");
		const auto& UItextSet = UItextLayer.getTileset();
		const auto& UItextSize = UItextLayer.getGridSize();

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

		//loading some spritesheets
		eggsheet = std::make_shared<SpriteSheet>("assets/Sprout Lands/objects/Egg_item.png", 16);
		GameOverSheet = std::make_shared<SpriteSheet>("assets/BigPixelTypefaceSets - PNG/BigPixelTypefaceSets - PNG/GameOver.png", 51);
        charactersheet = std::make_shared<SpriteSheet>("assets/Sprout Lands/Characters/Basic charakter Spritesheet.png", 48);
		victorySheet = std::make_shared<SpriteSheet>("assets/BigPixelTypefaceSets - PNG/BigPixelTypefaceSets - PNG/Victory.png", 83);

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

		auto spritesheet5 = std::make_shared<SpriteSheet>(ldtk_project.getFilePath().directory() + UItextSet.path, tileSet.tile_size); // Create a sprite sheet from the tileset
		UITextmap = TileMap(spritesheet5, gridSize.y, gridSize.x); // Create a tilemap with the sprite sheet and grid size

		for (const auto& tile : UItextLayer.allTiles()) // Loop through all the tiles in the layer
		{
			auto [x, y] = tile.getGridPosition(); // Get the grid position of the tile
			UITextmap(y, x) = tile.tileId; // Set the tile at the grid position to the tile ID
		}
	}

}

// -----------------------------------------------------------