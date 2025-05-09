#pragma once
#include "SpriteSheet.h"
#include "Player.h"
#include <LDtkLoader/Project.hpp>
#include "spriteSheet.h"

class Hitbox
{
public:
	Hitbox() = default; // Default constructor
	Hitbox(const Rect& hitbox); // Constructor with parameters
	~Hitbox() = default; // Default destructor

	void Draw(Tmpl8::Surface* surface, const Tmpl8::vec2& pos); // Draw the hitbox

	

private:
	Rect hitbox; // The hitbox
	

};
class Coin
{
public:
	Coin() = default;
	~Coin() = default;
	void addCoin(Tmpl8::Surface* surface, std::vector <Rect> collisionObject, Tmpl8::vec2 playerPosition, Rect playerSize, Sprite2D sprite, float deltatime); // Add the coin
	void resetCheck();// Reset the coin
	void setCoins(int coin) { coins = coin; } // Set the coins
	int getCoins() { return coins; } // Get the coins
	

private:
	int coins;
};

class Finish 
{
public:
	Finish() = default;
	~Finish() = default;

	struct position { float x; float y; }; // position struct
	void LevelFinish(Tmpl8::Surface* surface, Rect finish, bool draw, Rect playerSize, float x, float y); // Draw the finish
	int isFinishHit(); // Check if the finish is hit
	
private:
	int currentLevel;
};

class DamageObject
{
public:
	DamageObject() = default; // Default constructor
	~DamageObject() = default; // Default destructor
	float getDamage(const ldtk::Layer& layer, Tmpl8::vec2 position, std::vector <Rect> collisionObject, Rect playersize); // Get the damage
	
private:

};