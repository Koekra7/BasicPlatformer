#include "Player.h"
#include "SpriteSheet.h"
#include "surface.h"
#include "game.h"
#include <LDtkLoader/Project.hpp>
#include <vector>
#include <memory>
#include <Windows.h>


Player::Player(const Rect& playerSize, float speedX, float speedY)
	: playerSize (playerSize), speedX(speedX), speedY(speedY)
{
	posX = playerSize.x;
	posY = playerSize.y;
}


bool hitTheGround = false;

void Player::Draw(Tmpl8::Surface* surface, int left, int right, int up, int down, int maxSpeedX, int maxSpeedY, float exeleration, bool addGrafity, int jumpForce)
{
	
	if (GetAsyncKeyState(left)) speedX -= exeleration;
	else if (speedX <= 0) speedX = 0;
	if (GetAsyncKeyState(right)) speedX += exeleration;
	else if (speedX >= 0) speedX = 0;
	if (GetAsyncKeyState(up) && (hitTheGround == true))
	{
		speedY = -jumpForce;
		hitTheGround = false;
	}
	if (GetAsyncKeyState(down)) speedY += exeleration;

	if (addGrafity) { speedY += exeleration; } // adds grafity

	if (speedX <= maxSpeedX) { posX += speedX; }
	else { speedX = maxSpeedX, posX += speedX; }
	if (speedY <= maxSpeedY) { posY += speedY; }
	else { speedY = maxSpeedY, posY += speedY; }

	if (speedX >= maxSpeedX * -1) { posX += speedX; }
	else { speedX = maxSpeedX * -1, posX += speedX; }
	if (speedY >= maxSpeedY * -1) { posY += speedY; }
	else { speedY = maxSpeedY * -1, posY += speedY; }

	if (posX < 0) posX = 0, speedX = 0;
	if (posY < 0) posY = 0, speedY = 0;
	if (posX + playerSize.w > surface->GetWidth()) posX = surface->GetWidth() - playerSize.w -1 , speedX = 0;
	if (posY + playerSize.h > surface->GetHeight())posY = surface->GetHeight() - playerSize.h - 1, speedY = 0, hitTheGround = true;

	surface->Box(posX, posY, playerSize.w + posX, playerSize.h + posY, 0x00ff00);

	position.x = posX;
	position.y = posY;
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

const Player::Position Player::GetPosition()
{
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
