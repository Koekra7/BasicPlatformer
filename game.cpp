#include "game.h"
#include "surface.h"
#include <cstdio> //printf

#include <LDtkLoader/Project.hpp>



namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		
		

		ldtk::Project ldtk_project;
		ldtk_project.loadFromFile("my_project.ldtk");

		const auto& world = ldtk_project.getWorld("World");
		const auto& level1 = world.getLevel("Level_0");
		const auto& bg_layer = level1.getLayer("World");
		for (const auto& tile : bg_layer.allTiles()){}
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	void Game::Tick(float deltaTime)
	{
		
	}

};
