#include "Player.h"
#include "SpriteSheet.h"
#include "surface.h"
#include "game.h"
#include <iostream>
#include <LDtkLoader/Project.hpp>
#include <vector>
#include <memory>
#define NOMINMAX // to fix Windows and algoritm same name min/max
#include <Windows.h>
#include <SDL.h>
#include <algorithm>


Player::Player(const Rect& playerSize, float speedX, float speedY) // constructor
	: playerSize (playerSize), speedX(speedX), speedY(speedY)
{
	posX = static_cast<float>(playerSize.x);
	posY = static_cast<float>(playerSize.y);
}


bool hitTheGround = false;

void Player::Draw(Tmpl8::Surface* surface, Sprite2D playersprite, bool showhitbox) // drawing the player
{
	if (showhitbox)
	{
		surface->Box(static_cast<int>(posX), static_cast<int>(posY), playerSize.w + static_cast<int>(posX), playerSize.h + static_cast<int>(posY), 0x000000);
	}
	playersprite.Draw(surface, Tmpl8::vec2(posX - 16, posY - 16)); // draw the player sprite
}

void Player::addCollisions(bool addCollisions, std::vector <Rect> collisionObject)
{
	if (addCollisions)
	{
			
		for (int i = 0; i <= collisionObject.size() - 1; i++) //repeat for the amount of hitboxes
		{
			if (posY + playerSize.h > collisionObject[i].y &&				// checking if the player is in the hitbox
				posY < collisionObject[i].y + collisionObject[i].h &&
				posX + playerSize.w > collisionObject[i].x &&
				posX < collisionObject[i].x + collisionObject[i].w)

			{
				// calculating the overlap of the 2 colliders / the x Overlap is the min of the max - max of the min
				float xOverlap = std::min(posX + playerSize.w, static_cast<float>(collisionObject[i].x + collisionObject[i].w)) - std::max(posX, static_cast<float>(collisionObject[i].x));
				float yOverlap = std::min(posY + playerSize.h, static_cast<float>(collisionObject[i].y + collisionObject[i].h)) - std::max(posY, static_cast<float>(collisionObject[i].y));


				if (xOverlap < yOverlap) // if the overlap of the x axis is smaller then theck the sides
				{
					// Player is to the left of the collider.
					if (posX < collisionObject[i].x)
					{
						posX = static_cast<float>(collisionObject[i].x - playerSize.w);
					}
					else // Player is to the right of the collider.
					{
						posX = static_cast<float>(collisionObject[i].x + collisionObject[i].w);
					}
					// Zero the x-velocity.
					speedX = 0.0f;
				}
				else // if the overlap of the y axis is smaller then theck the top and bottom
				{
					// The players is above the collider.
					if (posY < collisionObject[i].y)
					{
						posY = static_cast<float>(collisionObject[i].y - playerSize.h);
						hitTheGround = true; // allow the player to jump
					}
					else
					{
						posY = static_cast<float>(collisionObject[i].y + collisionObject[i].h);
					}
					speedY = 0.0f;
				}
			}
		}

	}
}

float w = 0.0f;
float a = 0.0f;
float s = 0.0f;
float d = 0.0f;
bool space = false;

void Player::movePlayer(float maxSpeedX, float exeleration, bool addGrafity, float jumpForce, float deltatime) // moving the player and adding the boosts from setSpeed
{
	speedX += d * exeleration * speedXboost;
	speedX -= a * exeleration * speedXboost;
	//posY += s * exeleration;
	//speedY -= w * exeleration;

	maxSpeedX *= speedXboost;

	if (addGrafity) { speedY += 1000 * deltatime; } // adds grafity

	if (space && hitTheGround == true || w != 0 && hitTheGround)
	{
		speedY = -jumpForce * speedYboost;
		hitTheGround = false;
	}

	if (speedX >= maxSpeedX) { speedX = maxSpeedX; }
	if (speedX <= maxSpeedX * -1) { speedX = maxSpeedX * -1; }

	posX += speedX * deltatime;
	posY += speedY * deltatime;

	if (posX < 0) posX = 0, speedX = 0;
	if (posY < 0) posY = 0, speedY = 0;
	if (posX + playerSize.w > 800) posX = 800.0f - static_cast<float>(playerSize.w) - 1.0f, speedX = 0;
	if (posY + playerSize.h > 512) posY = 512.0f - static_cast<float>(playerSize.h) - 1.0f, speedY = 0, hitTheGround = true;

}


void Player::keyUp(int key) // checking which key is released
{
	switch (key)
	{
	case SDL_SCANCODE_W:
	case SDL_SCANCODE_UP:
		w = 0.0f;
		break;
	case SDL_SCANCODE_A:
	case SDL_SCANCODE_LEFT:
		a = 0.0f;
		speedX = 0;
		break;
	//case SDL_SCANCODE_S:
	//	s = 0.0f;
	//	break;
	case SDL_SCANCODE_D:
	case SDL_SCANCODE_RIGHT:
		d = 0.0f;
		speedX = 0;
		break;
	case SDL_SCANCODE_SPACE:
		space = false;
		break;
	}
}

void Player::keyDown(int key) // checking which key is pressed
{
	switch (key)
	{
	case SDL_SCANCODE_W:
	case SDL_SCANCODE_UP:
		w = 1.0f;
		break;
	case SDL_SCANCODE_A:
	case SDL_SCANCODE_LEFT:
		a = 1.0f;
		break;
	//case SDL_SCANCODE_S:
	//	s = 1.0f;
	//	break;
	case SDL_SCANCODE_D:
	case SDL_SCANCODE_RIGHT:
		d = 1.0f;
		break;
	case SDL_SCANCODE_SPACE:
		space = true;
		break;
	}
}


int Player::currentframe() // checking which frame to use
{
	if (d != 0)
	{
		currentFrame = 12;
	}
	else if (a != 0)
	{
		currentFrame = 8;
	}
	else
	{
		currentFrame = 0;
	}
	return currentFrame;
}

void Player::playerHealth(Tmpl8::Surface* surface, Rect playerHealthBar, int currentHealth) // drawing the health bar
{
	surface->Box(playerHealthBar.x, playerHealthBar.y, playerHealthBar.x + playerHealthBar.w, playerHealthBar.y + playerHealthBar.h, 0x00ff00);
	surface->Bar(playerHealthBar.x + 1, playerHealthBar.y + 1, playerHealthBar.x + playerHealthBar.w / 100 * currentHealth - 1, playerHealthBar.y + playerHealthBar.h - 1, 0xff0000);
} 
