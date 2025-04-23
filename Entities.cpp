#include "entities.h"
#include "SpriteSheet.h"
#include "game.h"
#include <LDtkLoader/Project.hpp>
#include <vector>
#include <memory>

Hitbox::Hitbox(const Rect& hitbox)
	: hitbox(hitbox)
{
	
}

void Hitbox::Draw(Tmpl8::Surface* surface, const Tmpl8::vec2& pos) // drawing the hitbox
{
	surface->Box(hitbox.x + pos.x, hitbox.y + pos.y, hitbox.x + hitbox.w + pos.x, hitbox.y + hitbox.h + pos.y, 0xff0000);
	
}

void Finish::LevelFinish(Tmpl8::Surface* surface, Rect finish, bool draw, Rect playerSize, float x, float y) // drawing the finish
{
	if (draw) // drawing the finish hitbox
	{
		surface->Box(finish.x, finish.y, finish.x + finish.w, finish.y + finish.h, 0xff00ff);
	}
	
	if(x + playerSize.w > finish.x && x < finish.x + finish.w && y < finish.y + finish.h && y + playerSize.h > finish.y ) // checking if player is inside finish
	{
		std::cout << "you have completed the level" << '\n';
		currentLevel++;
	}

	
}

int Finish::isFinishHit() // giving the currentLevel
{
	return currentLevel;
}

float Damage = 0; // Damage variable
float DamageObject::getDamage(const ldtk::Layer& layer, Tmpl8::vec2 position, std::vector <Rect> collisionObject, Rect playersize)
{
	const auto& hitBoxLayer = layer.getEntitiesByName("HitBox"); // Get the tileset of the layer
	
	for (int i = 0; i < collisionObject.size(); i++) //repeat for the amount of hitboxes
	{
		if (position.y + playersize.h + 0.2f > collisionObject[i].y &&				// checking if the player is in the hitbox
			position.y < collisionObject[i].y + collisionObject[i].h &&
			position.x + playersize.w > collisionObject[i].x &&
			position.x < collisionObject[i].x + collisionObject[i].w)
		{
			Damage = hitBoxLayer[i].get().getField<float>("Damage").value(); // setting the right amount of damage
			return Damage;
		}
		else
		{
			Damage = 0; // resetting damage
		}
	}
	return Damage;
	
}

std::vector <bool> check(1000);
std::vector <bool> check2(1000);
std::vector <bool> check3(1000);
std::vector <float> Ycurrent(1000);


void Coin::addCoin(Tmpl8::Surface* surface ,std::vector <Rect> collisionObject, Tmpl8::vec2 playerPosition, Rect playersize, Sprite2D sprite, float deltatime )
{
	


	for (int i = 0; i <= collisionObject.size() - 1; i++) //repeat for the amount of coins
	{
		if (check3[i] == false) 
		{
			Ycurrent[i] = collisionObject[i].y; // setting Ycurrent to the start pos of the coin/egg
			check3[i] = true;
		}
		
		if (playerPosition.y + playersize.h - 0.2f > collisionObject[i].y &&				// checking if the player is in the hitbox
			playerPosition.y < collisionObject[i].y + collisionObject[i].h &&
			playerPosition.x + playersize.w > collisionObject[i].x &&
			playerPosition.x < collisionObject[i].x + collisionObject[i].w
			&& check[i] == false)
		{
			coins++; // adding a coin
			check[i] = true; // setting the coin to collected
		}
		else if (check[i] == false) 
		{
			if (check2[i] == false) //checking where the coin/egg is in its loop/animation
			{
				if (Ycurrent[i] >= collisionObject[i].y - 10.0f) // checking if the coin/egg is at the top
				{
					Ycurrent[i] -= 10 * deltatime;
					if (Ycurrent[i] <= collisionObject[i].y - 10.0f)
					{
						check2[i] = true;
						break;
					}
				}
			}
			
			if (check2[i] == true) // checking where the coin / egg is in its loop / animation
			{
				if (Ycurrent[i] <= collisionObject[i].y) // checking if the coin/egg is in its original position
				{
					Ycurrent[i] += 10 * deltatime;
					if (Ycurrent[i] >= collisionObject[i].y)
					{
						check2[i] = false;
						break;
					}
				}
			}
			sprite.Draw(surface, Tmpl8::vec2(collisionObject[i].x, Ycurrent[i] + 2)); // drawing the coin/egg

			
		}
	}
}

void Coin::resetCheck() // resetting the check variables
{
	for (int i = 0; i < check.size(); i++)
	{
		check[i] = false;
	}
	for (int i = 0; i < check2.size(); i++)
	{
		check2[i] = false;
	}
	for (int i = 0; i < check3.size(); i++)
	{
		check3[i] = false;
	}
}


