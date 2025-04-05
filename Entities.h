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

class Finish 
{
public:
	Finish() = default;
	~Finish() = default;

	struct position { float x; float y; };
	void LevelFinish(Tmpl8::Surface* surface, Rect finish, bool draw, Rect playerSize, float x, float y);
	int isFinishHit();
	
};