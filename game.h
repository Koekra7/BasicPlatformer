#pragma once
#include "TileMap.hpp"
#include "Player.h"
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
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
private:
	Surface* screen;
	Surface* tiles;
	ldtk::Project project; 

	TileMap tilemap;
	Player player;

	float playerX;
	float playerY;

	std::vector<Rect> hitboxes;

	Rect playerSize;
	Rect startPosition;

	
};

}; // namespace Tmpl8