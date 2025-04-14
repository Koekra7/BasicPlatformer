#include "SpriteSheet.h"

#include <cassert>
#include <string>

Sprite2D::Sprite2D(std::shared_ptr<Tmpl8::Surface> image, const Rect& rect) //constructor
	: image(image), rect(rect) //initialize the variables
{
}

void Sprite2D::Draw(Tmpl8::Surface* surface, const Tmpl8::vec2& pos) //draw the sprite
{
	for (int y = 0; y < rect.h; y++) //loop through the height of the sprite
	{
		for (int x = 0; x < rect.w; x++) //loop through the width of the sprite
		{
			Tmpl8::Pixel color = image->GetBuffer()[(x + rect.x) + (y + rect.y) * image->GetPitch()]; //get the color of the pixel
			if (color >> 24 > 0)
				surface->Plot(x + pos.x, y + pos.y, image->GetBuffer()[(x + rect.x) + (y + rect.y) * image->GetPitch()]); //draw the sprite
		}
	}
}

SpriteSheet::SpriteSheet(const std::string& path, int tilesize) //constructor
{
	image = std::make_shared<Tmpl8::Surface>(path.c_str()); //load the image
	columns = image->GetWidth() / tilesize; //number of tiles in x 
	rows = image->GetHeight() / tilesize; //number of tiles in y
	for (int y = 0; y < rows; y++) //loop through the tiles in y
	{
		for (int x = 0; x < columns; x++) //loop through the tiles in x
		{
			Rect rect; //create a rectangle
			rect.x = x * tilesize; //set the x coordinate
			rect.y = y * tilesize; //set the y coordinate
			rect.w = tilesize; //set the width
			rect.h = tilesize; //set the height
			sprites.emplace_back(image, rect); //add the sprite to the vector
		}
	}


}



const Sprite2D& SpriteSheet::GetSprite(int TileNumber) //get the sprite
{
	assert(TileNumber < sprites.size()); //assert that the tile number is within the bounds
	return sprites[TileNumber]; //return the sprite
}

