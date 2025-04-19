#pragma once

#include "template.h"
#include "surface.h"

#include <memory>
#include <vector>
#include <string>


struct Rect // Rectangle struct
{
	int x, y, w, h; // x and y coordinates, width and height
};

class Sprite2D
{
public:
	Sprite2D() = default;
	~Sprite2D() = default;
	Sprite2D(std::shared_ptr<Tmpl8::Surface> image, const Rect& rect); // Constructor.

	//Draw the sprite with the camera position taken into consideration.
	void Draw(Tmpl8::Surface* surface, const Tmpl8::vec2& pos); 
	int GetWidth() const { return rect.w; } // Get the width of the sprite.
	int GetHeight() const { return rect.h; } // Get the height of the sprite.

private:
	std::shared_ptr<Tmpl8::Surface> image; // Image of sprite.
	Rect rect; // Coordinates of sprite in image.
};

class SpriteSheet { // SpriteSheet class.
	 
public:
	SpriteSheet() = default; // Constructor.
	SpriteSheet(const std::string& path, int tilesize); // Constructor.
	~SpriteSheet() = default; // Destructor.

	const Sprite2D& GetSprite(int TileNumber);

private:
	std::shared_ptr<Tmpl8::Surface> image; // Image of sprite.
	std::vector<Sprite2D> sprites; // Sprites.
	int columns = 0; // Number of columns.
	int rows = 0; // Number of rows.
};


