#include "Player.h"
#include "SpriteSheet.h"
#include "surface.h"
#include "game.h"
#include <LDtkLoader/Project.hpp>
#include <vector>
#include <memory>
#include <Windows.h>
#include <SDL.h>


Player::Player(const Rect& playerSize, float speedX, float speedY)
	: playerSize (playerSize), speedX(speedX), speedY(speedY)
{
	posX = playerSize.x;
	posY = playerSize.y;
}


bool hitTheGround = false;

void Player::Draw(Tmpl8::Surface* surface)
{
	surface->Box(posX, posY, playerSize.w + posX, playerSize.h + posY, 0x00ff00);
}

void Player::addCollisions(bool addCollisions, std::vector <Rect> collisionObject)
{
	if (addCollisions)
	{
		float minmaxX = 0; // minimum of the maximum position of the collider
		float minmaxY = 0;
		float maxminX = 0;
		float maxminY = 0;


		for (int i = 0; i <= collisionObject.size() - 1; i++) //repeat for the amount of hitboxes
		{
			if (posY + playerSize.h > collisionObject[i].y &&				// checking if the player is in the hitbox
				posY < collisionObject[i].y + collisionObject[i].h &&
				posX + playerSize.w > collisionObject[i].x &&
				posX < collisionObject[i].x + collisionObject[i].w)

			{
				if (posX < collisionObject[i].x) // getting the smallest of the maximums
				{
					minmaxX = posX;
				}
				else { minmaxX = collisionObject[i].x; }
				
				if (posY < collisionObject[i].y) { minmaxY = posY; }
				else { minmaxY = collisionObject[i].y; }
					
				if (posX + playerSize.w < collisionObject[i].x + collisionObject[i].w) // getting the biggest of the minimums
				{
					maxminX = collisionObject[i].x + collisionObject[i].w;
				}
				else { maxminX = posX + playerSize.w; }

				if (posY + playerSize.h < collisionObject[i].y + collisionObject[i].h) { maxminY = posY + playerSize.h; }
				else { maxminY = collisionObject[i].y + collisionObject[i].h; }

				float collisionX = maxminX - minmaxX;
				float collisionY = maxminY - minmaxY;

				if (collisionX < collisionY)
				{
					if (posX < collisionObject[i].x)
					{
						posX = collisionObject[i].x - playerSize.w - 1;
						speedX = 0;
					}
					else
					{
						posX = collisionObject[i].x + collisionObject[i].w + 1;
						speedX = 0;
					}
				}
				else
				{
					if (posY < collisionObject[i].y)
					{
						posY = collisionObject[i].y - playerSize.h;
						speedY = 0;
						hitTheGround = true;
					}
					else
					{
						posY = collisionObject[i].y + collisionObject[i].h + 1;
						speedY = 0;
					}
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

void Player::movePlayer(float maxSpeedX, float exeleration, bool addGrafity, float jumpForce, float deltatime)
{
	speedX += d * exeleration;
	speedX -= a * exeleration;
	//posY += s * exeleration;
	//speedY -= w * exeleration;

	if (addGrafity) { speedY += 1000 * deltatime; } // adds grafity

	if (space && hitTheGround == true || w != 0 && hitTheGround)
	{
		speedY = -jumpForce;
		hitTheGround = false;
	}

	if (speedX >= maxSpeedX) { speedX = maxSpeedX; }
	if (speedX <= maxSpeedX * -1) { speedX = maxSpeedX * -1; }

	posX += speedX * deltatime;
	posY += speedY * deltatime;

	if (posX < 0) posX = 0, speedX = 0;
	if (posY < 0) posY = 0, speedY = 0;
	if (posX + playerSize.w > 800) posX = 800 - playerSize.w - 1, speedX = 0;
	if (posY + playerSize.h > 512) posY = 512 - playerSize.h - 1, speedY = 0, hitTheGround = true;

}


void Player::keyUp(int key)
{
	switch (key)
	{
	case SDL_SCANCODE_W:
		w = 0.0f;
		break;
	case SDL_SCANCODE_A:
		a = 0.0f;
		speedX = 0;
		break;
	//case SDL_SCANCODE_S:
	//	s = 0.0f;
	//	break;
	case SDL_SCANCODE_D:
		d = 0.0f;
		speedX = 0;
		break;
	case SDL_SCANCODE_SPACE:
		space = false;
		break;
	}
}

void Player::keyDown(int key)
{
	switch (key)
	{
	case SDL_SCANCODE_W:
		w = 1.0f;
		break;
	case SDL_SCANCODE_A:
		a = 1.0f;
		break;
	//case SDL_SCANCODE_S:
	//	s = 1.0f;
	//	break;
	case SDL_SCANCODE_D:
		d = 1.0f;
		break;
	case SDL_SCANCODE_SPACE:
		space = true;
		break;
	}
}

const Player::Position Player::GetPosition()
{
	position.x = posX;
	position.y = posY;
	return position;
}

void Player::setPlayerPos(int x, int y)
{
	posX = x;
	posY = y;
}

void Player::playerHealth(Tmpl8::Surface* surface, Rect playerHealthBar, float currentHealth)
{
	surface->Box(playerHealthBar.x, playerHealthBar.y, playerHealthBar.x + playerHealthBar.w, playerHealthBar.y + playerHealthBar.h, 0x00ff00);
	surface->Bar(playerHealthBar.x + 1, playerHealthBar.y + 1, playerHealthBar.x + playerHealthBar.w / 100 * currentHealth - 1, playerHealthBar.y + playerHealthBar.h - 1, 0xff0000);
} 
