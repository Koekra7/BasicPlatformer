#pragma once
#include "TileMap.hpp"
#include "Player.h"
#include "Entities.h"
#include "UI.h"
#include <iostream>
#include <LDtkLoader/Project.hpp>
#include <vector>



namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove(int x, int y) { mouseX += x, mouseY += y; }
	void KeyUp(int key) { player.keyUp(key); }
	void KeyDown(int key) { player.keyDown(key); } // print the mouse position to the console}
	
	void loadLevel(int id);
private:
	Surface* screen;
	Surface* tiles;
	ldtk::Project project; 

	TileMap tilemap;
	Player player;
	Finish a_finish;

	UI ui;

	int mouseX, mouseY;

	float playerX;
	float playerY;
	float playerHealth;

	std::vector<Rect> hitboxes;

	Rect playerSize;
	Rect startPosition;
	Rect finishRect;

	int currentLevel;
	
};

}; // namespace Tmpl8