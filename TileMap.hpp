#pragma once // makes sure that it is only called once

#include "SpriteSheet.h"
#include <memory>
#include <vector>



class TileMap 
{
public:
	TileMap() = default; // Constructor.
	TileMap(std::shared_ptr<SpriteSheet> spriteSheet, int rows, int columns); // Constructor.
	~TileMap() = default; // Destructor.

	void Draw(Tmpl8::Surface* surface, const Tmpl8::vec2& pos); // Draw the tiles.

	int operator()(int row, int column) const; // Read the tiles.
	int& operator()(int row, int column); // Read and write the tiles.

	int GetRows() const { return rows; } // Get the number of rows.
	int GetColumns() const { return columns; } // Get the number of columns.

private:
	std::shared_ptr<SpriteSheet> spriteSheet; // Sprite sheet.
	int rows = 0; // Number of rows.
	int columns = 0; // Number of columns.
	std::vector<int> tiles; // Tiles.
};
