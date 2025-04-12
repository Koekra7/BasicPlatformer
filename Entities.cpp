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

void Hitbox::Draw(Tmpl8::Surface* surface, const Tmpl8::vec2& pos)
{
	surface->Box(hitbox.x + pos.x, hitbox.y + pos.y, hitbox.x + hitbox.w + pos.x, hitbox.y + hitbox.h + pos.y, 0xff0000);
	
}

int currentLevel;

void Finish::LevelFinish(Tmpl8::Surface* surface, Rect finish, bool draw, Rect playerSize, float x , float y)
{
	if (draw) 
	{
		surface->Box(finish.x, finish.y, finish.x + finish.w, finish.y + finish.h, 0xff00ff);
	}
	
	if(x + playerSize.w > finish.x && x < finish.x + finish.w && y < finish.y + finish.h && y + playerSize.h > finish.y )
	{
		std::cout << "you have completed the level" << '\n';
		currentLevel++;
	}

	
}

int Finish::isFinishHit()
{
	return currentLevel;
}

float Damage = 0; // Damage variable
float DamageObject::getDamage(const ldtk::Layer& layer, Tmpl8::vec2 position, std::vector <Rect> collisionObject, Rect playersize)
{
	const auto& hitBoxLayer = layer.getEntitiesByName("HitBox"); // Get the tileset of the layer
	
	for (int i = 0; i <= collisionObject.size() - 1; i++) //repeat for the amount of hitboxes
	{
		if (position.y + playersize.h - 0.2f > collisionObject[i].y &&				// checking if the player is in the hitbox
			position.y < collisionObject[i].y + collisionObject[i].h &&
			position.x + playersize.w > collisionObject[i].x &&
			position.x < collisionObject[i].x + collisionObject[i].w)
		{
			Damage = hitBoxLayer[i].get().getField<float>("Damage").value();
			return Damage;
			std::cout << Damage << '\n'; // Print the damage to the console
		}
		else
		{
			Damage = 0;
		}
	}
	return Damage;
	
}
