#include "Player.h"
#include "SpriteSheet.h"
#include "surface.h"
#include "game.h"
#include <LDtkLoader/Project.hpp>
#include <vector>
#include <memory>
#include <Windows.h>


Player::Player(const Rect& playerSize, float posX, float posY, float speedX, float speedY)
	: playerSize (playerSize), posX (posX), posY(posY), speedX(speedX), speedY(speedY)
{

}


bool hitTheGround = false;

void Player::Draw(Tmpl8::Surface* surface, int left, int right, int up, int down, int maxSpeedX, int maxSpeedY, float exeleration, bool addGrafity, int jumpForce, std::vector <Rect> collisionObject)
{

	if (GetAsyncKeyState(left)) speedX -= exeleration;
	else if (speedX < 0) speedX = 0;
	if (GetAsyncKeyState(right)) speedX += exeleration;
	else if (speedX > 0) speedX = 0;
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


	for (int i = 0; i <= collisionObject.size() - 1; i++) //
	{
		if (posY >= collisionObject[i].y && 
			posY <= collisionObject[i].y + collisionObject[i].h && 
			posX >= collisionObject[i].x && 
			posX <= collisionObject[i].x + collisionObject[i].w)

		{ // checks the top left corner of player for a collision
			auto x = (collisionObject[i].x + collisionObject[i].w - posX);
			auto y = (collisionObject[i].y + collisionObject[i].h - posY);
			if (x < y)
			{
				posX = collisionObject[i].x + collisionObject[i].w;
				speedX = 0;
			}
			else
			{
				posY = collisionObject[i].y + collisionObject[i].h;
				speedY = 0;
			}
		}
		if (posY + playerSize.h >= collisionObject[i].y && 
			posY + playerSize.h <= collisionObject[i].y + collisionObject[i].h && 
			posX + playerSize.w >= collisionObject[i].x && 
			posX + playerSize.w <= collisionObject[i].x + collisionObject[i].w)

		{ // checks the bottom right corner of player for a collision
			auto x = (collisionObject[i].x + posX);
			auto y = (collisionObject[i].y + posY);
			if (x > y)
			{
				posX = collisionObject[i].x - playerSize.w - 1;
				speedX = 0;
			}
			else
			{
				posY = collisionObject[i].y - playerSize.h - 1;
				speedY = 0;
				hitTheGround = true;
			}
		}
	}


	
	



	if (posX < 0) posX = 0, speedX = 0;
	if (posY < 0) posY = 0, speedY = 0;
	if (posX + playerSize.w > surface->GetWidth()) posX = surface->GetWidth() - playerSize.w -1 , speedX = 0;
	if (posY + playerSize.h > surface->GetHeight()) posY = surface->GetHeight() - playerSize.h - 1, speedY = 0, hitTheGround = true;

	surface->Box(playerSize.x + posX, playerSize.y + posY, playerSize.x + playerSize.w + posX, playerSize.y + playerSize.h + posY, 0x00ff00);
}

