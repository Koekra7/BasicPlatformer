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

	void Draw(Tmpl8::Surface* surface, Sprite2D playersprite, bool showhitbox); // draws a movable player
	Tmpl8::vec2 GetPosition() { return Tmpl8::vec2(posX, posY); } // returns the position of the player
	Tmpl8::vec2 GetSpeed() { return Tmpl8::vec2(speedX, speedY); } // returns the speed of the player
    void SetSpeed(float x, float y) { speedXboost = x; speedYboost = y; } // sets the speedboosts of the player
	void setPlayerPos(float x, float y) { posX = x; posY = y; } // sets the position of the player
	void playerHealth(Tmpl8::Surface* surface, Rect playerHealthBar, int currentHealth); // draws the health bar
	void addCollisions(bool addCollisions, std::vector <Rect> collisionObject); // adds collisions to the player
	void movePlayer(float maxSpeedX, float exeleration, bool addGrafity, float jumpForce, float deltatime); // moves the player
	void keyUp(int key); // checks which key is released
	void keyDown(int key); // checks which key is pressed
	int currentframe(); // checks which frame to use

private:
	Rect playerSize; // defines the playerSize
	float posX;
	float posY;
	float speedX;
	float speedY;
	float speedXboost;
	float speedYboost;
	int currentFrame;
};