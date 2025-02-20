#include "entities.h"
#include "SpriteSheet.h"
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

