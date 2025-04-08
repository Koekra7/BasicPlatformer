#pragma once
#include "SpriteSheet.h"
#include <LDtkLoader/Project.hpp>
#include <memory>
#include "spriteSheet.h"

class Player 
{
public:
	Player() = default;
	Player(const Rect& playerSize, float speedX, float speedY);
	~Player() = default;

	void Draw(Tmpl8::Surface* surface); // draws a movable player
	struct Position { float x; float y; };
	const Position GetPosition();
	void setPlayerPos(int x, int y);
	void playerHealth(Tmpl8::Surface* surface, Rect playerHealthBar, float currentHealth);
	void addCollisions(bool addCollisions, std::vector <Rect> collisionObject);
	void movePlayer(int maxSpeedX, int maxSpeedY, float exeleration, bool addGrafity, int jumpForce);
	void keyUp(int key);
	void keyDown(int key);

private:
	Rect playerSize; // defines the playerSize
	float posX;
	float posY;
	float speedX;
	float speedY;
	Position position;
};