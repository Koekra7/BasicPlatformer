#pragma once
#include "SpriteSheet.h"
#include <LDtkLoader/Project.hpp>
#include <memory>
#include "spriteSheet.h"

class Player 
{
public:
	Player() = default;
	Player(const Rect& playerSize, float posX, float posY, float speedX, float speedY);
	~Player() = default;

	void Draw(Tmpl8::Surface* surface, int left, int right, int up, int down, int maxSpeedX, int maxSpeedY, float exeleration , bool addGrafity, int jumpForce, std::vector <Rect> collisionObject); // draws a movable player
	
private:
	Rect playerSize; // defines the playerSize
	float posX;
	float posY;
	float speedX;
	float speedY;
};