#pragma once
#include "TileMap.hpp"
#include "Player.h"
#include "Entities.h"
#include "UI.h"
#include <iostream>
#include <LDtkLoader/Project.hpp>
#include <vector>
#include <chrono>



namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button) { ui.mouseUp(button); }
	void MouseDown(int button) { ui.mouseDown(button); }
	void MouseMove(int x, int y) { mouseX += x, mouseY += y; }
	void KeyUp(int key) { player.keyUp(key); }
	void KeyDown(int key) { player.keyDown(key); } // print the mouse position to the console}
	
	void loadLevel(int id);
private:
	Surface* screen;
	Surface* tiles;
	ldtk::Project project; 

	TileMap tilemap;
	TileMap tilemap2;
	TileMap tilemap3;
	TileMap tilemap4;
	TileMap UITextmap;
	TileMap charactermap;

	Player player;
	Finish a_finish;

	DamageObject damageObject;

	UI ui;

	int mouseX, mouseY;

	float playerX;
	float playerY;
	int playerHealth;

	std::shared_ptr<SpriteSheet> charactersheet;
	std::shared_ptr<SpriteSheet> eggsheet;
	std::shared_ptr<SpriteSheet> GameOverSheet;
	std::shared_ptr<SpriteSheet> victorySheet;

	std::vector<Rect> hitboxes;
	std::vector<Rect> coins;

	Rect playerSize;
	Rect startPosition;
	Rect finishRect;

	bool gameOver = false;
	bool showUI = true;
	int currentLevel;
	std::string finishTime;
	int finishtime;

	Sprite2D playersprite;
	Sprite2D eggsprite;
	Sprite2D GameOver;
	Sprite2D victory;
	
	Coin coin;

	std::chrono::time_point<std::chrono::steady_clock> startTime;
	bool startedTimer;

	
};

}; // namespace Tmpl8