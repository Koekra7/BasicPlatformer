#include "TileMap.hpp"
#include <cassert> 

TileMap::TileMap(std::shared_ptr<SpriteSheet> spriteSheet, int rows, int columns) //constructor
	: spriteSheet(spriteSheet), rows(rows), columns(columns), tiles(rows* columns, -1) //initialize the variables
{

}

void TileMap::Draw(Tmpl8::Surface* surface, const Tmpl8::vec2& pos) //draw the tiles
{
	for (int y = 0; y < rows; y++) //loop through the rows
	{
		for (int x = 0; x < columns; x++) //loop through the columns
		{
			auto tile = tiles[y * columns + x]; //get the tile
			if (tile != -1) //if the tile is not empty
			{
				auto sprite = spriteSheet->GetSprite(tile); //get the sprite
				sprite.draw(surface, { x * sprite.getWidth() + pos.x, y * sprite.getHeight() + pos.y }); //draw the sprite
			}
		}
	}
}

int TileMap::operator()(int row, int column) const //read the tiles
{
	assert(row >= 0 && row < rows); //assert that the row is within the bounds
	assert(column >= 0 && column < columns); //assert that the column is within the bounds
	return tiles[row * columns + column]; //return the tile
}

int& TileMap::operator()(int row, int column) // read and write the tiles
{
	assert(row >= 0 && row < rows); //assert that the row is within the bounds
	assert(column >= 0 && column < columns); //assert that the column is within the bounds
	return tiles[row * columns + column]; //return the tile
}


